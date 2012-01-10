// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-inline-call -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region -verify %s
// XFAIL: *

struct A {
  int x;
  A(int a) { x = a; }
  int getx() const { return x; }
};

void f1() {
  A x(3);
  if (x.getx() == 3) {
    int *p = 0;
    *p = 3;  // expected-warning{{Dereference of null pointer}}
  } else {
    int *p = 0;
    *p = 3;  // no-warning
  }
}

void f2() {
  const A &x = A(3);
  if (x.getx() == 3) {
    int *p = 0;
    *p = 3;  // expected-warning{{Dereference of null pointer}}
  } else {
    int *p = 0;
    *p = 3;  // no-warning
  }
}

void f3() {
  const A &x = (A)3;
  if (x.getx() == 3) {
    int *p = 0;
    *p = 3;  // expected-warning{{Dereference of null pointer}}
  } else {
    int *p = 0;
    *p = 3;  // no-warning
  }
}
