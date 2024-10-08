#include "scanner.hpp"
#include <iostream>
#include <string>
#include <cctype>

static const std::string_view error_message = "Unexpected character";
Token Scanner::scanToken()
{
    skip_space();
    start = current;
    if (isAtEnd())
        return makeToken(TOKEN_EOF);
    char ch = advance();
    if (std::isdigit(ch))
        return number();
    if (std::isalpha(ch) || ch == '_')
        return identifier();

    switch (ch)
    {
    case ':':
        return makeToken(TOKEN_COLON);
    case '[':
        return makeToken(TOKEN_LEFT_BRACKET);
    case ']':
        return makeToken(TOKEN_RIGHT_BRACKET);
    case '(':
        return makeToken(TOKEN_LEFT_PAREN);
    case ')':
        return makeToken(TOKEN_RIGHT_PAREN);
    case '{':
        return makeToken(TOKEN_LEFT_BRACE);
    case '}':
        return makeToken(TOKEN_RIGHT_BRACE);
    case ';':
        return makeToken(TOKEN_SEMICOLON);
    case ',':
        return makeToken(TOKEN_COMMA);
    case '.':
        return makeToken(TOKEN_DOT);
    case '-':
        if(match('='))
            return makeToken(TOKEN_MINUS_EQUAL);
        return makeToken(TOKEN_MINUS);
    case '+':
        if(match('='))
            return makeToken(TOKEN_ADD_EQUAL);
        return makeToken(TOKEN_PLUS);
    case '/':
        return makeToken(TOKEN_SLASH);
    case '*':
        return makeToken(TOKEN_STAR);
    case '!':
        return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
        return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<':
        return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
        return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    case '"':
        return this->string();
    }
    return Token{TOKEN_ERROR, error_message, line};
}
char Scanner::peek()
{
    return *current;
}
char Scanner::advance()
{
    char ch = *current;
    current++;
    return ch;
}
void Scanner::skip_space()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
            line++;
            advance();
            break;
        case '/':
            if (peek_next() == '/')
            {
                while (peek() != '\n' && !isAtEnd())
                    advance();
            }
            else
            {
                return;
            }
            break;
        default:
            return;
        }
    }
}
bool Scanner::match(char wana)
{
    if (isAtEnd())
        return false;
    if (*current != wana)
        return false;
    current++;
    return true;
}
bool Scanner::isAtEnd()
{
    return current == source.end() || *current == '\0';
}
Token Scanner::makeToken(TokenType type)
{
    return Token{type, std::string_view(start, std::distance(start, current)), line};
}
char Scanner::peek_next()
{
    if (isAtEnd())
        return '\0';
    return *(current + 1);
}
Token Scanner::number()
{
    while (std::isdigit(peek()))
        advance();

    if (peek() == '.' && std::isdigit(peek_next()))
        advance();

    while (std::isdigit(peek()))
        advance();
    return makeToken(TOKEN_NUMBER);
}
Token Scanner::string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            line++;
        advance();
    }
    if (isAtEnd())
        return Token{TOKEN_ERROR, error_message, line};
    advance();
    return makeToken(TOKEN_STRING);
}
Token Scanner::identifier()
{
    while (std::isalpha(peek()) || std::isdigit(peek()) || peek() == '_')
        advance();
    return makeToken(identifier_type());
}
TokenType Scanner::identifier_type()
{
    auto str = std::string_view(start, std::distance(start, current));
    return check_keyword.find(str) != check_keyword.end()
               ? check_keyword.at(str)
               : TOKEN_IDENTIFIER;
}