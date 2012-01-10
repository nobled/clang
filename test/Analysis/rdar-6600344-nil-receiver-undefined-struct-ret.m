// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core,experimental.core -plugin-arg-analyzer -analyzer-constraints=basic -plugin-arg-analyzer -analyzer-store=region %s -verify

typedef struct Foo { int x; } Bar;

@interface MyClass {}
- (Bar)foo;
@end
@implementation MyClass
- (Bar)foo { 
  struct Foo f = { 0 };
  return f;
}
@end

void createFoo() {
  MyClass *obj = 0;  
  Bar f = [obj foo]; // no-warning
}

void createFoo2() {
  MyClass *obj = 0;  
  [obj foo]; // no-warning
  Bar f = [obj foo]; // no-warning
}

