# EPoll wakeup tests

## Test cases

```
tN: Thread N
eN: EPoll N
sN: Socket N

et: Edge-triggered
lt: Level-triggered

ew: epoll_wait
p: poll
```

* Case 1:
```
            t0
             | (ew)
            e0
             | (lt)
            s0
```

* Case 2:
```
            t0
             | (ew)
            e0
             | (et)
            s0
```

* Case 3:
```
            t0
             | (ew)
            e0
      (lt) /  \ (lt)
         s0    s2
```

* Case 4:
```
            t0
             | (ew)
            e0
      (et) /  \ (et)
         s0    s2
```

* Case 5:
```
            t0
             | (p)
            e0
             | (lt)
            s0
```

* Case 6:
```
            t0
             | (p)
            e0
             | (et)
            s0
```

* Case 7:
```
            t0
             | (p)
            e0
      (lt) /  \ (lt)
         s0    s2
```

* Case 8:
```
            t0
             | (p)
            e0
      (et) /  \ (et)
         s0    s2
```

* Case 9:
```
         t0    t1
      (ew) \  / (ew)
            e0
             | (lt)
            s0
```

* Case 10:
```
         t0    t1
      (ew) \  / (ew)
            e0
             | (et)
            s0
```

* Case 11:
```
         t0    t1
      (ew) \  / (ew)
            e0
      (lt) /  \ (lt)
         s0    s2
```

* Case 12:
```
         t0    t1
      (ew) \  / (ew)
            e0
      (et) /  \ (et)
         s0    s2
```

* Case 13:
```
         t0    t1
      (ew) \  / (p)
            e0
             | (lt)
            s0
```

* Case 14:
```
         t0    t1
      (ew) \  / (p)
            e0
             | (et)
            s0
```

* Case 15:
```
         t0    t1
      (ew) \  / (p)
            e0
      (lt) /  \ (lt)
         s0    s2
```

* Case 16:
```
         t0    t1
      (ew) \  / (p)
            e0
      (et) /  \ (et)
         s0    s2
```

* Case 17:
```
            t0
             | (ew)
            e0
             | (lt)
            e1
             | (lt)
            s0
```

* Case 18:
```
            t0
             | (ew)
            e0
             | (lt)
            e1
             | (et)
            s0
```

* Case 19:
```
            t0
             | (ew)
            e0
             | (et)
            e1
             | (lt)
            s0
```

* Case 20:
```
            t0
             | (ew)
            e0
             | (et)
            e1
             | (et)
            s0
```

* Case 21:
```
            t0
             | (p)
            e0
             | (lt)
            e1
             | (lt)
            s0
```

* Case 22:
```
            t0
             | (p)
            e0
             | (lt)
            e1
             | (et)
            s0
```

* Case 23:
```
            t0
             | (p)
            e0
             | (et)
            e1
             | (lt)
            s0
```

* Case 24:
```
            t0
             | (p)
            e0
             | (et)
            e1
             | (et)
            s0
```

* Case 25:
```
         t0    t1
      (ew) \  / (ew)
            e0
             | (lt)
            e1
             | (lt)
            s0
```

* Case 26:
```
         t0    t1
      (ew) \  / (ew)
            e0
             | (lt)
            e1
             | (et)
            s0
```

* Case 27:
```
         t0    t1
      (ew) \  / (ew)
            e0
             | (et)
            e1
             | (lt)
            s0
```

* Case 28:
```
         t0    t1
      (ew) \  / (ew)
            e0
             | (et)
            e1
             | (et)
            s0
```

* Case 29:
```
         t0    t1
      (ew) \  / (p)
            e0
             | (lt)
            e1
             | (lt)
            s0
```

* Case 30:
```
         t0    t1
      (ew) \  / (p)
            e0
             | (lt)
            e1
             | (et)
            s0
```

* Case 31:
```
         t0    t1
      (ew) \  / (p)
            e0
             | (et)
            e1
             | (lt)
            s0
```

* Case 32:
```
         t0    t1
      (ew) \  / (p)
            e0
             | (et)
            e1
             | (et)
            s0
```

* Case 33:
```
         t0   t1
     (ew) |    | (ew)
         e0    |
      (lt) \  /
            e1
             | (lt)
            s0
```

* Case 34:
```
         t0   t1
     (ew) |    | (ew)
         e0    |
      (lt) \  /
             |
            e1
             | (et)
            s0
```

* Case 35:
```
         t0   t1
     (ew) |    | (ew)
         e0    |
      (et) \  /
            e1
             | (lt)
            s0
```

* Case 36:
```
         t0   t1
     (ew) |    | (ew)
         e0    |
      (et) \  /
            e1
             | (et)
            s0
```

* Case 37:
```
         t0   t1
     (ew) |    | (p)
         e0    |
      (lt) \  /
            e1
             | (lt)
            s0
```

* Case 38:
```
         t0   t1
     (ew) |    | (p)
         e0    |
      (lt) \  /
             |
            e1
             | (et)
            s0
```

* Case 39:
```
         t0   t1
     (ew) |    | (p)
         e0    |
      (et) \  /
            e1
             | (lt)
            s0
```

* Case 40:
```
         t0   t1
     (ew) |    | (p)
         e0    |
      (et) \  /
            e1
             | (et)
            s0
```

* Case 41:
```
         t0   t1
      (p) |    | (ew)
         e0    |
      (lt) \  /
            e1
             | (lt)
            s0
```

* Case 42:
```
         t0   t1
      (p) |    | (ew)
         e0    |
      (lt) \  /
             |
            e1
             | (et)
            s0
```

* Case 43:
```
         t0   t1
      (p) |    | (ew)
         e0    |
      (et) \  /
            e1
             | (lt)
            s0
```

* Case 44:
```
         t0   t1
      (p) |    | (ew)
         e0    |
      (et) \  /
            e1
             | (et)
            s0
```

* Case 45:
```
         t0   t1
      (p) |    | (p)
         e0    |
      (lt) \  /
            e1
             | (lt)
            s0
```

* Case 46:
```
         t0   t1
      (p) |    | (p)
         e0    |
      (lt) \  /
             |
            e1
             | (et)
            s0
```

* Case 47:
```
         t0   t1
      (p) |    | (p)
         e0    |
      (et) \  /
            e1
             | (lt)
            s0
```

* Case 48:
```
         t0   t1
      (p) |    | (p)
         e0    |
      (et) \  /
            e1
             | (et)
            s0
```

* Case 49:
```
            t0
             | (ew)
            e0
      (lt) /  \ (lt)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 50:
```
            t0
             | (ew)
            e0
      (et) /  \ (et)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 51:
```
            t0
             | (p)
            e0
      (lt) /  \ (lt)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 52:
```
            t0
             | (p)
            e0
      (et) /  \ (et)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 53:
```
         t0    t1
      (ew) \  / (ew)
            e0
      (lt) /  \ (lt)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 54:
```
         t0    t1
      (ew) \  / (ew)
            e0
      (et) /  \ (et)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 55:
```
         t0    t1
      (ew) \  / (p)
            e0
      (lt) /  \ (lt)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 56:
```
         t0    t1
      (ew) \  / (p)
            e0
      (et) /  \ (et)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 57:
```
         t0    t1
       (p) \  / (p)
            e0
      (lt) /  \ (lt)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

* Case 58:
```
         t0    t1
       (p) \  / (p)
            e0
      (et) /  \ (et)
         e1    e2
     (lt) |     | (lt)
         s0    s2
```

## How to run
```bash
make
```
