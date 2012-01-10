// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region -plugin-arg-analyzer -analyzer-inline-call -plugin-arg-analyzer -cfg-add-initializers -verify %s
// XFAIL: *

class A {
  int x;
public:
  A();
  int getx() const {
    return x;
  }
};

A::A() : x(0) {
}

class B : public A {
  int y;
public:
  B();
};

B::B() {
}

void f() {
  B b;
  if (b.getx() != 0) {
    int *p = 0;
    *p = 0; // no-warning
  }
}
