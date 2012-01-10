// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region -verify %s
char PR7218(char a) {
    char buf[2];
    buf[0] = a;
    return buf[1]; // expected-warning {{Undefined or garbage value returned to caller}}
}
