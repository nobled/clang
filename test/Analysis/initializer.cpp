// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region -plugin-arg-analyzer -cfg-add-initializers -verify %s

class A {
  int x;
public:
  A();
};

A::A() : x(0) {
  if (x != 0) {
    int *p = 0;
    *p = 0; // no-warning
  }
}
