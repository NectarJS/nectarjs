#include "array.h"
#include "baseobject.cpp"
#include <sstream>

NJS::Class::Array::Array()
{
	BaseObject();
	__NJS_CreateMethodToClass("@@iterator", this->__iterator);
	__NJS_CreateMethodToClass("@@unscopables", this->__unscopables);
	__NJS_CreateMethodToClass("concat", this->concat);
	__NJS_CreateMethodToClass("copyWithin", this->copyWithin);
	__NJS_CreateMethodToClass("entries", this->entries);
	__NJS_CreateMethodToClass("every", this->every);
	__NJS_CreateMethodToClass("fill", this->fill);
	__NJS_CreateMethodToClass("filter", this->filter);
	__NJS_CreateMethodToClass("find", this->find);
	__NJS_CreateMethodToClass("findIndex", this->findIndex);
	__NJS_CreateMethodToClass("flat", this->flat);
	__NJS_CreateMethodToClass("flatMap", this->flatMap);
	__NJS_CreateMethodToClass("forEach", this->forEach);
	__NJS_CreateMethodToClass("includes", this->includes);
	__NJS_CreateMethodToClass("indexOf", this->indexOf);
	__NJS_CreateMethodToClass("join", this->join);
	__NJS_CreateMethodToClass("keys", this->keys);
	__NJS_CreateMethodToClass("lastIndexOf", this->lastIndexOf);
	__NJS_CreateMethodToClass("map", this->map);
	__NJS_CreateMethodToClass("pop", this->pop);
	__NJS_CreateMethodToClass("push", this->push);
	__NJS_CreateMethodToClass("reduce", this->reduce);
	__NJS_CreateMethodToClass("reduceRight", this->reduceRight);
	__NJS_CreateMethodToClass("reverse", this->reverse);
	__NJS_CreateMethodToClass("shift", this->shift);
	__NJS_CreateMethodToClass("slice", this->slice);
	__NJS_CreateMethodToClass("some", this->some);
	__NJS_CreateMethodToClass("sort", this->sort);
	__NJS_CreateMethodToClass("splice", this->splice);
	__NJS_CreateMethodToClass("toLocaleString", this->toLocaleString);
	__NJS_CreateMethodToClass("toString", this->toString);
	__NJS_CreateMethodToClass("unshift", this->unshift);
	__NJS_CreateMethodToClass("values", this->values);
	(*this)["length"] = 0;
}

NJS::Class::Array::operator NJS::VAR() const
{
	auto _var = NJS::VAR();
	_var.type = NJS::Enum::Type::ARRAY;
	REGISTER[_ptr].a = this;
	return _var;
}

explicit NJS::Class::Array::operator bool() const
{
	return true;
}
explicit NJS::Class::Array::operator double() const
{
	auto size = this->__NJS_VALUE.size();
	if (size == 0)
		return 0;
	if (size == 1)
		return (double)this->__NJS_VALUE[0];
	return NJS::Value::NaN;
}
explicit NJS::Class::Array::operator int() const
{
	auto size = this->__NJS_VALUE.size();
	return size == 1 ? (int)this->__NJS_VALUE[0] : 0;
}
explicit NJS::Class::Array::operator std::string() const
{
	auto &_arr = this->__NJS_VALUE;
	int l = _arr.size();
	if (l == 0)
		return "";
	std::stringstream stream;
	stream << (std::string)_arr[0]["toLocaleString"]();
	for (int i = 1; i < l; i++)
	{
		NJS::VAR val = _arr[i];
		stream << "," << (std::string)val["toLocaleString"]();
	}
	return stream.str();
}
explicit NJS::Class::Array::operator long long() const
{
	auto size = __NJS_VALUE.size();
	return size == 1 ? (long long)__NJS_VALUE[0] : NJS::Value::NaN;
}

NJS::VAR const &NJS::Class::Array::operator[](NJS::VAR _index) const
{
	if (_index.type != NJS::Enum::Type::NUMBER)
	{
		return BaseObject::operator[](_index);
	}
	int i = (int)_index;
	return (i <= __NJS_VALUE.size() && i >= 0) ? __NJS_VALUE[i] : NJS::Value::undefined;
};
NJS::VAR &NJS::Class::Array::operator[](NJS::VAR _index)
{
	if (_index.type != NJS::Enum::Type::NUMBER)
	{
		return BaseObject::operator[](_index);
	}
	int i = (int)_index;
	if (__NJS_VALUE.size() <= i)
	{
		__NJS_VALUE.reserve(i + 1);
		__NJS_VALUE.resize(i + 1);
		(*this)["length"] = (int)__NJS_VALUE.size();
	}
	return __NJS_VALUE.at(i);
};

NJS::VAR NJS::Class::Array::__iterator() const {}
NJS::VAR NJS::Class::Array::__unscopables() const {}
NJS::VAR NJS::Class::Array::concat(std::vector<NJS::VAR> args) const
{
	auto &res = *new NJS::Class::Array();
	auto &vec = res.__NJS_VALUE;
	for (auto _arr : args)
	{
		auto &arr = (NJS::Class::Array)_arr;
		vec.insert(vec.end(), arr.begin(), arr.end());
	}
	return res;
}
NJS::VAR NJS::Class::Array::copyWithin(std::vector<NJS::VAR> args)
{
	auto &vec = __NJS_VALUE;
	int _size = args.size();
	int target = _size > 0 ? (int)args[0] : 0;
	int start = _size > 1 ? (int)args[1] : 0;
	int end = _size > 2 ? (int)args[2] : vec.size();
	int size = vec.size();
	if (start < 0)
	{
		start += size;
	}
	if (end < 0)
	{
		end += size;
	}
	std::copy(vec.begin() + target, vec.begin() + end, vec.begin() + start);
	return *this;
}
NJS::VAR NJS::Class::Array::entries(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::every(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::fill(std::vector<NJS::VAR> args) const
{
	NJS::VAR value = args.size() ? args[0] : NJS::Value::undefined;
	__NJS_VALUE.assign(__NJS_VALUE.size(), value);
	return *this;
};
NJS::VAR NJS::Class::Array::filter(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::find(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::findIndex(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::flat(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::flatMap(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::forEach(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::includes(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::indexOf(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::join(std::vector<NJS::VAR> args) const
{
	auto _str = (std::string)(args.size() ? args[0] : NJS::Value::undefined);
	int l = __NJS_VALUE.size();
	if (l == 0)
		return "";
	std::stringstream stream;
	stream << (std::string)__NJS_VALUE[0]["toString"]();
	for (int i = 1; i < l; i++)
	{
		stream << _str << (std::string)__NJS_VALUE[i]["toString"]();
	}
	return stream.str();
};
NJS::VAR NJS::Class::Array::keys() const {}
NJS::VAR NJS::Class::Array::lastIndexOf(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::map(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::pop(std::vector<NJS::VAR> args) {}
NJS::VAR NJS::Class::Array::push(std::vector<NJS::VAR> args)
{
	for (auto value : args)
	{
		__NJS_VALUE.push_back(value);
	}
	return (*this)["length"] = (int)__NJS_VALUE.size();
};
NJS::VAR NJS::Class::Array::reduce(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::reduceRight(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::reverse(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::shift(std::vector<NJS::VAR> args) {}
NJS::VAR NJS::Class::Array::slice(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::some(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::sort(std::vector<NJS::VAR> args) const {}
NJS::VAR NJS::Class::Array::splice(std::vector<NJS::VAR> args) {}
NJS::VAR NJS::Class::Array::toLocaleString() const
{
	int l = __NJS_VALUE.size();
	if (l == 0)
		return "";
	std::stringstream stream;
	stream << (std::string)__NJS_VALUE[0]["toLocaleString"]();
	for (int i = 1; i < l; i++)
	{
		NJS::VAR val = __NJS_VALUE[i];
		stream << "," << (std::string)val["toLocaleString"]();
	}
	return stream.str();
}
NJS::VAR NJS::Class::Array::toString() const
{
	return this->join(std::vector<NJS::VAR>({","}));
}

NJS::VAR NJS::Class::Array::unshift(std::vector<NJS::VAR> values)
{
	auto pos = __NJS_VALUE.begin();
	for (auto value : values)
	{
		__NJS_VALUE.insert(pos, value);
	}
	return *this;
}
NJS::VAR NJS::Class::Array::values() const {}
