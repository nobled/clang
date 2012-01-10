// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-inline-call -plugin-arg-analyzer -analyzer-store -plugin-arg-analyzer region -verify %s

// Test parameter 'a' is registered to LiveVariables analysis data although it
// is not referenced in the function body. 
// Before processing 'return 1;', in RemoveDeadBindings(), we query the liveness
// of 'a', because we have a binding for it due to parameter passing.
int f1(int a) {
  return 1;
}

void f2() {
  int x;
  x = f1(1);
}
