#include "compiler.hpp"
#include "tokentype.hpp"
#include "objstring.hpp"
#include "object.hpp"
#include "obj.hpp"
#include "memory.hpp"
#include "vm.hpp"

Complication::Complication(VM &vm) : current(nullptr), parser(nullptr), vm(vm), getRule({
                                                                                    {TOKEN_LEFT_BRACKET, {&Complication::list, &Complication::get_or_set, PREC_CALL}},
                                                                                    {TOKEN_RIGHT_BRACKET, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_LEFT_PAREN, {&Complication::grouping, &Complication::call, PREC_CALL}},
                                                                                    {TOKEN_RIGHT_PAREN, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_LEFT_BRACE, {&Complication::json, nullptr, PREC_NONE}},
                                                                                    {TOKEN_RIGHT_BRACE, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_COMMA, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_DOT, {nullptr, &Complication::dot, PREC_CALL}},
                                                                                    {TOKEN_MINUS, {&Complication::unary, &Complication::binary, PREC_TERM}},
                                                                                    {TOKEN_PLUS, {nullptr, &Complication::binary, PREC_TERM}},
                                                                                    {TOKEN_SEMICOLON, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_SLASH, {nullptr, &Complication::binary, PREC_FACTOR}},
                                                                                    {TOKEN_STAR, {nullptr, &Complication::binary, PREC_FACTOR}},
                                                                                    {TOKEN_BANG, {&Complication::unary, nullptr, PREC_NONE}},
                                                                                    {TOKEN_BANG_EQUAL, {nullptr, &Complication::binary, PREC_EQUALITY}},
                                                                                    {TOKEN_EQUAL, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_EQUAL_EQUAL, {nullptr, &Complication::binary, PREC_EQUALITY}},
                                                                                    {TOKEN_GREATER, {nullptr, &Complication::binary, PREC_COMPARISON}},
                                                                                    {TOKEN_GREATER_EQUAL, {nullptr, &Complication::binary, PREC_COMPARISON}},
                                                                                    {TOKEN_LESS, {nullptr, &Complication::binary, PREC_COMPARISON}},
                                                                                    {TOKEN_LESS_EQUAL, {nullptr, &Complication::binary, PREC_COMPARISON}},
                                                                                    {TOKEN_IDENTIFIER, {&Complication::variable, nullptr, PREC_NONE}},
                                                                                    {TOKEN_STRING, {&Complication::string, nullptr, PREC_NONE}},
                                                                                    {TOKEN_NUMBER, {&Complication::number, nullptr, PREC_NONE}},
                                                                                    {TOKEN_AND, {nullptr, &Complication::and_, PREC_AND}},
                                                                                    {TOKEN_CLASS, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_ELSE, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_FALSE, {&Complication::literal, nullptr, PREC_NONE}},
                                                                                    {TOKEN_FOR, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_FUN, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_IF, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_NIL, {&Complication::literal, nullptr, PREC_NONE}},
                                                                                    {TOKEN_OR, {nullptr, &Complication::or_, PREC_OR}},
                                                                                    {TOKEN_PRINT, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_RETURN, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_SUPER, {&Complication::super_, nullptr, PREC_NONE}},
                                                                                    {TOKEN_THIS, {&Complication::this_, nullptr, PREC_NONE}},
                                                                                    {TOKEN_TRUE, {&Complication::literal, nullptr, PREC_NONE}},
                                                                                    {TOKEN_VAR, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_WHILE, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_ERROR, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_EOF, {nullptr, nullptr, PREC_NONE}},
                                                                                    {TOKEN_COLON, {nullptr, nullptr, PREC_NONE}},
                                                                                })
{
}

ObjFunction *Complication::compile(const std::string_view &source)
{
    parser = std::make_unique<Parser>(source);
    initCompiler(TYPE_SCRIPT);
    advance();
    while (!match(TOKEN_EOF))
        declaration();
    consume(TOKEN_EOF, "Expect EOF in the end.");
    auto [function, done] = endCompiler();
    return parser->hadError ? nullptr : function;
}

Chunk *Complication::currentChunk()
{
    return &current->function->chunk;
}

auto Complication::endCompiler() -> std::pair<ObjFunction *, std::unique_ptr<Compiler>>
{
    emitReturn();
    ObjFunction *function = current->function;
#ifdef DEBUG_MODE
    if (!parser->hadError)
    {
        std::cout << "=== ";
        if (function->name != nullptr)
            std::cout << *function->name << "===\n";
        else
            std::cout << "<script>" << " ===\n";
    }
#endif
    std::unique_ptr<Compiler> done = std::move(current);
    current = std::move(done->enclosing);
    return {function, std::move(done)};
}

void Complication::synchronize()
{
    parser->panicMode = false;

    while (parser->current.type != TOKEN_EOF)
    {
        if (parser->previous.type == TOKEN_SEMICOLON)
            return;
        switch (parser->current.type)
        {
        case TOKEN_CLASS:
        case TOKEN_FUN:
        case TOKEN_VAR:
        case TOKEN_FOR:
        case TOKEN_IF:
        case TOKEN_WHILE:
        case TOKEN_PRINT:
        case TOKEN_RETURN:
            return;

        default:; // Do nothing.
        }

        advance();
    }
}

void Complication::advance()
{
    parser->previous = parser->current;
    while (true)
    {
        parser->current = parser->scanner.scanToken();
        if (parser->current.type != TOKEN_ERROR)
            break;

        parser->errorAtCurrent("Get error token.");
    }
}
void Complication::consume(TokenType type, const std::string &message)
{
    if (parser->current.type == type)
    {
        advance();
        return;
    }
    parser->errorAtCurrent(message);
}
void Complication::expression()
{
    parsePrecedence(PREC_ASSIGNMENT);
}
void Complication::parsePrecedence(Precedence precedence)
{
    advance();
    auto name = getRule.at(parser->previous.type);
    auto prefixRule = name.prefix;
    if (prefixRule == nullptr)
    {
        parser->error("No suitable prefixRule for " + std::string(parser->previous.string));
        return;
    }
    bool canAssign = precedence <= PREC_ASSIGNMENT;
    prefixRule(*this, canAssign);
    while (precedence <= getRule.at(parser->current.type).precedence)
    {
        advance();
        auto infixRule = getRule.at(parser->previous.type).infix;
        infixRule(*this, canAssign);
    }
    if (canAssign && match(TOKEN_EQUAL)) // to detect a * b = c * d gramma error
        parser->error("Can't be assigned.");
}
void Complication::number(bool canAssign)
{
    Value value = std::stoi(std::string(parser->previous.string));
    emitConstant(value);
}
void Complication::binary(bool canAssign)
{
    TokenType operatorType = parser->previous.type;
    auto rule = getRule.at(operatorType);
    parsePrecedence(static_cast<Precedence>(rule.precedence + 1));

    switch (operatorType)
    {
    case TOKEN_BANG_EQUAL:
        emitBytes(OP_EQUAL, OP_NOT);
        break;
    case TOKEN_EQUAL_EQUAL:
        emitByte(OP_EQUAL);
        break;
    case TOKEN_GREATER:
        emitByte(OP_GREATER);
        break;
    case TOKEN_GREATER_EQUAL:
        emitBytes(OP_LESS, OP_NOT);
        break;
    case TOKEN_LESS:
        emitByte(OP_LESS);
        break;
    case TOKEN_LESS_EQUAL:
        emitBytes(OP_GREATER, OP_NOT);
        break;
    case TOKEN_PLUS:
        emitByte(OP_ADD);
        break;
    case TOKEN_MINUS:
        emitByte(OP_SUB);
        break;
    case TOKEN_STAR:
        emitByte(OP_MUL);
        break;
    case TOKEN_SLASH:
        emitByte(OP_DIV);
        break;
    default:
        return; // Unreachable.
    }
}
void Complication::unary(bool canAssign)
{
    TokenType operatorType = parser->previous.type;
    expression();
    switch (operatorType)
    {
    case TOKEN_BANG:
        emitByte(OP_NOT);
        break;
    case TOKEN_MINUS:
        emitByte(OP_NEGATE);
        break;
    default:
        return; // Unreachable.
    }
}
void Complication::and_(bool canAssign)
{
    int endJump = emitJump(OP_JUMP_IF_FALSE);

    emitByte(OP_POP);
    parsePrecedence(PREC_AND);

    patchJump(endJump);
}
void Complication::or_(bool canAssign)
{
    int elseJump = emitJump(OP_JUMP_IF_FALSE);
    int endJump = emitJump(OP_JUMP);

    patchJump(elseJump);
    emitByte(OP_POP);

    parsePrecedence(PREC_OR);
    patchJump(endJump);
}
void Complication::grouping(bool canAssign)
{
    expression();
    consume(TOKEN_RIGHT_PAREN, "No right paren.");
}

void Complication::list(bool canAssign)
{
    // [value-1, value-2, value-3]
    int count = 0;
    if (!check(TOKEN_RIGHT_BRACKET))
    {
        do
        {
            count++;
            expression();
        } while (match(TOKEN_COMMA));
    }
    emitBytes(OP_ARRAY, count);
    consume(TOKEN_RIGHT_BRACKET, "Expect ']' to end array or list.");
}

void Complication::json(bool canAssign)
{
    int count = 0;
    if(!check(TOKEN_RIGHT_BRACE)) {
        do {
            count++;
            expression();
            consume(TOKEN_COLON, "Expect ':' to set json value.");
            expression();
        } while (match(TOKEN_COMMA));
    }
    emitBytes(OP_JSON, count);
    consume(TOKEN_RIGHT_BRACE, "Expect '}' to end json.");
}

void Complication::get_or_set(bool canAssign)
{
    expression();
    consume(TOKEN_RIGHT_BRACKET, "Expect ']' to get list element.");
    if(match(TOKEN_EQUAL)) {
        expression();
        emitByte(OP_SET_ELEMENT);
    }
    else
        emitByte(OP_GET_ELEMENT);
}

uint8_t Complication::argumentList()
{
    uint8_t argCount = 0;
    if (!check(TOKEN_RIGHT_PAREN))
    {
        do
        {
            expression();
            argCount++;
        } while (match(TOKEN_COMMA));
    }
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after arguments.");
    return argCount;
}

void Complication::super_(bool assign)
{
    if (currentClass == NULL)
        parser->error("Can't use 'super' outside of a class.");
    else if (!currentClass->hasSuperclass)
        parser->error("Can't use 'super' in a class with no superclass.");

    consume(TOKEN_DOT, "Expect '.' after 'super'.");
    consume(TOKEN_IDENTIFIER, "Expect superclass method name.");
    uint8_t name = identifierConstant(parser->previous);
    namedVariable(syntheticToken("this"), false);
    if (match(TOKEN_LEFT_PAREN))
    {
        uint8_t argCount = argumentList();
        namedVariable(syntheticToken("super"), false);
        emitBytes(OP_SUPER_INVOKE, name);
        emitByte(argCount);
    }
    else
    {
        namedVariable(syntheticToken("super"), false);
        emitBytes(OP_GET_SUPER, name);
    }
}

void Complication::call(bool canAssign)
{
    uint8_t argCount = argumentList();
    emitBytes(OP_CALL, argCount);
}

void Complication::literal(bool canAssign)
{
    switch (parser->previous.type)
    {
    case TOKEN_FALSE:
        emitByte(OP_FALSE);
        break;
    case TOKEN_NIL:
        emitByte(OP_NIL);
        break;
    case TOKEN_TRUE:
        emitByte(OP_TRUE);
        break;
    default:
        return; // Unreachable.
    }
}

void Complication::string(bool canAssign)
{
    std::string_view text = parser->previous.string;
    std::string_view str = text.substr(1, text.size() - 2);
    auto obj = create_obj_string(str, vm);
    emitConstant(obj);
}

void Complication::variable(bool canAssign)
{
    namedVariable(parser->previous, canAssign);
}

void Complication::statement()
{
    if (match(TOKEN_RETURN))
    {
        returnStatement();
    }
    else if (match(TOKEN_PRINT))
    {
        printStatement();
    }
    else if (match(TOKEN_IF))
    {
        ifStatement();
    }
    else if (match(TOKEN_WHILE))
    {
        whileStatement();
    }
    else if (match(TOKEN_FOR))
    {
        forStatement();
    }
    else if (match(TOKEN_LEFT_BRACE))
    {
        beginScope();
        block();
        endScope();
    }
    else
    {
        expressionStatement();
    }
}

void Complication::block()
{
    while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF))
        declaration();
    consume(TOKEN_RIGHT_BRACE, "block only have left right brace.");
}

void Complication::dot(bool canAssign)
{
    consume(TOKEN_IDENTIFIER, "Expect property name after '.'.");
    uint8_t name = identifierConstant(parser->previous);

    if (canAssign && match(TOKEN_EQUAL))
    {
        expression();
        emitBytes(OP_SET_PROPERTY, name);
    }
    else if (match(TOKEN_LEFT_PAREN))
    {
        uint8_t argCount = argumentList();
        emitBytes(OP_INVOKE, name);
        emitByte(argCount);
    }
    else
    {
        emitBytes(OP_GET_PROPERTY, name);
    }
}

void Complication::whileStatement()
{
    int loopStart = currentChunk()->bytecode.size();
    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'while'.");
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after condition.");

    int exitJump = emitJump(OP_JUMP_IF_FALSE);
    emitByte(OP_POP);
    statement();
    emitLoop(loopStart);

    patchJump(exitJump);
    emitByte(OP_POP);
}

void Complication::forStatement()
{
    beginScope();
    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'for'.");
    if (match(TOKEN_SEMICOLON))
    {
        // No initializer.
    }
    else if (match(TOKEN_VAR))
    {
        varDeclaration();
    }
    else
    {
        expressionStatement();
    }

    int loopStart = currentChunk()->bytecode.size();
    int exitJump = -1;
    if (!match(TOKEN_SEMICOLON))
    {
        expression();
        consume(TOKEN_SEMICOLON, "Expect ';' after loop condition.");

        // Jump out of the loop if the condition is false.
        exitJump = emitJump(OP_JUMP_IF_FALSE);
        emitByte(OP_POP); // Condition.
    }

    if (!match(TOKEN_RIGHT_PAREN))
    {
        int bodyJump = emitJump(OP_JUMP);
        int incrementStart = currentChunk()->bytecode.size();
        expression();
        emitByte(OP_POP);
        consume(TOKEN_RIGHT_PAREN, "Expect ')' after for clauses.");

        emitLoop(loopStart);
        loopStart = incrementStart;
        patchJump(bodyJump);
    }

    statement();
    emitLoop(loopStart);

    if (exitJump != -1)
    {
        patchJump(exitJump);
        emitByte(OP_POP); // Condition.
    }

    endScope();
}

void Complication::emitLoop(int loopStart)
{
    emitByte(OP_LOOP);

    int offset = currentChunk()->bytecode.size() - loopStart + 2;
    if (offset > UINT16_MAX)
        parser->error("Loop body too large.");

    emitByte((offset >> 8) & 0xff);
    emitByte(offset & 0xff);
}

void Complication::returnStatement()
{
    if (current->type == TYPE_SCRIPT)
        parser->error("Can't return from top-level code.");

    if (match(TOKEN_SEMICOLON))
        emitReturn();
    else
    {
        if (current->type == TYPE_INITIALIZER)
            parser->error("Can't return a value from an initializer.");

        expression();
        consume(TOKEN_SEMICOLON, "Expect ';' after return value.");
        emitByte(OP_RETURN);
    }
}

void Complication::printStatement()
{
    expression();
    consume(TOKEN_SEMICOLON, "At the end of statement required ;.");
    emitByte(OP_PRINT);
}

void Complication::ifStatement()
{
    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'if'.");
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after condition.");

    int thenJump = emitJump(OP_JUMP_IF_FALSE);
    emitByte(OP_POP);
    statement();
    int elseJump = emitJump(OP_JUMP);
    patchJump(thenJump);
    emitByte(OP_POP);

    if (match(TOKEN_ELSE))
        statement();
    patchJump(elseJump);
}

void Complication::expressionStatement()
{
    expression();
    consume(TOKEN_SEMICOLON, "expressionStatement needs ;.");
    emitByte(OP_POP);
}

void Complication::varDeclaration()
{
    uint8_t global = parseVariable("Expect variable declare.");
    if (match(TOKEN_EQUAL))
    {
        expression();
    }
    else
    {
        emitByte(OP_NIL);
    }
    consume(TOKEN_SEMICOLON, "Variable declaration needs ;.");
    defineVariable(global);
}

void Complication::namedVariable(Token name, bool canAssign)
{
    Opcode getOp, setOp;
    int arg = resolveLocal(current, name);
    if (arg != -1)
    {
        getOp = OP_GET_LOCAL;
        setOp = OP_SET_LOCAL;
    }
    else if ((arg = resolveUpvalue(current, name)) != -1)
    {
        getOp = OP_GET_UPVALUE;
        setOp = OP_SET_UPVALUE;
    }
    else
    {
        arg = identifierConstant(name);
        getOp = OP_GET_GLOBAL;
        setOp = OP_SET_GLOBAL;
    }
    if (canAssign && match(TOKEN_EQUAL))
    {
        expression();
        emitBytes(setOp, arg);
    }
    else
    {
        emitBytes(getOp, arg);
    }
}

int Complication::resolveLocal(const std::unique_ptr<Compiler> &compiler, const Token &name)
{
    for (int i = compiler->localCount - 1; i >= 0; i--)
    {
        Local &local = compiler->locals[i];
        if (identifiersEqual(name, local.name))
        {
            if (local.depth == -1)
                parser->error("var variable = variable is not allowed."); // var a = 1; {
                                                                          //     var a = a;  // we first define a and search a but this is not initialized
                                                                          //                 // if we first expression not define can get a = 1 result
                                                                          // }
            return i;
        }
    }
    return -1;
}

void Complication::markInitialized() // when define function and define local variable used
{
    if (current->scopeDepth == 0)
        return;
    if (current->scopeDepth > 0) // at start all depth is -1
        current->locals[current->localCount - 1].depth = current->scopeDepth;
}

void Complication::initCompiler(FunctionType type)
{
    auto compiler = std::make_unique<Compiler>();
    compiler->enclosing = std::move(current);
    current = std::move(compiler);
    current->function = create_obj<ObjFunction>(vm.gc);
    current->type = type;

    if (type != FunctionType::TYPE_SCRIPT)
        current->function->name = create_obj_string(parser->previous.string, vm);
    Local &local = current->locals.at(current->localCount++); // why
    local.depth = 0;
    local.isCaptured = false;
    if (type != TYPE_FUNCTION)
        local.name.string = "this";
    else
        local.name.string = std::string_view();
}

int Complication::resolveUpvalue(const std::unique_ptr<Compiler> &compiler, Token &name)
{
    if (compiler->enclosing == nullptr)
        return -1;
    int local = resolveLocal(compiler->enclosing, name);
    if (local != -1)
    {
        compiler->enclosing->locals[local].isCaptured = true;
        return addUpvalue(compiler, local, true);
    }

    int upvalue = resolveUpvalue(compiler->enclosing, name); // layer-by-layer
                                                             // to add upvalue
                                                             // and ensure concerned func
                                                             // all have upvalue
    if (upvalue != -1)
        return addUpvalue(compiler, upvalue, false); // capture upvalue

    return -1;
}

int Complication::addUpvalue(const std::unique_ptr<Compiler> &compiler, int index, bool isLocal)
{
    int upvalueCount = compiler->function->upvalueCount; // outside function firstly add upvalue
                                                         // and the outest one have 0 upvalueCount
                                                         // because only after outside capture it,
                                                         // can inside get upvalueCount and upvalue information
    for (int i = 0; i < upvalueCount; i++)
    {
        Upvalue &upvalue = compiler->upvalues[i];
        if (upvalue.index == index && upvalue.isLocal == isLocal) // index is about captured local-var
            return i;                                             // isLocal is outside function's local-var
    } // we shouldn't repeatedly add
    if (upvalueCount == UINT8_MAX)
    {
        parser->error("Too many closure variables in function.");
        return 0;
    }
    compiler->upvalues[upvalueCount].isLocal = isLocal;
    compiler->upvalues[upvalueCount].index = index;
    return compiler->function->upvalueCount++;
}

uint8_t Complication::parseVariable(const std::string &message)
{
    consume(TOKEN_IDENTIFIER, message);
    declareVariable();           // this function define local
    if (current->scopeDepth > 0) // below is to define global variable
        return 0;
    return identifierConstant(parser->previous);
}

uint8_t Complication::identifierConstant(const Token &token)
{
    auto name = create_obj_string(token.string, vm);
    return makeConstant(name);
}

int Complication::emitJump(Opcode instruction)
{
    emitByte(instruction);
    emitBytes(0xff, 0xff);
    return currentChunk()->bytecode.size() - 2;
}

void Complication::patchJump(int offset)
{
    int jump = currentChunk()->bytecode.size() - offset - 2;

    if (jump > UINT16_MAX)
        parser->error("Too much code to jump over.");

    currentChunk()->bytecode[offset] = (jump >> 8) & 0xff;
    currentChunk()->bytecode[offset + 1] = jump & 0xff;
}

bool Complication::check(TokenType type)
{
    return parser->current.type == type;
}

bool Complication::match(TokenType type)
{
    if (!check(type))
        return false;
    advance();
    return true;
}

void Complication::declaration()
{
    if (match(TOKEN_CLASS))
    {
        classDeclaration();
    }
    else if (match(TOKEN_FUN))
    {
        funDeclaration();
    }
    else if (match(TOKEN_VAR))
    {
        varDeclaration();
    }
    else
    {
        statement();
    }
}

void Complication::declareVariable()
{
    if (current->scopeDepth == 0)
        return;

    Token name = parser->previous;
    for (int i = current->localCount - 1; i >= 0; i--)
    {
        Local local = current->locals[i];
        if (local.depth != -1 && local.depth < current->scopeDepth)
            break;
        if (identifiersEqual(name, local.name))
            parser->error(std::string(name.string) + "has defined before.");
    }
    addLocal(name);
}

void Complication::classDeclaration()
{
    consume(TOKEN_IDENTIFIER, "Expect class name.");
    Token className = parser->previous;
    uint8_t nameConstant = identifierConstant(parser->previous);
    declareVariable();

    emitBytes(OP_CLASS, nameConstant);
    defineVariable(nameConstant);

    auto classCompiler = std::make_unique<ClassCompiler>();
    classCompiler->enclosing = std::move(currentClass);
    currentClass = std::move(classCompiler);

    if (match(TOKEN_LESS))
    {
        consume(TOKEN_IDENTIFIER, "Expect superclass name.");
        variable(false);

        if (className.string == parser->previous.string)
            parser->error("A class cannot inherit from itself.");

        beginScope();
        addLocal(syntheticToken("super"));
        defineVariable(0);

        namedVariable(className, false);
        emitByte(OP_INHERIT);
        currentClass->hasSuperclass = true;
    }

    namedVariable(className, false);

    consume(TOKEN_LEFT_BRACE, "Expect '{' before class body.");

    while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF))
        method();

    consume(TOKEN_RIGHT_BRACE, "Expect '}' after class body.");
    emitByte(OP_POP);

    if (currentClass->hasSuperclass)
        endScope();
    currentClass = std::move(currentClass->enclosing);
}

void Complication::funDeclaration()
{
    uint8_t global = parseVariable("Expect function name."); // before closure all function is global
    markInitialized();                                       // why initialize
    function(TYPE_FUNCTION);
    defineVariable(global);
}

void Complication::function(FunctionType type)
{
    initCompiler(type);
    beginScope();

    consume(TOKEN_LEFT_PAREN, "Expect '(' after function name.");
    if (!check(TOKEN_RIGHT_PAREN))
    {
        do
        {
            current->function->arity++;
            if (current->function->arity > 255)
                parser->errorAtCurrent("Can't have more than 255 parameters.");
            uint8_t constant = parseVariable("Expect parameter name.");
            defineVariable(constant);
        } while (match(TOKEN_COMMA));
    }
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after parameters.");
    consume(TOKEN_LEFT_BRACE, "Expect '{' before function body.");
    block();

    auto [function, done] = endCompiler();
    // emitBytes(OP_CONSTANT, makeConstant(static_cast<Obj *>(function)));
    emitBytes(OP_CLOSURE, makeConstant(function));
    for (int i = 0; i < function->upvalueCount; i++)
    {
        emitByte(done->upvalues[i].isLocal ? 1 : 0);
        emitByte(done->upvalues[i].index);
    }
}

void Complication::method()
{
    consume(TOKEN_IDENTIFIER, "Expect method name.");
    uint8_t constant = identifierConstant(parser->previous);
    FunctionType type = TYPE_METHOD;
    if (parser->previous.string == "init")
        type = TYPE_INITIALIZER;
    function(type);
    emitBytes(OP_METHOD, constant);
}

void Complication::this_(bool assign)
{
    if (currentClass == nullptr)
    {
        parser->error("Can't use 'this' outside of a class.");
        return;
    }
    variable(false);
}

void Complication::addLocal(Token name)
{
    if (current->localCount == UINT8_MAX)
    {
        parser->error("Local variable count has reached limit.");
        return;
    }
    Local &local = current->locals[current->localCount++];
    local.name = name;
    local.depth = -1;
}

bool Complication::identifiersEqual(const Token &a, const Token &b)
{
    return a.string == b.string;
}

void Complication::defineVariable(uint8_t global)
{
    if (current->scopeDepth > 0)
    {
        markInitialized(); // begin all current local variable depth is -1
        return;            // local variable has been defined before
    }
    emitBytes(OP_DEFINE_GLOBAL, global);
}

Token Complication::syntheticToken(const std::string_view text)
{
    Token token;
    token.string = text;
    return token;
}

void Complication::writeChunk(uint8_t op, int line)
{
    currentChunk()->bytecode.push_back(op);
    currentChunk()->lines.push_back(line);
}

uint8_t Complication::addConstant(Value value)
{
    vm.push(value);
    currentChunk()->constants.push_back(value);
    vm.pop();
    return currentChunk()->constants.size() - 1;
}

void Complication::emitConstant(Value value)
{
    emitBytes(OP_CONSTANT, makeConstant(value));
}
void Complication::emitBytes(uint8_t byte1, uint8_t byte2)
{
    emitByte(byte1);
    emitByte(byte2);
}
void Complication::emitReturn()
{
    if (current->type == TYPE_INITIALIZER)
        emitBytes(OP_GET_LOCAL, 0);
    else
        emitByte(OP_NIL);
    emitByte(Opcode::OP_RETURN);
}
void Complication::emitByte(uint8_t byte)
{
    writeChunk(byte, parser->previous.line);
}

uint8_t Complication::makeConstant(Value value)
{
    int constant = addConstant(value);
    if (constant > UINT8_MAX)
    {
        throw std::logic_error("Too many constants in one chunk.");
        return 0;
    }
    return (uint8_t)constant;
}
