// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=experimental.unix.Chroot -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region -verify %s

extern int chroot(const char* path);
extern int chdir(const char* path);

void foo(void) {
}

void f1(void) {
  chroot("/usr/local"); // root changed.
  foo(); // expected-warning {{No call of chdir("/") immediately after chroot}}
}

void f2(void) {
  chroot("/usr/local"); // root changed.
  chdir("/"); // enter the jail.
  foo(); // no-warning
}

void f3(void) {
  chroot("/usr/local"); // root changed.
  chdir("../"); // change working directory, still out of jail.
  foo(); // expected-warning {{No call of chdir("/") immediately after chroot}}
}
