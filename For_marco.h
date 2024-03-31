#pragma once

#define PRIMITIVE_CAT(x, y) x ## y
#define CAT(x, y) PRIMITIVE_CAT(x, y)

#define GET_SEC(x, n, ...) n
#define ATTER(atter) atter
#define CHECK(...) ATTER(GET_SEC(__VA_ARGS__,0))
#define PROBE(x) x, 1

#define IS_EMPTY(x, ...) CHECK(CAT(PRIMITIVE_CAT(IS_EMPTY_, x), 0))
#define IS_EMPTY_0 PROBE()

#define EMPTY()
#define DEFER(id) id EMPTY()

#define FOR_EACH(macro, x, ...) CAT(FOR_EACH_, IS_EMPTY(__VA_ARGS__)) (macro, x, __VA_ARGS__)
#define FOR_EACH_0(macro, x, ...) macro(x), DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
#define FOR_EACH_1(macro, x, ...) macro(x)
#define FOR_EACH_I() FOR_EACH

#define FOR_EACH_NO_INTERVAL(macro, x, ...) CAT(FOR_EACH_NO_INTERVAL_, IS_EMPTY(__VA_ARGS__)) (macro, x, __VA_ARGS__)
#define FOR_EACH_NO_INTERVAL_0(macro, x, ...) macro(x) DEFER(FOR_EACH_NO_INTERVAL_I)() (macro, __VA_ARGS__)
#define FOR_EACH_NO_INTERVAL_1(macro, x, ...) macro(x)
#define FOR_EACH_NO_INTERVAL_I() FOR_EACH_NO_INTERVAL

#define EVAL(...)  EVAL1(EVAL1(EVAL1(EVAL1(__VA_ARGS__))))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(EVAL2(__VA_ARGS__))))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(EVAL3(__VA_ARGS__))))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(EVAL4(__VA_ARGS__))))
#define EVAL4(...) Impl(Impl(Impl(Impl(__VA_ARGS__))))
#define Impl(...) __VA_ARGS__

#define FOREACH(F, ...) EVAL(FOR_EACH(F, __VA_ARGS__))
#define FOREACH_NO_INTERVAL(F, ...) EVAL(FOR_EACH_NO_INTERVAL(F, __VA_ARGS__))
