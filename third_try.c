#define AT(M)                                                    \
    for (int _done = 0; !_done;  _done = 1)                      \
        for (typeof(M) _M = M; !_done; _done = 1)                \
            for (typeof(_M)* _current = &_M; !_done; _done = 1)  \

#define ENTER(f)                                                                    \
    for (int _done = 0; !_done;  _done = 1)                                         \
        for (typeof(_current)  _old =  _current; !_done; _done = 1)                 \
            for (typeof(_old->f) *_current = &_old->f; !_done; _done = 1)           \
                                                                                                                             

#define GET(f) ((_current) -> f)

struct Point    { int x, y; };
struct Line     { struct Point p1, p2; };
struct TwinLine { struct Line l1, l2;  };

int printf(const char *, ...);

int main(void) {
     struct TwinLine q = {{{1, 2}, {3, 4}}, 
                          {{5, 6}, {7, 8}}};
     int a, b, c, d, e, f, g, h;
     AT (q) {
         ENTER (l1) {
             ENTER (p1)
                 h = GET(x), g = GET(y);
             ENTER (p2)
                 f = GET(x), e = GET(y);
         }
         ENTER (l2) {
             ENTER (p1)
                 d = GET(x), c = GET(y);
             ENTER (p2)
                 b = GET(x), a = GET(y);
         }
     };
     printf("%d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h);
}
