Pattern Match in C
======================
Simple Pattern Matchings:


First Try
======================
This is not (C99) standard version, however, the warnings along with are suppressed by GCC pragma.


### Synopsis
```c

struct Point {
    DF1(int, x);
    DF2(int, y);
};

struct Line {
    DF1(struct Point, a1);
    DF2(struct Point, a2);
};

struct TwoLine {
    DF1(struct Line, l1);
    DF2(struct Line, l2);
};


int printf(const char *, ...);
int main() {
    struct TwoLine q;
    q.l1.a1.x = 8; q.l1.a1.y = 7; q.l1.a2.x = 6; q.l1.a2.y = 5;
    q.l2.a1.x = 4; q.l2.a1.y = 3; q.l2.a2.x = 2; q.l2.a2.y = 1;
     
    int a, b, c, d, e, f, g, h;
    MATCH(m(
        L2(
          L2( 
            L2(O(a), O(b)), 
            L2(O(c), O(d))),
          L2( 
            L2(O(e), O(f)), 
            L2(O(g), O(h)))), q));
    printf("%d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h);
}
```

Second Try
======================
This is not (C99) standard version, however, the warnings along with are suppressed by GCC pragma.


### Synopsis
```c
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

int main(void) {
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
```

