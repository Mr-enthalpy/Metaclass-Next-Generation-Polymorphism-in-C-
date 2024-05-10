#include "For_marco.h"
#include <type_traits>
import ANY;

#define List_push_back(x, ...) CAT(List_pusk_back_, IS_EMPTY(__VA_ARGS__)) (x, __VA_ARGS__)
#define List_pusk_back_0(x, ...) Impl x, __VA_ARGS__
#define List_pusk_back_1(x, ...) Impl x

#define Expand(...) __VA_ARGS__

#define Expand_In_List_0_Impl(type, name) type name
#define Expand_In_List_0(...) Expand_In_List_0_Impl __VA_ARGS__
#define Expand_In_List_1(...)
#define Expand_In_List(...) CAT(Expand_In_List_, IS_EMPTY(__VA_ARGS__)) (__VA_ARGS__)

#define Expand_Args_List_0_Impl(type, name) std::forward<decltype(name)>(name)
#define Expand_Args_List_0(...) Expand_Args_List_0_Impl __VA_ARGS__
#define Expand_Args_List_1(...)
#define Expand_Args_List(...) CAT(Expand_Args_List_, IS_EMPTY(__VA_ARGS__)) (__VA_ARGS__)

#define F_Extend(x, name) (Impl name, CAT(F_,__COUNTER__), Impl x)
#define Fn_Impl(True_Name, Inside_Name, ...) \
	((template<typename T, typename ...Args> \
	static auto Inside_Name(void* self, Args ...args) \
	{ \
		return (*static_cast<std::decay_t<T>*>(self)).True_Name(std::forward<Args>(args)...); \
	} \
	template<typename ...Args> \
	auto True_Name() const;), \
    (FOREACH_ADD(F_Extend, (Inside_Name, True_Name), __VA_ARGS__)))
#define Fn(F_Name, ...) Fn_Impl(F_Name, CAT(F_Name,__COUNTER__), __VA_ARGS__)

#define Oper_Impl(oper, name, ...) \
	((template<typename T, typename Arg> \
	static auto name(void* self, Arg arg) \
	{ \
		return (*static_cast<std::decay_t<T>*>(self)) oper arg; \
	} \
	template<typename Arg> \
	auto operator oper() const;), \
	(FOREACH_ADD(F_Extend, (name, operator oper), __VA_ARGS__)))
#define Oper(oper, ...) Oper_Impl(oper, CAT(operator_,__COUNTER__), __VA_ARGS__)

#define Paren_Impl(name, ...) \
	((template<typename T, typename ...Args> \
	static auto name(void* self, Args ...args) \
	{ \
		return (*static_cast<std::decay_t<T>*>(self))(std::forward<Args>(args)...); \
	} \
	template<typename ...Args> \
	auto operator()() const; ),\
	(FOREACH_ADD(F_Extend, (name, operator()), __VA_ARGS__)))
#define Paren(...) Paren_Impl(CAT(operator_,__COUNTER__), __VA_ARGS__)

#define Bracket_Impl(name, ...) \
	((template<typename T, typename ...Args> \
	static auto name(void* self, Args ...args) \
	{ \
		return(*static_cast<std::decay_t<T>*>(self))[std::forward<Args>(args)...]; \
	} \
	template<typename ...Args> \
	auto operator[]() const;), \
	(FOREACH_ADD(F_Extend, (name, operator[]), __VA_ARGS__)))
#define Bracket(...) Bracket_Impl(CAT(operator_,__COUNTER__), __VA_ARGS__)

#define Gener_Warpper_Impl(warpper, override_set) Impl warpper
#define Gener_Warpper(X) Gener_Warpper_Impl X

#define Declare_Impl(inside_name, true_name, f_ptr, type_in, type_out) \
    using CAT(f_ptr, _type) = type_out(List_push_back((void*), Expand type_in)); \
    CAT(f_ptr, _type)* f_ptr = nullptr;
#define Declare(args, x) Declare_Impl args
#define Gener_Delcare_Impl(warpper, override_set) FOREACH_ADD_NOINTERVAL(Declare, x, Impl override_set)
#define Gener_Delcare(X) Gener_Delcare_Impl X

#define Init_Impl(inside_name, true_name, f_ptr, type_in, type_out) f_ptr(& inside_name<List_push_back((std::decay_t<T>), Expand type_in)>)
#define Init(args, x) Init_Impl args
#define Gener_Init_Impl(warpper, override_set) FOREACH_ADD(Init, x, Impl override_set)
#define Gener_Init(x) Gener_Init_Impl x

#define Invoke_Impl(inside_name, true_name, f_ptr, type_in, type_out) \
	type_out true_name(FOREACH(Expand_In_List, Impl type_in)) \
	{ \
		return f_ptr(List_push_back((static_cast<void*>(object)), FOREACH(Expand_Args_List, Impl type_in))); \
	}
#define Invoke(ags, x) Invoke_Impl ags

#define Args_Add_0_Impl(type, x) (type, CAT(Arg_, __COUNTER__))
#define Args_Add_0(...) FOREACH_ADD(Args_Add_0_Impl, x, __VA_ARGS__)
#define Args_Add_1(...)
#define Args_Add(...) CAT(Args_Add_, IS_EMPTY(__VA_ARGS__)) (__VA_ARGS__)
#define Gener_Args_Impl(inside_name, true_name, f_ptr, type_in, type_out) (inside_name, true_name, f_ptr,(Args_Add type_in), type_out)
#define Gener_Args(x) Gener_Args_Impl x
#define Gener_Invoke_Impl(warpper, override_set) FOREACH_ADD_NOINTERVAL(Invoke, x, FOREACH(Gener_Args, Impl override_set))
#define Gener_Invoke(...) Gener_Invoke_Impl __VA_ARGS__

#define Copy_Impl(inside_name, true_name, f_ptr, type_in, type_out) f_ptr(other.f_ptr)
#define Copy(x, y) Copy_Impl x 
#define Copy_ptr_Impl(warpper, override_set) FOREACH_ADD(Copy, x, Impl override_set)
#define Copy_Ptr(x) Copy_ptr_Impl x

#define Assign_Copy_Impl(inside_name, true_name, f_ptr, type_in, type_out) f_ptr = other.f_ptr
#define Assign_Copy(x, y) Assign_Copy_Impl x 
#define Assign_Copy_ptr_Impl(warpper, override_set) FOREACH_ADD(Assign_Copy, x, Impl override_set)
#define Assign_Copy_Ptr(x) Assign_Copy_ptr_Impl x

#define Assign_Init_Impl(inside_name, true_name, f_ptr, type_in, type_out) f_ptr = &inside_name<List_push_back((std::decay_t<T>), Expand type_in)>
#define Assign_Init(x, y) Assign_Init_Impl x 
#define Assign_Init_Ptr_Impl(warpper, override_set) FOREACH_ADD(Assign_Init, x, Impl override_set)
#define Assign_Init_Ptr(x) Assign_Init_Ptr_Impl x

#define Reflect_Impl(inside_name, true_name, f_ptr, type_in, type_out) \
	template<> \
	auto true_name<Impl type_in>() const \
	{ \
		return f_ptr; \
	}
#define Reflect(args, x) Reflect_Impl args
#define Gener_Reflect_Impl(warpper, override_set) FOREACH_ADD_NOINTERVAL(Reflect, x, Impl override_set)
#define Gener_Reflect(X) Gener_Reflect_Impl X

#define Ptr_Impl(inside_name, true_name, f_ptr, type_in, type_out) f_ptr(other.true_name<Impl type_in>())
#define Ptr(x, y) Ptr_Impl x
#define Reflect_Ptr_Impl(warpper, override_set) FOREACH_ADD(Ptr, x, Impl override_set)
#define Reflect_Ptr(X) Reflect_Ptr_Impl X

#define Assign_Ptr_Impl(inside_name, true_name, f_ptr, type_in, type_out) f_ptr = other.true_name<Impl type_in>()
#define Assign_Ptr(x, y) Assign_Ptr_Impl x
#define Assign_Reflect_Ptr_Impl(warpper, override_set) FOREACH_ADD(Assign_Ptr, x, Impl override_set)
#define Assign_Reflect_Ptr(X) Assign_Reflect_Ptr_Impl X

#define Interface(intername, ...) \
template <OwnerShip ownership> \
struct intername; \
\
template <> \
struct intername<OwnerShip::Owner> \
{ \
private: \
	using any = Any<OwnerShip::Owner>; \
	using swift = Any<OwnerShip::Owner>; \
	any object; \
    FOREACH_NOINTERVAL(Gener_Delcare, __VA_ARGS__) \
	friend struct intername<OwnerShip::Observer>; \
public: \
	FOREACH_NOINTERVAL(Gener_Warpper, __VA_ARGS__) \
	intername() = default; \
	template <typename T> \
		requires (!is_observer<T>) && (!is_owner<T>) \
	intername(T&& x) : object(std::forward<decltype(x)>(x)), FOREACH(Gener_Init, __VA_ARGS__) {} \
	intername(const intername& other) = default; \
	intername(intername&& other) = default; \
	template<typename T> \
		requires is_owner<T> && (!std::is_same_v<std::remove_cvref_t<T>, intername<OwnerShip::Owner>>) \
	intername(T&& other) : object(std::forward<decltype(other.object)>(other.object)), FOREACH(Reflect_Ptr, __VA_ARGS__) {} \
	intername& operator=(const intername& other) = default; \
	intername& operator=(intername&& other) = default; \
	template<typename T> \
		requires (!is_interface<T>) \
	intername& operator=(T&& other) \
	{ \
		object = std::forward<decltype(other)>(other), \
		FOREACH(Assign_Init_Ptr, __VA_ARGS__); \
		return *this; \
	} \
	template<typename T> \
		requires is_owner<T> && (!std::is_same_v<std::remove_cvref_t<T>, intername<OwnerShip::Owner>>) \
	intername& operator=(T&& other) \
	{ \
		object = std::forward<decltype(other.object)>(other.object), \
		FOREACH(Assign_Reflect_Ptr, __VA_ARGS__); \
		return *this; \
	} \
	FOREACH_NOINTERVAL(Gener_Invoke, __VA_ARGS__) \
	FOREACH_NOINTERVAL(Gener_Reflect, __VA_ARGS__) \
	~intername() {} \
};\
\
template <> \
struct intername<OwnerShip::Observer> \
{ \
private: \
	using any = Any<OwnerShip::Observer>; \
	using swift = Any<OwnerShip::Owner>; \
	any object; \
    FOREACH_NOINTERVAL(Gener_Delcare, __VA_ARGS__) \
public: \
	FOREACH_NOINTERVAL(Gener_Warpper, __VA_ARGS__) \
	intername() = default; \
	template <typename T> \
		requires (!is_observer<T>) && (!is_owner<T>) \
	intername(T& x) : object(x), FOREACH(Gener_Init, __VA_ARGS__) {} \
	template <typename T> \
		requires std::is_rvalue_reference_v<T&&> \
	intername(T&& x) = delete; \
	intername(const intername<OwnerShip::Owner>& other) : object(other.object), FOREACH(Copy_Ptr, __VA_ARGS__) {} \
    intername(intername<OwnerShip::Owner>&& other) = delete; \
	intername(const intername& other) = default; \
	intername(intername&& other) = delete; \
	template<typename T> \
		requires (is_observer<T> || is_owner<T>) && (!std::is_same_v<std::remove_cvref_t<T>, intername<OwnerShip::Observer>>) && (!std::is_same_v<std::remove_cvref_t<T>, intername<OwnerShip::Owner>>) \
	intername(T& other) : object(other.object), FOREACH(Reflect_Ptr, __VA_ARGS__) {} \
	template<typename T> \
		requires (!is_interface<T>) \
	intername& operator=(T& other) \
	{ \
		object.content = &other, \
		FOREACH(Assign_Init_Ptr, __VA_ARGS__); \
		return *this; \
	} \
	template<typename T> \
		requires (is_observer<T> || is_owner<T>) && (!std::is_same_v<std::remove_cvref_t<T>, intername<OwnerShip::Observer>>) && (!std::is_same_v<std::remove_cvref_t<T>, intername<OwnerShip::Owner>>) \
	intername& operator=(T& other) \
	{ \
		object.content = &other, \
		FOREACH(Assign_Reflect_Ptr, __VA_ARGS__); \
		return *this; \
	} \
	intername& operator=(const intername<OwnerShip::Owner>& other) \
	{ \
		object.content = static_cast<void*>(other.object), \
		FOREACH(Assign_Copy_Ptr, __VA_ARGS__); \
		return *this; \
	} \
	intername& operator=(const intername& other) = default; \
	intername& operator=(intername&& other) = delete; \
	FOREACH_NOINTERVAL(Gener_Invoke, __VA_ARGS__) \
	FOREACH_NOINTERVAL(Gener_Reflect, __VA_ARGS__) \
	~intername() {} \
};
