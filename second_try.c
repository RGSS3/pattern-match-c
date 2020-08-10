#pragma GCC diagnostic push "-Wpedantic"
#pragma GCC diagnostic ignored "-Wpedantic"

#define DF(type, name)          \
    union {                     \
        typeof(type) name;      \
        typeof(type) value;     \
    };

#define NEXT struct {           
#define END  } next;
#pragma GCC diagnostic pop "-Wpedantic" 

#define AT(M)                                                    \
    for (int _done = 0; !_done;  _done = 1)                      \
        for (typeof(M) _M = M; !_done; _done = 1)                \
            for (typeof(_M)* _current = &_M; !_done; _done = 1)  \

#define ENTER                                                                           \
    for (int _done = 0; !_done;  _done = 1)                                             \
        for (typeof(_current)  _old =  _current; !_done; _done = 1)                     \
            for (typeof(_old->value) *_current = &_old->value; !_done; _done = 1)       \
                                                                                                                             

#define THEN                                                                            \
    for (int _done = 0; !_done;  _done = 1)                                             \
        for (typeof(_current) _old =  _current; !_done; _done = 1)                      \
            for (typeof(_old->next) *_current = &_old->next; !_done; _done = 1)         \

#define GET(e) do { e = _current->value; } while(0)

struct Point {
         DF(int, x)
    NEXT DF(int, y) END
};

struct Line {
         DF(struct Point, p1)
    NEXT DF(struct Point, p2) END
};

struct Vector3 {
         DF(int, x)
    NEXT DF(int, y) 
    NEXT DF(int, z) END
                    END
};

struct TwoLine {
         DF(struct Line, l1)
    NEXT DF(struct Line, l2) END
};


int printf(const char *, ...);
int main () {
    struct Point r = {{3}, {{5}}};
    int x, y;
    AT(r) {
       GET(x);
       THEN GET(y);
    }
    printf("%d %d\n", x, y);
    struct Vector3 v = {{4}, {{5}, {{6}}}};
    int z;
    AT(v) {
        GET(x);
        THEN {
            GET(y);
            THEN GET(z);
        }
    };
    printf("%d %d %d\n", x, y, z);
    struct TwoLine q;
    q.l1.p1.x = 8; q.l1.p1.next.y = 7; q.l1.next.p2.x = 6; q.l1.next.p2.next.y = 5;
    q.next.l2.p1.x = 4; q.next.l2.p1.next.y = 3; q.next.l2.next.p2.x = 2; q.next.l2.next.p2.next.y = 1;
    int a, b, c, d, e, f, g, h;
    AT(q) {
        ENTER {
            ENTER {
               GET(a);
               THEN GET(b);
            }
            THEN ENTER {
               GET(c);
               THEN GET(d);
            }
        }
                                                                                                                      
        THEN ENTER {
            ENTER {
               GET(e);
               THEN GET(f);
            }
            THEN ENTER {
               GET(g);
               THEN GET(h);
            }
        }
    };
    printf("%d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h);
}
