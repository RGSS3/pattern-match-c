#pragma GCC diagnostic push "-Wpedantic"
#pragma GCC diagnostic ignored "-Wpedantic"
#define DU(type, name, name2) \
    union {\
        type name;\
        type name2;\
    };
#pragma GCC diagnostic pop "-Wpedantic"
#define DF1(type, value) DU(type, value, _f1)
#define DF2(type, value) DU(type, value, _f2)
#define DF3(type, value) DU(type, value, _f3)

#define m(L, R)              \
    {                        \
      typeof(R) _current = R;\
      L;                     \
    }
    
#define L1(a)                               \
    {                                       \
        typeof(_current) *_old = &_current; \
        m(a, (_old->_f1));                  \
    }
#define L2(a, b)                            \
    {                                       \
        typeof(_current) *_old = &_current; \
        m(a, (_old->_f1));                  \
        m(b, (_old->_f2));                  \
    }
#define L3(a, b, c)                         \
    {                                       \
        typeof(_current) *_old = &_current; \
        m(a, (_old->_f1));                  \
        m(b, (_old->_f2));                  \
        m(c, (_old->_f3));                  \
    }
    
#define O(a)   a = _current;


struct Point {
    DF1(int, x)
    DF2(int, y)
};

struct Line {
    DF1(struct Point, a1)
    DF2(struct Point, a2)
};

struct TwoLine {
    DF1(struct Line, l1)
    DF2(struct Line, l2)
};

#define eval10(...) __VA_ARGS__
#define eval9(...) eval10(__VA_ARGS__)
#define eval8(...) eval9(__VA_ARGS__)
#define eval7(...) eval8(__VA_ARGS__)
#define eval6(...) eval7(__VA_ARGS__)
#define eval5(...) eval6(__VA_ARGS__)
#define eval4(...) eval5(__VA_ARGS__)
#define eval3(...) eval4(__VA_ARGS__)
#define eval2(...) eval3(__VA_ARGS__)
#define eval1(...) eval2(__VA_ARGS__)
#define eval(...)  eval1(__VA_ARGS__)

#include <stdio.h>
int main() {
    struct TwoLine q;
    q.l1.a1.x = 8; q.l1.a1.y = 7; q.l1.a2.x = 6; q.l1.a2.y = 5;
    q.l2.a1.x = 4; q.l2.a1.y = 3; q.l2.a2.x = 2; q.l2.a2.y = 1;
     
    int a, b, c, d, e, f, g, h;
    eval(m(
      L2(
          L2( 
            L2(O(a), O(b)), 
            L2(O(c), O(d))),
          L2( 
            L2(O(e), O(f)), 
            L2(O(g), O(h)))), q));
    printf("%d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h);
}




