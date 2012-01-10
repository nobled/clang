// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-store=region -verify %s

int f1() {
  int x = 0, y = 1;
  return x += y; // Should bind a location to 'x += y'. No crash.
}
