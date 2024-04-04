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
	if constexpr(requires{ name(*this, std::forward<Args>(args)...); } && std::same_as<transform_tuple_t<std::tuple<Impl type_in>>, std::tuple<std::remove_cvref_t<Args>...>>) \
	{ \
		return name(*this, std::forward<Args>(args)...); \
	}
#define F_Overload_0(args) Impl(F_Overload_0_Impl args)
#define F_Overload_1_Impl(name, type_in, type_out) \
	else if constexpr(requires{ name(*this, std::forward<Args>(args)...); } && std::same_as<transform_tuple_t<std::tuple<Impl type_in>>, std::tuple<std::remove_cvref_t<Args>...>>) \
	{ \
		return name(*this, std::forward<Args>(args)...); \
	}
#define F_Overload_1(args) Impl(F_Overload_1_Impl args)
#define Overload_0(x, ...) F_Overload_0(x) FOREACH_NO_INTERVAL(F_Overload_1, __VA_ARGS__)
#define Overload_1(x, ...) F_Overload_0(x) 
#define Overload(x, ...) CAT(Overload_, IS_EMPTY(__VA_ARGS__)) (x, __VA_ARGS__)

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

// 定义transform_tuple，用于处理std::tuple
template<typename Tuple>
struct transform_tuple;

// 部分特化，用于非空的std::tuple
template<typename... Args>
struct transform_tuple<std::tuple<Args...>> 
{
	using type = std::tuple<std::remove_cvref_t<Args>...>;
};

// 完全特化，用于空的std::tuple
template<>
struct transform_tuple<std::tuple<>> 
{
	using type = std::tuple<>;
};

template<typename Tuple>
using transform_tuple_t = typename transform_tuple<Tuple>::type;
