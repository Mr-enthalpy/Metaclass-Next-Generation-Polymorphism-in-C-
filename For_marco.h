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

#define FOR_EACH_Add(macro, macro_other_args, x, ...) CAT(FOR_EACH_Add_, IS_EMPTY(__VA_ARGS__)) (macro, macro_other_args, x, __VA_ARGS__)
#define FOR_EACH_Add_0(macro, macro_other_args, x, ...) macro(x, macro_other_args), DEFER(FOR_EACH_Add_I)() (macro, macro_other_args, __VA_ARGS__)
#define FOR_EACH_Add_1(macro, macro_other_args, x, ...) macro(x, macro_other_args)
#define FOR_EACH_Add_I() FOR_EACH_Add

#define FOR_EACH_Add_NO_INTERVAL(macro, macro_other_args, x, ...) CAT(FOR_EACH_Add_NO_INTERVAL_, IS_EMPTY(__VA_ARGS__)) (macro, macro_other_args, x, __VA_ARGS__)
#define FOR_EACH_Add_NO_INTERVAL_0(macro, macro_other_args, x, ...) macro(x, macro_other_args) DEFER(FOR_EACH_Add_NO_INTERVAL_I)() (macro, macro_other_args, __VA_ARGS__)
#define FOR_EACH_Add_NO_INTERVAL_1(macro, macro_other_args, x, ...) macro(x, macro_other_args)
#define FOR_EACH_Add_NO_INTERVAL_I() FOR_EACH_Add_NO_INTERVAL

#define FOR_EACH(macro, x, ...) CAT(FOR_EACH_, IS_EMPTY(__VA_ARGS__)) (macro, x, __VA_ARGS__)
#define FOR_EACH_0(macro, x, ...) macro(x), DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
#define FOR_EACH_1(macro, x, ...) macro(x)
#define FOR_EACH_I() FOR_EACH

#define FOR_EACH_NO_INTERVAL(macro, x, ...) CAT(FOR_EACH_NO_INTERVAL_, IS_EMPTY(__VA_ARGS__)) (macro, x, __VA_ARGS__)
#define FOR_EACH_NO_INTERVAL_0(macro, x, ...) macro(x) DEFER(FOR_EACH_NO_INTERVAL_I)() (macro, __VA_ARGS__)
#define FOR_EACH_NO_INTERVAL_1(macro, x, ...) macro(x)
#define FOR_EACH_NO_INTERVAL_I() FOR_EACH_NO_INTERVAL

#define EXPAND0(...) __VA_ARGS__
#define EXPAND1(...) EXPAND0(EXPAND0(__VA_ARGS__))
#define EXPAND2(...) EXPAND1(EXPAND1(__VA_ARGS__))
#define EXPAND3(...) EXPAND2(EXPAND2(__VA_ARGS__))
#define EXPAND4(...) EXPAND3(EXPAND3(__VA_ARGS__))
#define EXPAND5(...) EXPAND4(EXPAND4(__VA_ARGS__))

#define NOEVAL0(...) __VA_ARGS__
#define NOEVAL1(...) NOEVAL0(NOEVAL0(__VA_ARGS__))
#define NOEVAL2(...) NOEVAL1(NOEVAL1(__VA_ARGS__))
#define NOEVAL3(...) NOEVAL2(NOEVAL2(__VA_ARGS__))
#define NOEVAL4(...) NOEVAL3(NOEVAL3(__VA_ARGS__))
#define NOEVAL5(...) NOEVAL4(NOEVAL4(__VA_ARGS__))

#define EVAL5(...) __VA_ARGS__
#define EVAL4(...) EVAL5(EVAL5(__VA_ARGS__))
#define EVAL3(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL2(...) EVAL3(EVAL3(__VA_ARGS__))
#define EVAL1(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL0(...) EVAL1(EVAL1(__VA_ARGS__))

#define EXEVAL(...)__VA_ARGS__
#define EXEVAL1(...) EXEVAL(EXEVAL(__VA_ARGS__))
#define EXEVAL2(...) EXEVAL1(EXEVAL1(__VA_ARGS__))
#define EXEVAL3(...) EXEVAL2(EXEVAL2(__VA_ARGS__))
#define EXEVAL4(...) EXEVAL3(EXEVAL3(__VA_ARGS__))
#define EXEVAL5(...) EXEVAL4(EXEVAL4(__VA_ARGS__))

#define FOREACH(F, ...) EVAL0(FOR_EACH(F, __VA_ARGS__))
#define FOREACH_ADD(F, macro_other_args, ...) EXPAND5(FOR_EACH_Add(F, macro_other_args, __VA_ARGS__))
#define FOREACH_NOINTERVAL(F, ...) NOEVAL5(FOR_EACH_NO_INTERVAL(F, __VA_ARGS__))
#define FOREACH_ADD_NOINTERVAL(F, macro_other_args, ...) EXEVAL5(FOR_EACH_Add_NO_INTERVAL(F, macro_other_args, __VA_ARGS__))

#define Impl(...) __VA_ARGS__
