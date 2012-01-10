// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region -plugin-arg-analyzer -analyzer-inline-call -plugin-arg-analyzer -cfg-add-implicit-dtors -verify %s

class A {
public:
  ~A() { 
    int *x = 0;
    *x = 3; // expected-warning{{Dereference of null pointer}}
  }
};

int main() {
  A a;
}
