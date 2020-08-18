#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdarg.h>

#ifdef __NJS_ARDUINO
#include <util/delay.h>
#include <string.h>
#include <WString.h>
#include <new.h>
#include <time.h>
#include <nonstd-function.h>
using namespace nonstd;
#else
#include <functional>
#endif

using namespace std;

enum __NJS_TYPE
{
	__NJS_UNDEFINED = 1,
	__NJS_NUMBER,
	__NJS_DOUBLE,
	__NJS_OBJECT,
	__NJS_BIGNUMBER,
	__NJS_BOOLEAN,
	__NJS_STRING,
	__NJS_NATIVE,
	__NJS_FUNCTION,
	__NJS_ARRAY,
	__NJS_NAN,
	__NJS_INFINITY,
	__NJS_NULL

};

/*** HELPERS ***/
#define __NJS_GET_STRING(_var) _var.get().s->__NJS_VALUE
#define var __NJS_VAR
#define let __NJS_VAR
#define __NJS_Create_Boolean(_value) __NJS_VAR(__NJS_BOOLEAN, _value)
#define __NJS_Create_Number(_value) __NJS_VAR(_value)
#define __NJS_Create_Function(_value) __NJS_VAR(__NJS_FUNCTION, _value)
#define __NJS_Create_Undefined() __NJS_VAR()
#define __NJS_DECL_FUNCTION function
#define __NJS_RETURN_UNDEFINED \
	var __undef = __NJS_VAR(); \
	return __undef;
#define __NJS_Create_String(_value) __NJS_VAR(_value)
#define __NJS_Create_Infinity() __NJS_VAR(__NJS_INFINITY, 0)
#define Infinity __NJS_Create_Infinity()
#define __NJS_Create_Null() __NJS_VAR(__NJS_NULL, 0)
#define __NJS_Create_Lambda(name) function<__NJS_VAR (vector<var>)>* name = new function<__NJS_VAR (vector<var>)>([](vector<var> __NJS_VARARGS)
#define __NJS_EXCEPTION_PARAMETER __NJS_VAR &e
#define finally ;
#define __NJS_BOOLEAN_TRUE __NJS_Create_Boolean(true)
#define __NJS_BOOLEAN_FALSE __NJS_Create_Boolean(false)
/*** END HELPERS ***/

struct __NJS_VAR;

class __NJS_Class_Object
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_Object();
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class __NJS_Class_String
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_String(string _str);
	string __NJS_VALUE;
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class __NJS_Class_Array
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_Array();
	vector<__NJS_VAR> __NJS_VALUE = vector<__NJS_VAR>();
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class __NJS_Class_Function
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_Function(void *_f);
	void *__NJS_VALUE;
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

class __NJS_Class_Native
{
public:
	int cnt = 0;
	void Delete();
	__NJS_Class_Native(void *_n);
	void *__NJS_VALUE;
	vector<pair<const char *, __NJS_VAR>> __OBJECT;
};

union __NJS_VAL {
	int i;
	double d;
	bool b;
	__NJS_Class_String *s;
	__NJS_Class_Array *a;
	__NJS_Class_Object *o;
	__NJS_Class_Function *f;
	__NJS_Class_Native *n;
};

/*** REGISTER ***/

int FREE_PTR = -1;
int REGISTER_PTR = 0;
#ifdef CL_WINDOWS
__NJS_VAL REGISTER[{{REGISTER}}];
#else
__NJS_VAL REGISTER[{{REGISTER}}]{(__NJS_VAL){.i = 0}};
#endif
int FREE[{{REGISTER}}] = {0};

/*** END REGISTER ***/

__NJS_VAR __NJS_Log_Console(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Keys(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var);
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var, bool _bracket);
/*** STRING MANIPULATION ***/
template <typename m, typename n>
string __NJS_Concat_To_Str(m _left, n _right)
{
	std::stringstream output;
	output << _left << _right;
	return output.str();
}
/* END STRING MANIPULATION */

/*** NUMBER MANIPULATION ***/
template <typename m>
int __NJS_Str_To_Int(m _left)
{
	int out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
template <typename m>
double __NJS_Str_To_Double(m _left)
{
	double out;
	std::stringstream output;
	output << _left;
	output >> out;
	return out;
}
/* END NUMBER MANIPULATION */

struct __NJS_VAR
{
private:
	void setPtr()
	{
		if (_ptr > -1)
		{
			return;
		}
		if (FREE_PTR > -1)
		{
			_ptr = FREE[FREE_PTR--];
		}
		else
		{
			_ptr = REGISTER_PTR++;
		}
	}

public:
	__NJS_TYPE type;
	int _ptr = -1;

	inline __NJS_VAL get() const
	{
		return REGISTER[_ptr];
	}

	__NJS_VAR()
	{
		setPtr();
		type = __NJS_UNDEFINED;
		REGISTER[_ptr].i = 0;
	}

	~__NJS_VAR()
	{
		if (type == __NJS_OBJECT)
		{
			REGISTER[_ptr].o->Delete();
		}
		else if (type == __NJS_STRING)
		{
			REGISTER[_ptr].s->Delete();
		}
		else if (type == __NJS_FUNCTION)
		{
			REGISTER[_ptr].f->Delete();
		}
		else if (type == __NJS_ARRAY)
		{
			REGISTER[_ptr].a->Delete();
		}
		else if (type == __NJS_NATIVE)
		{
			REGISTER[_ptr].n->Delete();
		}
		FREE[++FREE_PTR] = _ptr;
	}

	/**/
	__NJS_VAR(__NJS_VAR const &_v)
	{
		setPtr();
		type = _v.type;

		if (_v.type == __NJS_OBJECT)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].o->cnt++;
		}
		else if (_v.type == __NJS_STRING)
		{

			REGISTER[_ptr].s = new __NJS_Class_String(REGISTER[_v._ptr].s->__NJS_VALUE);
		}
		else if (_v.type == __NJS_FUNCTION)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].f->cnt++;
		}
		else if (_v.type == __NJS_ARRAY)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].a->cnt++;
		}
		else if (_v.type == __NJS_NATIVE)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].n->cnt++;
		}
		else
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
		}
	}
	/**/

	/*** CONSTRUCTOR ***/

	__NJS_VAR(__NJS_TYPE _type, int _value)
	{
		setPtr();
		this->type = _type;
		REGISTER[_ptr].i = _value;
	}

	__NJS_VAR(int _value)
	{
		setPtr();
		this->type = __NJS_NUMBER;
		REGISTER[_ptr].i = _value;
	}

	__NJS_VAR(double _value)
	{
		setPtr();
		this->type = __NJS_DOUBLE;
		REGISTER[_ptr].d = _value;
	}

	__NJS_VAR(char *_value)
	{
		setPtr();
		type = __NJS_STRING;
		REGISTER[_ptr].s = new __NJS_Class_String(_value);
	}

	__NJS_VAR(string _value)
	{
		setPtr();
		type = __NJS_STRING;
		REGISTER[_ptr].s = new __NJS_Class_String(_value);
	}

	__NJS_VAR(const char *_value)
	{
		setPtr();
		type = __NJS_STRING;
		REGISTER[_ptr].s = new __NJS_Class_String(_value);
	}

	__NJS_VAR(__NJS_Class_Array *_value)
	{
		setPtr();
		type = __NJS_ARRAY;
		REGISTER[_ptr].a = _value;
	}
	__NJS_VAR(__NJS_Class_Object *_value)
	{
		setPtr();
		type = __NJS_OBJECT;
		REGISTER[_ptr].o = _value;
	}
	__NJS_VAR(__NJS_Class_Native *_value)
	{
		setPtr();
		type = __NJS_NATIVE;
		REGISTER[_ptr].n = _value;
	}
	__NJS_VAR(__NJS_TYPE _type, void *_value)
	{
		setPtr();
		type = _type;
		REGISTER[_ptr].f = new __NJS_Class_Function(_value);
	}

	__NJS_VAR(function<__NJS_VAR(vector<var>)> &_value)
	{
		setPtr();
		type = __NJS_FUNCTION;
		REGISTER[_ptr].f = new __NJS_Class_Function(&_value);
	}

	/*** VARIADIC LAMBDAS ***/
	template <class... Args>
	__NJS_VAR(function<__NJS_VAR(Args...)> &_value)
	{
		setPtr();
		type = __NJS_FUNCTION;
		REGISTER[_ptr].f = new __NJS_Class_Function(&_value);
	}
	/*** END VARIADIC LAMBDAS ***/

	/*** END CONSTRUCTOR ***/

	/*** OPERATOR ***/
	__NJS_VAR operator=(const __NJS_VAR &_v)
	{
		if (type == __NJS_OBJECT)
			REGISTER[_ptr].o->Delete();
		else if (type == __NJS_STRING)
			REGISTER[_ptr].s->Delete();
		else if (type == __NJS_FUNCTION)
			REGISTER[_ptr].f->Delete();
		else if (type == __NJS_ARRAY)
			REGISTER[_ptr].a->Delete();
		else if (type == __NJS_NATIVE)
			REGISTER[_ptr].n->Delete();

		type = _v.type;
		;
		if (_v.type == __NJS_OBJECT)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].o->cnt++;
		}
		else if (_v.type == __NJS_STRING)
		{
			REGISTER[_ptr].s = new __NJS_Class_String((string)_v);
		}
		else if (_v.type == __NJS_FUNCTION)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].f->cnt++;
		}
		else if (_v.type == __NJS_ARRAY)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].a->cnt++;
		}
		else if (_v.type == __NJS_NATIVE)
		{
			REGISTER[_ptr] = REGISTER[_v._ptr];
			REGISTER[_ptr].n->cnt++;
		}
		else
			REGISTER[_ptr] = REGISTER[_v._ptr];

		return *this;
	}

	/// Unary operators
	__NJS_VAR operator+()
	{
		if (type == __NJS_NUMBER || type == __NJS_DOUBLE)
			return *this;
		else
			return (double)*this;
	}
	__NJS_VAR operator-()
	{
		if (type == __NJS_NUMBER)
			return -(int)*this;
		else
			return -(double)*this;
	}
	__NJS_VAR operator!() { return !(bool)*this; };

	/// Logical operators
	__NJS_VAR operator&&(const __NJS_VAR &_v1) { return (bool)*this && (bool)_v1; }
	__NJS_VAR operator||(const __NJS_VAR &_v1) { return (bool)*this || (bool)_v1; }

	/// Arithmetic operators
	__NJS_VAR operator+(const __NJS_VAR &_v1)
	{
		if (type == __NJS_STRING || type == __NJS_ARRAY || type == __NJS_OBJECT || _v1.type == __NJS_STRING)
			return __NJS_Concat_To_Str((string) * this, (string)_v1);
		else if (type == __NJS_NUMBER)
			return __NJS_VAR((int)*this + (int)_v1);
		else if (type == __NJS_DOUBLE)
			return __NJS_VAR((double)*this + (double)_v1);
		else return __NJS_VAR();
	}
	__NJS_VAR operator+(const char _v1[])
	{
		return __NJS_Concat_To_Str((string)*this, _v1);
	}
	__NJS_VAR operator+=(const __NJS_VAR &_v1)
	{
		if(type == __NJS_NUMBER) 
			REGISTER[_ptr].i += (int)_v1;
		else if(type == __NJS_DOUBLE) 
			REGISTER[_ptr].d += (double)_v1;
		else if(type == __NJS_STRING) 
			REGISTER[_ptr].s->__NJS_VALUE += (string)_v1;
		else 
		{
			string _s = (string)*this;
			type = __NJS_STRING;
			REGISTER[_ptr].s = new __NJS_Class_String("");
			REGISTER[_ptr].s->__NJS_VALUE += _s + (string)_v1;
		}
		return *this;
	}
	__NJS_VAR operator-(const __NJS_VAR &_v1)
	{
		if (type == __NJS_NUMBER )
			return __NJS_VAR((int)*this - (int)_v1);
		else if (type == __NJS_DOUBLE )
			return __NJS_VAR((double)*this - (double)_v1);
		else return "NaN";
	}
	__NJS_VAR operator-=(const __NJS_VAR &_v1)
	{
		if(type == __NJS_NUMBER && _v1.type == __NJS_NUMBER) 
			REGISTER[_ptr].i -= (int)_v1;
		else if(type == __NJS_NUMBER && _v1.type == __NJS_DOUBLE) 
			REGISTER[_ptr].i -= (double)_v1;
		else if(type == __NJS_DOUBLE && _v1.type == __NJS_NUMBER) 
			REGISTER[_ptr].d -= (int)_v1;
		else if(type == __NJS_DOUBLE && _v1.type == __NJS_DOUBLE) 
			REGISTER[_ptr].d -= (double)_v1;
		else 
		{
			type = __NJS_NAN;
			REGISTER[_ptr].s = new __NJS_Class_String("NaN");
		}
		return *this;
	}
	__NJS_VAR operator*(const __NJS_VAR &_v1)
	{
		if(type == __NJS_NUMBER) 
			return REGISTER[_ptr].i * (int)_v1;
		else if(type == __NJS_DOUBLE) 
			return REGISTER[_ptr].d * (double)_v1;
		return __NJS_VAR();
	}
	__NJS_VAR operator*=(const __NJS_VAR &_v1)
	{
		if(type == __NJS_NUMBER) 
			REGISTER[_ptr].i *= (int)_v1;
		else if(type == __NJS_DOUBLE) 
			REGISTER[_ptr].d *= (double)_v1;
		return __NJS_VAR();
	}
	__NJS_VAR operator/(const __NJS_VAR &_v1)
	{
		if (type == __NJS_NUMBER)
			return REGISTER[_ptr].i / (int)_v1;
		else if (type == __NJS_DOUBLE)
			return REGISTER[_ptr].d / (double)_v1;
		return __NJS_VAR();
	}
	__NJS_VAR operator/=(const __NJS_VAR &_v1)
	{
		if(type == __NJS_NUMBER) 
			REGISTER[_ptr].i /= (int)_v1;
		else if(type == __NJS_DOUBLE) 
			REGISTER[_ptr].d /= (double)_v1.get().d;
		return __NJS_VAR();
	}
	__NJS_VAR operator%(const __NJS_VAR &_v1)
	{
		if (type == __NJS_NUMBER && _v1.type == __NJS_NUMBER)
			return REGISTER[_ptr].i % (int)_v1;
		else
			return remainder(REGISTER[_ptr].d, (double)_v1);
	}
	__NJS_VAR operator%=(const __NJS_VAR &_v1)
	{
		if (type == __NJS_NUMBER && _v1.type == __NJS_NUMBER)
		{
			REGISTER[_ptr].i %= (int)_v1;
		}
		else
		{
			type = __NJS_DOUBLE;
			REGISTER[_ptr].d = remainder((double)*this, (double)_v1);
		}
		return *this;
	}
	// TODO: "**" and "**=" operators
	__NJS_VAR operator++(const int _v1)
	{
		if (type == __NJS_NUMBER)
		{
			REGISTER[_ptr].i++;
		}
		else if (type == __NJS_DOUBLE)
		{
			REGISTER[_ptr].d++;
		}
		else
		{
			type = __NJS_DOUBLE;
			REGISTER[_ptr].d = (double)*this;
		}
		return *this;
	}
	__NJS_VAR operator--(const int _v1)
	{
		if (type == __NJS_NUMBER)
			REGISTER[_ptr].i--;
		else if (type == __NJS_DOUBLE)
			REGISTER[_ptr].d--;
		else
		{
			type = __NJS_DOUBLE;
			REGISTER[_ptr].d = (double)*this;
		}
		return *this;
	}

	/// Comparison operators
	__NJS_VAR operator==(const __NJS_VAR &_v1)
	{
		if (type == _v1.type)
		{
			switch (type)
			{
			case __NJS_NUMBER:
				return __NJS_Create_Boolean(REGISTER[_ptr].i == (int)_v1);
			case __NJS_DOUBLE:
				return __NJS_Create_Boolean(REGISTER[_ptr].d == (double)_v1);
			//case __NJS_BIGNUMBER: return __NJS_VAR((long)*this == (long)_v1);
			case __NJS_BOOLEAN:
				return __NJS_Create_Boolean(REGISTER[_ptr].b == (bool)_v1);
			case __NJS_STRING:
				return __NJS_Create_Boolean((REGISTER[_ptr].s->__NJS_VALUE).compare((string)_v1) == 0);
			case __NJS_INFINITY:
			case __NJS_NULL:
			case __NJS_UNDEFINED:
				return __NJS_Create_Boolean(true);
			case __NJS_ARRAY:
			case __NJS_NATIVE:
			case __NJS_FUNCTION:
			case __NJS_OBJECT:
			case __NJS_NAN:
				return __NJS_Create_Boolean(false);
			}
		}
		else
		{
			if (type == __NJS_STRING || _v1.type == __NJS_STRING)
			{
				return __NJS_Create_Boolean((string) * this == (string)_v1);
			}
			else
				return __NJS_Create_Boolean((double)*this == (double)_v1);
		}
	}
	// === emulated with __NJS_EQUAL_VALUE_AND_TYPE
	__NJS_VAR operator!=(const __NJS_VAR &_v1)
	{
		return !(*this == _v1);
	}
	
	// !== emulated with __NJS_NOT_EQUAL_VALUE_AND_TYPE
	__NJS_VAR operator<(const __NJS_VAR &_v1)
	{
		if (type == _v1.type && type == __NJS_NUMBER)
			return (int)*this < (int)_v1;
		else
			return (double)*this < (double)_v1;
	}
	__NJS_VAR operator<=(const __NJS_VAR &_v1)
	{
		if (type == _v1.type && type == __NJS_NUMBER)
			return (int)*this <= (int)_v1;
		else
			return (double)*this <= (double)_v1;
	}
	__NJS_VAR operator>(const __NJS_VAR &_v1)
	{
		if (type == _v1.type && type == __NJS_NUMBER)
			return (int)*this > (int)_v1;
		else
			return (double)*this > (double)_v1;
	}
	__NJS_VAR operator>=(const __NJS_VAR &_v1)
	{
		if (type == _v1.type && type == __NJS_NUMBER)
			return (int)*this >= (int)_v1;
		else
			return (double)*this >= (double)_v1;
	}

	/// Bitwise operators
	__NJS_VAR operator&(const __NJS_VAR &_v1) { return (int)*this & (int)_v1; }
	__NJS_VAR operator&=(const __NJS_VAR &_v1)
	{
		type = __NJS_NUMBER;
		REGISTER[_ptr].i = (int)*this & (int)_v1;
		return *this;
	}
	__NJS_VAR operator|(const __NJS_VAR &_v1) { return (int)*this | (int)_v1; }
	__NJS_VAR operator|=(const __NJS_VAR &_v1)
	{
		type = __NJS_NUMBER;
		REGISTER[_ptr].i = (int)*this | (int)_v1;
		return *this;
	}
	__NJS_VAR operator^(const __NJS_VAR &_v1) { return (int)*this ^ (int)_v1; }
	__NJS_VAR operator^=(const __NJS_VAR &_v1)
	{
		type = __NJS_NUMBER;
		REGISTER[_ptr].i = (int)*this ^ (int)_v1;
		return *this;
	}
	__NJS_VAR operator~() { return ~(int)*this; }
	__NJS_VAR operator>>(const __NJS_VAR &_v1) { return (int)*this >> (int)_v1; }
	__NJS_VAR operator>>=(const __NJS_VAR &_v1)
	{
		type = __NJS_NUMBER;
		REGISTER[_ptr].i = (int)*this >> (int)_v1;
		return *this;
	}
	__NJS_VAR operator<<(const __NJS_VAR &_v1) { return (int)*this << (int)_v1; }
	__NJS_VAR operator<<=(const __NJS_VAR &_v1)
	{
		type = __NJS_NUMBER;
		REGISTER[_ptr].i = (int)*this << (int)_v1;
		return *this;
	}
	// TODO: ">>>" and ">>>=" operator support

	explicit operator int() const
	{
		switch (type)
		{
		case __NJS_NUMBER:
			return this->get().i;
		case __NJS_DOUBLE:
			return static_cast<int>(this->get().d);
		//case __NJS_BIGNUMBER: return static_cast<int>(this->get().l);
		case __NJS_BOOLEAN:
			return static_cast<int>(this->get().b);
		case __NJS_STRING:
			return strtol(this->get().s->__NJS_VALUE.c_str(), nullptr, 10);
		case __NJS_ARRAY:
			if (this->get().a->__NJS_VALUE.size() != 1)
				return 0;
			return static_cast<int>(this->get().a->__NJS_VALUE[0]);
		case __NJS_NATIVE:
		case __NJS_FUNCTION:
		case __NJS_OBJECT:
		case __NJS_INFINITY:
		case __NJS_NAN:
		case __NJS_NULL:
		case __NJS_UNDEFINED:
			return 0;
		}
	}

	explicit operator double() const
	{
		switch (type)
		{
		case __NJS_NUMBER:
			return static_cast<double>(this->get().i);
		case __NJS_DOUBLE:
			return this->get().d;
		//case __NJS_BIGNUMBER:
		//	return static_cast<double>(this->get().l);
		case __NJS_BOOLEAN:
			return static_cast<double>(this->get().b);
		case __NJS_STRING:
			return strtod(this->get().s->__NJS_VALUE.c_str(), nullptr);
		case __NJS_ARRAY:
			if (this->get().a->__NJS_VALUE.size() == 0)
				return 0;
			if (this->get().a->__NJS_VALUE.size() > 1)
				return NAN;
			return static_cast<double>(this->get().a->__NJS_VALUE[0]);
		case __NJS_NATIVE:
		case __NJS_FUNCTION:
		case __NJS_OBJECT:
		case __NJS_INFINITY:
		case __NJS_NAN:
		case __NJS_NULL:
		case __NJS_UNDEFINED:
			return 0;
		}
	}

	explicit operator bool() const
	{
		switch (type)
		{
		case __NJS_NUMBER:
			return static_cast<bool>(this->get().i);
		case __NJS_DOUBLE:
			return static_cast<bool>(this->get().d);
		//case __NJS_BIGNUMBER:
		//	return static_cast<bool>(this->get().l);
		case __NJS_BOOLEAN:
			return this->get().b;
		case __NJS_STRING:
			return static_cast<bool>(this->get().s->__NJS_VALUE.size());
		case __NJS_ARRAY:
		case __NJS_NATIVE:
		case __NJS_FUNCTION:
		case __NJS_OBJECT:
		case __NJS_INFINITY:
			return true;
		case __NJS_NAN:
		case __NJS_NULL:
		case __NJS_UNDEFINED:
			return false;
		}
	}

	explicit operator string() const
	{
		switch (type)
		{
		case __NJS_NUMBER:
			return to_string(this->get().i);
		case __NJS_DOUBLE:
			return to_string(this->get().d);
		//case __NJS_BIGNUMBER: return to_string(this->get().l);
		case __NJS_BOOLEAN:
			return (bool)*this ? "true" : "false";
		case __NJS_STRING:
			return this->get().s->__NJS_VALUE;
		case __NJS_ARRAY:
			return __NJS_Object_Stringify(*this, false).get().s->__NJS_VALUE;
		case __NJS_NATIVE:
			return "[native code]";
		case __NJS_FUNCTION:
			return "[Function]";
		case __NJS_OBJECT:
			return "[object Object]";
		case __NJS_INFINITY:
			return "Infinity";
		case __NJS_NAN:
			return "NaN";
		case __NJS_NULL:
			return "null";
		case __NJS_UNDEFINED:
			return "undefined";
		}
	}
};

namespace NECTAR
{
	__NJS_VAR null = __NJS_Create_Null();
	__NJS_VAR undefined = __NJS_VAR();
} // namespace NECTAR

/*** VARIADIC CALLS ***/
template <class... Args>
__NJS_VAR __NJS_Back_Var_Call_Function(__NJS_VAR _obj, Args... args)
{
	vector<var> _args = vector<var>{(var)args...};
	return (*static_cast<function<__NJS_VAR(vector<var>)> *>(_obj.get().f->__NJS_VALUE))(_args);
}

template <class... Args>
__NJS_VAR __NJS_Call_Function(__NJS_VAR _obj, Args... args)
{
	if (_obj.type != __NJS_FUNCTION)
	{
#ifndef __NJS_ARDUINO
		cout << "[!] Fatal error, object is not a function" << endl;
#endif
		exit(1);
	}
	return __NJS_Back_Var_Call_Function(_obj, (__NJS_VAR)(args)...);
}
/*** END VARIADIC CALLS ***/

/*** FIXED CALLS ***/
template <class... Args>
__NJS_VAR __NJS_Back_Var_Call_Fixed_Function(__NJS_VAR _obj, Args... args)
{
	return (*static_cast<function<__NJS_VAR(Args...)> *>(_obj.get().f->__NJS_VALUE))(args...);
}

template <class... Args>
__NJS_VAR __NJS_Call_Fixed_Function(__NJS_VAR _obj, Args... args)
{
	if (_obj.type != __NJS_FUNCTION)
	{
#ifndef __NJS_ARDUINO
		cout << "[!] Fatal error, object is not a function" << endl;
#endif
		exit(1);
	}
	return __NJS_Back_Var_Call_Fixed_Function(_obj, (__NJS_VAR)(args)...);
}
/*** END FIXED CALLS ***/

/*** FAST CALLS ***/
#define __NJS_Call_Fast_Function(_name, __VA_ARGS__) _name(__VA_ARGS__)
/*** END FAST CALLS ***/

__NJS_VAR __create_Array()
{
	__NJS_Class_Array *_a = new __NJS_Class_Array();
	return __NJS_VAR(__NJS_ARRAY, _a);
}

__NJS_VAR __NJS_Create_Array()
{
	__NJS_Class_Array *_a = new __NJS_Class_Array();
	return __NJS_VAR(_a);
}

int __NJS_Get_Int(__NJS_VAR _v)
{
	return _v.get().i;
}

const char *__NJS_Get_String(__NJS_VAR _v)
{
	if (_v.type != __NJS_STRING)
		return "";
	return _v.get().s->__NJS_VALUE.c_str();
}

__NJS_VAR __NJS_Typeof(__NJS_VAR _var)
{
	const char *_array[] = {"", "undefined", "number", "number", "object", "number", "boolean", "string", "native", "function", "array", "NaN", "number", "object"};
	return __NJS_Create_String(_array[_var.type]);
}

/*** ***/
__NJS_VAR __NJS_Object_Set(const char *_index, __NJS_VAR _value, vector<pair<const char *, __NJS_VAR>> *_obj)
{
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		if (strcmp(_index, (*_obj)[_i].first) == 0)
		{

			if (_value.type == __NJS_STRING)
			{
				REGISTER[(*_obj)[_i].second._ptr].s = new __NJS_Class_String((string)_value);
			}
			else
				REGISTER[(*_obj)[_i].second._ptr] = REGISTER[_value._ptr];

			return __NJS_VAR();
		}
	}

	(*_obj).push_back(pair<const char *, __NJS_VAR>(_index, _value));
	return __NJS_VAR();
}
/**/

__NJS_VAR __NJS_Object_Set(__NJS_VAR _index, __NJS_VAR _value, __NJS_VAR _array)
{
	if (_array.type == __NJS_ARRAY && _index.type == __NJS_NUMBER)
	{

		if (_array.get().a->__NJS_VALUE.size() <= _index.get().i)
		{
			_array.get().a->__NJS_VALUE.reserve(_index.get().i + 1);
			_array.get().a->__NJS_VALUE.resize(_index.get().i + 1);
		}

		_array.get().a->__NJS_VALUE.at(_index.get().i) = _value;

		__NJS_Object_Set("length", (int)_array.get().a->__NJS_VALUE.size(), &_array.get().a->__OBJECT);
		return __NJS_VAR();
	}
	else if (_array.type == __NJS_OBJECT || _array.type == __NJS_STRING || _array.type == __NJS_FUNCTION || _array.type == __NJS_ARRAY || _array.type == __NJS_NATIVE)
	{
		vector<pair<const char *, __NJS_VAR>> *_obj;
		if (_array.type == __NJS_OBJECT)
			_obj = &_array.get().o->__OBJECT;
		else if (_array.type == __NJS_ARRAY)
			_obj = &_array.get().a->__OBJECT;
		else if (_array.type == __NJS_STRING)
			_obj = &_array.get().s->__OBJECT;
		else if (_array.type == __NJS_FUNCTION)
			_obj = &_array.get().f->__OBJECT;
		else
			return __NJS_VAR();

		_index.get().s->cnt++;
		return __NJS_Object_Set(_index.get().s->__NJS_VALUE.c_str(), _value, _obj);
	}

	return __NJS_VAR();
}

__NJS_VAR __NJS_Object_Get(__NJS_VAR _index, __NJS_VAR _array)
{
	if (_array.type != __NJS_ARRAY && _array.type != __NJS_OBJECT && _array.type != __NJS_STRING && _array.type != __NJS_FUNCTION && _array.type != __NJS_NATIVE)
	{
		__NJS_RETURN_UNDEFINED;
	}
	if (_array.type == __NJS_ARRAY && _index.type == __NJS_NUMBER)
	{
		if (_index.get().i > _array.get().a->__NJS_VALUE.size())
		{
			__NJS_RETURN_UNDEFINED;
		}
		return _array.get().a->__NJS_VALUE[_index.get().i];
	}
	else
	{
		if (_index.type != __NJS_STRING)
		{
			__NJS_RETURN_UNDEFINED;
		}
		vector<pair<const char *, __NJS_VAR>> *_obj;
		if (_array.type == __NJS_OBJECT)
			_obj = &_array.get().o->__OBJECT;
		else if (_array.type == __NJS_ARRAY)
			_obj = &_array.get().a->__OBJECT;
		else if (_array.type == __NJS_STRING)
			_obj = &_array.get().s->__OBJECT;
		else if (_array.type == __NJS_FUNCTION)
			_obj = &_array.get().f->__OBJECT;
		else
		{
			__NJS_RETURN_UNDEFINED;
		}
		int _j = (*_obj).size();
		for (int _i = 0; _i < _j; _i++)
		{
			if (strcmp(_index.get().s->__NJS_VALUE.c_str(), (*_obj)[_i].first) == 0)
			{
				return (*_obj)[_i].second;
			}
		}
	}

	__NJS_RETURN_UNDEFINED;
}

__NJS_Class_String::__NJS_Class_String(string _value)
{
	cnt++;
	/*** toString ***/
	function<__NJS_VAR()> *__OBJ_TO___NJS_STRING = new function<__NJS_VAR()>([&]() { return __NJS_Create_String(this->__NJS_VALUE); });
	__NJS_VAR toString = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_STRING);
	__NJS_Object_Set("toString", toString, &this->__OBJECT);
	/*** end to string ***/

	/*** length ***/
	__NJS_Object_Set("length", __NJS_VAR((int)_value.size()), &this->__OBJECT);
	/*** end length ***/

	/*** split ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SPLIT = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);

		__NJS_VAR _arr = __NJS_Create_Array();
		char *_v = (char *)malloc(strlen(this->__NJS_VALUE.c_str()) + 1);
		strcpy(_v, this->__NJS_VALUE.c_str());
		char *delim = (char *)malloc(strlen(_needle.get().s->__NJS_VALUE.c_str()) + 1);
		strcpy(delim, _needle.get().s->__NJS_VALUE.c_str());

		char *ptr = strtok(_v, delim);
		int i = 0;
		char *_new;
		while (ptr != NULL)
		{
			_new = (char *)malloc(strlen(ptr) + 1);
			strcpy(_new, ptr);
			__NJS_Object_Set(i, _new, _arr);
			free(_new);
			ptr = strtok(NULL, delim);
			i++;
		}

		free(delim);
		return _arr;
	});

	__NJS_VAR __split = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_SPLIT);
	__NJS_Object_Set("split", __split, &this->__OBJECT);
	/*** end split ***/

#ifndef __NJS_ARDUINO
	/*** indexOf ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_INDEXOF = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __indexof = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_INDEXOF);

	__NJS_Object_Set("indexOf", __indexof, &this->__OBJECT);
	/*** end indexOf ***/

	/*** lastIndexOf ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_LASTINDEXOF = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find_last_of(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __lastindexof = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_LASTINDEXOF);

	__NJS_Object_Set("lastIndexOf", __lastindexof, &this->__OBJECT);
	/*** end lastIndexOf ***/

	/*** search ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SEARCH = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _needle;
		if (__NJS_VARARGS.size() > 0)
			_needle = __NJS_VARARGS[0];
		else
			return __NJS_VAR(-1);

		string::size_type loc = this->__NJS_VALUE.find(_needle.get().s->__NJS_VALUE, 0);
		if (loc != string::npos)
		{
			return __NJS_VAR((int)loc);
		}
		return __NJS_VAR(-1);
	});

	__NJS_VAR __search = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_SEARCH);

	__NJS_Object_Set("search", __search, &this->__OBJECT);
	/*** end search ***/

	/*** slice ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SLICE = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _start;
		var _end;
		if (__NJS_VARARGS.size() > 0)
			_start = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_end = __NJS_VARARGS[1];

		if (_end.type == __NJS_UNDEFINED)
			return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, string::npos));
		int _endIndex = _end.get().i - _start.get().i;
		return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, _endIndex));
	});

	__NJS_VAR __slice = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_SLICE);

	__NJS_Object_Set("slice", __slice, &this->__OBJECT);
	__NJS_Object_Set("substring", __slice, &this->__OBJECT);
	/*** end slice ***/

	/*** substr ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_SUBSTR = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _start;
		var _end;
		if (__NJS_VARARGS.size() > 0)
			_start = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_end = __NJS_VARARGS[1];

		if (_end.type == __NJS_UNDEFINED)
			return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, string::npos));
		return __NJS_VAR(this->__NJS_VALUE.substr(_start.get().i, _end.get().i));
	});

	__NJS_VAR __substr = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_SUBSTR);

	__NJS_Object_Set("substr", __substr, &this->__OBJECT);
	/*** end substr ***/

	/*** replace ***/
	function<__NJS_VAR(vector<var>)> *__OBJ_TO___NJS_REPLACE = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _search;
		var _replace;
		if (__NJS_VARARGS.size() > 0)
			_search = __NJS_VARARGS[0];
		else
			return __NJS_VAR(this->__NJS_VALUE);
		if (__NJS_VARARGS.size() > 1)
			_replace = __NJS_VARARGS[1];

		size_t start_pos = this->__NJS_VALUE.find(_search.get().s->__NJS_VALUE);
		if (start_pos == std::string::npos)
		{
			return var(this->__NJS_VALUE);
		}
		return var(this->__NJS_VALUE.replace(start_pos, _search.get().s->__NJS_VALUE.length(), _replace.get().s->__NJS_VALUE));
	});

	__NJS_VAR __replace = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_REPLACE);

	__NJS_Object_Set("replace", __replace, &this->__OBJECT);
	/*** end replace ***/
#endif

	__NJS_VALUE = _value;
}

__NJS_Class_Array::__NJS_Class_Array()
{
	cnt++;
	function<__NJS_VAR()> *__OBJ_TO___NJS_STRING = new function<__NJS_VAR()>([&]() { return __NJS_Create_String("Array"); });
	__NJS_VAR toString = __NJS_VAR(__NJS_FUNCTION, __OBJ_TO___NJS_STRING);
	__NJS_Object_Set("toString", toString, &this->__OBJECT);

	function<__NJS_VAR(vector<var>)> *__NJS_ARRAY_PUSH = new function<__NJS_VAR(vector<var>)>([&](vector<var> __NJS_VARARGS) {
		var _add;
		if (__NJS_VARARGS.size() > 0)
			_add = __NJS_VARARGS[0];
		else
			return (int)this->__NJS_VALUE.size();

		this->__NJS_VALUE.push_back(_add);
		__NJS_Object_Set("length", (int)this->__NJS_VALUE.size(), &this->__OBJECT);

		return (int)this->__NJS_VALUE.size();
	});
	__NJS_VAR arrayPush = __NJS_VAR(__NJS_FUNCTION, __NJS_ARRAY_PUSH);
	__NJS_Object_Set("push", arrayPush, &this->__OBJECT);

	__NJS_Object_Set("length", 0, &this->__OBJECT);
}

__NJS_Class_Object::__NJS_Class_Object()
{
	cnt++;
}

__NJS_Class_Function::__NJS_Class_Function(void *_f)
{
	cnt++;
	__NJS_VALUE = _f;
}

__NJS_Class_Native::__NJS_Class_Native(void *_n)
{
	cnt++;
	__NJS_VALUE = _n;
}

void __NJS_Class_String::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

void __NJS_Class_Array::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

void __NJS_Class_Object::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

void __NJS_Class_Function::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

void __NJS_Class_Native::Delete()
{
	this->cnt--;
	if (this->cnt < 1)
	{
		delete this;
	}
}

__NJS_VAR Array()
{
	vector<__NJS_VAR> *_arr = new vector<__NJS_VAR>();
	return __NJS_VAR(__NJS_ARRAY, _arr);
}

__NJS_VAR __NJS_Boolean_Result(__NJS_VAR _v)
{
	if (_v.type == __NJS_NUMBER)
		return _v.get().i;
	else if (_v.type == __NJS_BOOLEAN)
		return _v.get().b;
	else if (_v.type == __NJS_STRING)
	{
		if (strlen(_v.get().s->__NJS_VALUE.c_str()) > 0)
			return true;
		else
			return false;
	}
	else if (_v.type == __NJS_ARRAY)
		return true;
	else
		return false;
}

ostream &operator<<(ostream &os, const __NJS_VAR &_v)
{
	switch (_v.type)
	{
	case __NJS_BOOLEAN:
		if (_v.get().b)
			os << "true";
		else
			os << "false";
		break;
	case __NJS_NUMBER:
		os << _v.get().i;
		break;
	case __NJS_DOUBLE:
		os << _v.get().d;
		break;
	case __NJS_STRING:
		os << _v.get().s->__NJS_VALUE;
		break;
	case __NJS_OBJECT:
		os << __NJS_Object_Stringify(_v);
		break;
	case __NJS_ARRAY:
		os << __NJS_Object_Stringify(_v);
		break;
	case __NJS_NATIVE:
		os << "[Native]";
		break;
	case __NJS_NAN:
		os << "NaN";
		break;
	case __NJS_FUNCTION:
		os << "[Function]";
		break;
	case __NJS_INFINITY:
		os << "Infinity";
		break;
	case __NJS_NULL:
		os << "null";
		break;
	default:
		os << "undefined";
		break;
	}
	return os;
}

__NJS_VAR parseInt(__NJS_VAR _str)
{
	if (_str.type == __NJS_STRING)
	{
#ifdef __NJS_ARDUINO
		return __NJS_VAR();
#else
		return __NJS_Create_Number(stoi(_str.get().s->__NJS_VALUE));
#endif
	}
	else
		return __NJS_Create_Undefined();
}

__NJS_VAR __NJS_Log_Console(__NJS_VAR _var)
{
#ifdef __NJS_ARDUINO

#else
	cout << _var;
	cout << endl;
#endif

	return __NJS_VAR();
}

__NJS_VAR __NJS_Object_Keys(__NJS_VAR _var)
{
	if (_var.type != __NJS_OBJECT)
		return 0;
	var _res = __NJS_Create_Array();

	vector<pair<const char *, __NJS_VAR>> *_obj = &_var.get().o->__OBJECT;
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		__NJS_Object_Set(_i, (*_obj)[_i].first, _res);
	}
	return _res;
}

__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var)
{
	return __NJS_Object_Stringify(_var, true);
}
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var, bool _bracket)
{

	__NJS_TYPE _t = _var.type;

	if (_t == __NJS_UNDEFINED)
		return "undefined";
	else if (_t == __NJS_NAN)
		return "NaN";
	else if (_t == __NJS_NUMBER)
		return var("") + _var;
	else if (_t == __NJS_DOUBLE)
		return var("") + _var;
	else if (_t == __NJS_STRING)
		return var("\"") + _var + "\"";
	else if (_t == __NJS_FUNCTION)
		return var("\"") + "[Function]" + "\"";
	else if (_t == __NJS_ARRAY)
	{
		var _res = "";
		vector<__NJS_VAR> *_arr = &_var.get().a->__NJS_VALUE;
		if(_bracket) _res += "[";
		int j = (*_arr).size();
		for (int i = 0; i < j; i++)
		{
			if (i > 0)
				_res += ",";
			_res += __NJS_Object_Stringify((*_arr)[i], _bracket);
		}
		if(_bracket) _res += "]";

		return _res;
	}
	else if (_t == __NJS_OBJECT)
	{
		var _res = "";
		vector<pair<const char *, __NJS_VAR>> *_obj = &_var.get().o->__OBJECT;
		_res = "{";
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			if (_i > 0)
				_res += ", ";
			_res += var("\"") + (*_obj)[_i].first + "\"";
			_res += ":";
			_res += __NJS_Object_Stringify((*_obj)[_i].second);
		}
		_res += "}";
		return _res;
	}
	else
		return "";
}


__NJS_VAR __NJS_Create_Object()
{
	__NJS_Class_Object *_obj = new __NJS_Class_Object();
	return __NJS_VAR(_obj);
}

__NJS_VAR __NJS_CREATE_FUNCTION(void *_fn)
{
	return __NJS_VAR(__NJS_FUNCTION, _fn);
}

__NJS_VAR __NJS_Create_Native(void *_native)
{
	return __NJS_VAR(__NJS_UNDEFINED, _native);
}

/*
void* __NJS_Get_Function(__NJS_VAR _fn)
{
  return _fn.get().f;
}
*/

function<var(vector<var>)> *__NJS_Get_Function(__NJS_VAR _v)
{
	return (function<var(vector<var>)> *)_v.get().f->__NJS_VALUE;
}

void *__NJS_Get_Native(__NJS_VAR _native)
{
	return _native.get().f;
}

/*** REDIFINING STD OPERATORS ***/

template <typename t>
__NJS_VAR operator+(t _left, const __NJS_VAR &_right)
{
	return __NJS_VAR(_left) + _right;
}

template <typename t>
__NJS_VAR operator-(t _left, const __NJS_VAR &_right)
{
	return __NJS_VAR(_left) - _right;
}

template <typename t>
__NJS_VAR operator*(t _left, const __NJS_VAR &_right)
{
	return __NJS_VAR(_left) * _right;
}

template <typename t>
__NJS_VAR operator/(t _left, const __NJS_VAR &_right)
{
	return __NJS_VAR(_left) / _right;
}


/*** END REDIFINING STD OPERATORS ***/

__NJS_Create_Lambda(__IMPL_EVAL)
{
	__NJS_Log_Console("eval not implemented, return undefined");
	return var();
});
var eval = __NJS_Create_Function(__IMPL_EVAL);

function<__NJS_VAR(vector<var>)> *__NJS_IS_NAN = new function<__NJS_VAR(vector<var>)>([](vector<var> __NJS_VARARGS) {
	var _test;
	if (__NJS_VARARGS.size() > 0)
		_test = __NJS_VARARGS[0];
	else
		return __NJS_Create_Boolean(0);

	if (_test.type == __NJS_NUMBER || _test.type == __NJS_DOUBLE)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
});

__NJS_VAR isNaN = __NJS_VAR(__NJS_FUNCTION, __NJS_IS_NAN);

__NJS_VAR __NJS_EQUAL_VALUE_AND_TYPE(__NJS_VAR _left, __NJS_VAR _right)
{
	if (_left.type == _right.type && _left == _right)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
}

__NJS_VAR __NJS_NOT_EQUAL_VALUE_AND_TYPE(__NJS_VAR _left, __NJS_VAR _right)
{
	if (_left.type != _right.type || _left != _right)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
}
