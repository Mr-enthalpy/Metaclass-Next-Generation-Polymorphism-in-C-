#include "For_marco.h"
#include <type_traits>
#include <tuple>
import ANY;

#define List_push_back(x, ...) CAT(List_pusk_back_, IS_EMPTY(__VA_ARGS__)) (x, __VA_ARGS__)
#define List_pusk_back_0(x, ...) Impl x, __VA_ARGS__
#define List_pusk_back_1(x, ...) Impl x

#define Expand(...) __VA_ARGS__
// 辅助宏，用于强制参数展开
#define F_Declare_Impl(name, type_in, type_out) \
    using CAT(name, _type) = type_out(List_push_back((Any&), Expand type_in)); \
    CAT(name, _type)* name = nullptr;
#define F_Declare(args) Impl(F_Declare_Impl args)

#define F_Init_Impl(name, type_in, type_out) \
	name(& Call<List_push_back((T), Expand type_in)>)
#define F_Init(args) Impl(F_Init_Impl args)

#define	Gener_Fun_Name(X) (CAT(F_,__COUNTER__), Impl X)

#define F_Overload_0_Impl(name, type_in, type_out) \
	if constexpr(requires{ name(*this, std::forward<Args>(args)...); } && std::same_as<transform_tuple_t<std::tuple<Impl type_in>>, std::tuple<Args...>>) \
	{ \
		return name(*this, std::forward<Args>(args)...); \
	}
#define F_Overload_0(args) Impl(F_Overload_0_Impl args)
#define F_Overload_1_Impl(name, type_in, type_out) \
	else if constexpr(requires{ name(*this, std::forward<Args>(args)...); } && std::same_as<transform_tuple_t<std::tuple<Impl type_in>>, std::tuple<Args...>>) \
	{ \
		return name(*this, std::forward<Args>(args)...); \
	}
#define F_Overload_1(args) Impl(F_Overload_1_Impl args)
#define Overload_0(x, ...) F_Overload_0(x) FOREACH_NO_INTERVAL(F_Overload_1, __VA_ARGS__)
#define Overload_1(x, ...) F_Overload_0(x) 
#define Overload(x, ...) CAT(Overload_, IS_EMPTY(__VA_ARGS__)) (x, __VA_ARGS__) //第一轮重载匹配，要求参数类型完全匹配

#define Overload_S_Impl(name, typein, typeout) \
	else if constexpr(requires{ name(*this, std::forward<Args>(args)...); } && std::same_as<transform_tuple_t<std::tuple<Impl typein>, remove_const_keep_ref>, std::tuple<remove_const_keep_ref_t<Args>...>>) \
	{ \
		return name(*this, std::forward<Args>(args)...); \
	}
#define Overload_S(args) Impl(Overload_S_Impl args) //第三轮重载匹配，放松条件至允许常量绑定到变量

#define Overload_T_Impl(name, typein, typeout) \
	else if constexpr(requires{ name(*this, std::forward<Args>(args)...); } && std::same_as<transform_tuple_t<std::tuple<Impl typein>, std::remove_cvref>, std::tuple<std::remove_cvref_t<Args>...>>) \
	{ \
		return name(*this, std::forward<Args>(args)...); \
	}
#define Overload_T(args) Impl(Overload_T_Impl args) //第三轮重载匹配，继续放松条件至允许T&&和T转发至T

#define Overload_F_Impl(name, typein, typeout) \
	else if constexpr(requires{ name(*this, std::forward<Args>(args)...); }) \
	{ \
		return name(*this, std::forward<Args>(args)...); \
	}
#define Overload_F(args) Impl(Overload_F_Impl args) //第四轮重载匹配，继续放松条件至允许隐式类型转换

#define Interface_Impl(Fun_name, ...) \
namespace Interface_detail \
{ \
	struct Interface_##Fun_name : virtual public Any \
	{ \
	private: \
		FOREACH_NO_INTERVAL(F_Declare, __VA_ARGS__) \
		template<typename T, typename ...Args> \
		static auto Call(Any& self, Args ...args) \
		{ \
			return Any_cast<T&>(self).Fun_name(std::forward<Args>(args)...); \
		}; \
	public: \
		Interface_##Fun_name() = default; \
		template<typename T> \
		Interface_##Fun_name(T& x) : Any(x), FOREACH(F_Init, __VA_ARGS__) {} \
		Interface_##Fun_name(const Interface_##Fun_name& other) = default; \
		Interface_##Fun_name& operator=(const Interface_##Fun_name& other) = default; \
		template <typename ...Args> \
		auto Fun_name(Args&& ...args) \
		{ \
			Overload(__VA_ARGS__) \
			FOREACH_NO_INTERVAL(Overload_S, __VA_ARGS__) \
			FOREACH_NO_INTERVAL(Overload_T, __VA_ARGS__) \
			FOREACH_NO_INTERVAL(Overload_F, __VA_ARGS__) \
			else return Interface_detail::no_matching_function(); \
		} \
	protected: \
		virtual ~Interface_##Fun_name() {} \
	}; \
};
#define Interface(Fun_name, ...) Interface_Impl(Fun_name, FOREACH(Gener_Fun_Name, __VA_ARGS__))

#define Make_X(X) Interface_##X(x)
#define Inter_name(X) Interface_detail::Interface_##X
#define Metaclass(class_name, ...) \
struct class_name final: FOREACH(Inter_name, __VA_ARGS__) \
{ \
    class_name() = default; \
    class_name(auto& x):  Any(x), FOREACH(Make_X, __VA_ARGS__) {} \
    class_name(const class_name& other) = default; \
    class_name& operator=(const class_name& other) = default; \
    ~ class_name() {} \
};

#define Fn(X,Y) (X, Y)


// 基本定义：对于非引用类型，直接移除 const 修饰符。
template<typename T>
struct remove_const_keep_ref {
    using type = typename std::remove_const<T>::type;
};

// 针对左值引用类型的特化：先移除引用，处理 const 后，再添加回引用。
template<typename T>
struct remove_const_keep_ref<T&> {
    using type = typename std::remove_const<T>::type&;
};

// 针对右值引用类型的特化：先移除引用，处理 const 后，再添加回右值引用。
template<typename T>
struct remove_const_keep_ref<T&&> {
    using type = typename std::remove_const<T>::type&&;
};

// 便捷使用的别名模板
template<typename T>
using remove_const_keep_ref_t = typename remove_const_keep_ref<T>::type;

template<typename T>
struct no_transform
{
	using type = T;
};

template<typename T>
using no_transform_t = typename no_transform<T>::type;

template<typename Tuple, template<typename> class Transformer>
struct transform_tuple;

// 部分特化，用于非空的std::tuple
template<template<typename> class Transformer, typename... Args>
struct transform_tuple<std::tuple<Args...>, Transformer> {
	using type = std::tuple<typename Transformer<Args>::type...>;
};

// 完全特化，用于空的std::tuple
template<template<typename> class Transformer>
struct transform_tuple<std::tuple<>, Transformer> {
	using type = std::tuple<>;
};

template<typename Tuple, template<typename> class Transformer = no_transform>
using transform_tuple_t = typename transform_tuple<Tuple, Transformer>::type;



namespace Interface_detail
{
	void no_matching_function() = delete;//匹配失败
}
