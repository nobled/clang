// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-inline-call -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region -verify %s

// Test when entering f1(), we set the right AnalysisDeclContext to Environment.
// Otherwise, block-level expr '1 && a' would not be block-level.
int a;

void f1() {
  if (1 && a)
    return;
}

void f2() {
  f1();
}
