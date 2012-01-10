// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region %s

class A {
protected:
  int x;
};

class B : public A {
public:
  void f();
};

void B::f() {
  x = 3;
}
