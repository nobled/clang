// RUN: %clang_cc1 -std=c++11 -fsyntax-only -verify %s

int i = delete; // expected-error{{only functions}}
int j = default; // expected-error{{special member functions}}

int f() = delete, g; // expected-error{{standalone}}
int o, p() = delete; // expected-error{{standalone}}

struct foo {
  foo() = default;
  ~foo() = delete;
  void bar() = delete;
};

void baz() = delete;

struct quux {
  int quux() = default; // expected-error{{constructor cannot have a return type}} expected-error {{member 'quux' has the same name as its class}}
};
