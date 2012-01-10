// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core,experimental.core -plugin-arg-analyzer -analyzer-store=region -verify %s

void f(void) {
  void (*p)(void);
  p = f;
  p = &f;
  p();
  (*p)();
}

void g(void (*fp)(void));

void f2() {
  g(f);
}
