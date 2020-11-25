/*** HELPERS ***/
#define __NJS_GET_String(_var) _var.get().s->value
//#define NJS::VAR NJS::VAR
//#define var NJS::VAR
//#define let NJS::VAR
//#define __NJS_CONST NJS::VAR
#define __NJS_Create_Boolean(_value) NJS::VAR(NJS::Enum::Type::Boolean, _value)
#define __NJS_Create_Number(_value) NJS::VAR(_value)
#define __NJS_Create_Function(_value) NJS::VAR(NJS::Enum::Type::Function, _value)
#define __NJS_Create_Undefined() NJS::VAR()
#define __NJS_Create_String(_value) NJS::VAR(_value)
#define __NJS_Create_Infinity() NJS::VAR(std::numeric_limits<double>::infinity)
#define __NJS_Create_Null() NJS::VAR(NJS::Enum::Type::Null, 0)
#define __NJS_Create_Struct(_value) NJS::VAR(new _value(), new NJS::Type::clean_struct([](void* _ptr){ delete (_value*)_ptr;}))
#define __NJS_Create_FixedArray(_length) NJS::VAR(new NJS::Class::FixedArray(_length))
#define __NJS_Create_Lambda(name) NJS::Type::function_t* name = new NJS::Type::function_t([](NJS::VAR __NJS_THIS, NJS::VAR* __NJS_VARARGS, int __NJS_VARLENGTH)
#define __NJS_Create_Ptr_Scoped_Anon(__CONTENT__) new NJS::Type::function_t([&](NJS::VAR __NJS_THIS, NJS::VAR* __NJS_VARARGS, int __NJS_VARLENGTH){ __CONTENT__ })
#define __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__) new NJS::Type::function_t([](NJS::VAR __NJS_THIS, NJS::VAR* __NJS_VARARGS, int __NJS_VARLENGTH){ __CONTENT__ })
#define __NJS_Create_Var_Scoped_Anon(__CONTENT__) NJS::VAR(NJS::Enum::Type::Function, __NJS_Create_Ptr_Scoped_Anon(__CONTENT__))
#define __NJS_Create_Var_Unscoped_Anon(__CONTENT__) NJS::VAR(NJS::Enum::Type::Function, __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__))
#define __NJS_Init_Int(_name, _value) int _name = _value
#define __NJS_Init_Double(_name, _value) double _name = _value
#define __NJS_Init_String(_name, _value) std::string _name = _value
#define __NJS_EXCEPTION_PARAMETER NJS::VAR &e
#define finally ;
#define __NJS_Boolean_TRUE __NJS_Create_Boolean(true)
#define __NJS_Boolean_FALSE __NJS_Create_Boolean(false)
#define __NJS_FAST_INT double
#define __NJS_CreateMethodToClass(_name, _fn) __NJS_Object_Set(_name, __NJS_Create_Var_Scoped_Anon( return _fn(__NJS_VARARGS, __NJS_VARLENGTH); ), &object);
#define __NJS_NEW(_fn) ((NJS::Class::Function*)_fn.data.ptr)->New
#define __NJS_SET_CONST(_var) _var.property.set(0,1)
#define __NJS_Access_Struct(_exp, _name) (*(_name*)((NJS::Class::Struct*)_exp.data.ptr)->value)

#ifdef __NJS__OBJECT_HASHMAP
#define __NJS_Method_Lazy_Loader(_name, _fn) \
if(_sview.compare(_name) == 0) { \
object[_str] = __NJS_Create_Var_Scoped_Anon( return _fn(__NJS_VARARGS, __NJS_VARLENGTH); ); \
object[_str].property.set(1,1); \
return object[_str];}
#define __NJS_Object_Lazy_Loader(_name) \
if(_sview.compare(_name) == 0) { \
object[_str] = __NJS_Create_Object(); \
object[_str].property.set(1,1); \
return object[_str];}
#else
#define __NJS_Method_Lazy_Loader(_name, _fn) \
if(_sview.compare(_name) == 0) { \
object.push_back(NJS::Type::pair_t(_str, __NJS_Create_Var_Scoped_Anon( return _fn(__NJS_VARARGS, __NJS_VARLENGTH); ))); \
object.back().second.property.set(1,1); \
return object.back().second;}
#define __NJS_Object_Lazy_Loader(_name) \
if(_sview.compare(_name) == 0) { \
object.push_back(NJS::Type::pair_t(_str, __NJS_Create_Object())); \
object.back().second.property.set(1,1); \
return object.back().second;}
#endif

#define __NJS_EXIT exit
/* END HELPERS */
