#include "value.hpp"
#include "obj.hpp"
#include "objstring.hpp"
#include "object.hpp"

bool Value::operator!() const
{
	if (is_number())
	{
		return !as<int>();
	}
	else if (is_bool())
	{
		return !as<bool>();
	}
	else if (is_nil())
	{
		return true;
	}
	throw std::runtime_error("Operand ! don't not fit");
}
bool Value::operator>(const Value &v) const
{
	return !(*this <= v);
}
bool Value::operator>=(const Value &v) const
{
	return *this > v || this->value == v.value;
}
bool Value::operator<=(const Value &v) const
{
	return *this < v || this->value == v.value;
}

bool Value::operator<(const Value &v) const
{
	if (is_number())
		return as<int>() < v.as<int>();
	throw std::runtime_error("Operator need to be a number.");
}
Value Value::operator-() const
{
	if (is_number())
		return Value(-as<int>());
	throw std::runtime_error("Operator need to be a number.");
}

Value Value::operator+(const Value &other) const
{
	return performOperation(other, std::plus<>());
}

Value Value::operator-(const Value &other) const
{
	return performOperation(other, std::minus<>());
}

Value Value::operator*(const Value &other) const
{
	return performOperation(other, std::multiplies<>());
}

Value Value::operator/(const Value &other) const
{
	return performOperation(other, std::divides<>());
}

Value::Value(bool value) : value(value) {}
Value::Value() : value(std::monostate()) {}
Value::Value(int value) : value(value) {}
Value::Value(Obj *obj) : value(obj) {}

template auto Value::is_obj_type<ObjString>() const -> typename std::enable_if_t<std::is_base_of_v<Obj, ObjString> && !std::is_same_v<Obj, ObjString>, bool>;
template auto Value::as_obj<ObjString>() const -> typename std::enable_if_t<std::is_base_of_v<Obj, ObjString> && !std::is_same_v<Obj, ObjString>, ObjString *>;
template auto Value::is_obj_type<ObjFunction>() const -> typename std::enable_if_t<std::is_base_of_v<Obj, ObjFunction> && !std::is_same_v<Obj, ObjFunction>, bool>;
template auto Value::as_obj<ObjFunction>() const -> typename std::enable_if_t<std::is_base_of_v<Obj, ObjFunction> && !std::is_same_v<Obj, ObjFunction>, ObjFunction*>;
template auto Value::is_obj_type<ObjNative>() const -> typename std::enable_if_t<std::is_base_of_v<Obj, ObjNative> && !std::is_same_v<Obj, ObjNative>, bool>;
template auto Value::as_obj<ObjNative>() const -> typename std::enable_if_t<std::is_base_of_v<Obj, ObjNative> && !std::is_same_v<Obj, ObjNative>, ObjNative*>;


template <typename U>
auto Value::is_obj_type() const -> typename std::enable_if_t<std::is_base_of_v<Obj, U> && !std::is_same_v<Obj, U>, bool>
{
	if (is_obj())
	{
		auto obj = as<Obj *>();
		return obj->is_type(objtype_of<U>());
	}
	return false;
}

template <typename U>
auto Value::as_obj() const -> typename std::enable_if_t<std::is_base_of_v<Obj, U> && !std::is_same_v<Obj, U>, U *>
{
	if (is_obj_type<U>())
		return static_cast<U *>(as<Obj *>());
	else
		throw std::invalid_argument(std::string("Value is not a ") + nameof<U>().data());
}

bool operator==(const Value &v1, const Value &v2)
{
	return v1.value == v2.value;
}

bool operator!=(const Value &v1, const Value &v2)
{
	return v1.value != v2.value;
}

template <typename Op>
Value Value::performOperation(const Value &other, Op op) const
{
	if (is_number() && other.is_number())
		return Value(op(as<int>(), other.as<int>()));
	throw std::runtime_error("PerformOperation only used for number.");
}
void test() {

}

std::ostream &operator<<(std::ostream &os, const Value &value)
{
	test();
	std::visit([&os](auto &&arg)
			   {
                   using T = std::decay_t<decltype(arg)>;
                   if constexpr (std::is_same_v<T, bool>)
                       os << std::boolalpha << arg << std::noboolalpha;
                   else if constexpr (std::is_same_v<T, std::monostate>)
                       os << "nil";
                   else if constexpr (std::is_same_v<T, int>)
                       os << arg;
                   else if constexpr (std::is_same_v<T, Obj*>) {
                       os << *arg;
                   } },
			   value.value);

	return os;
}