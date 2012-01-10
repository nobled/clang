// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core,experimental.core -triple i386-apple-darwin10 -fobjc-fragile-abi -plugin-arg-analyzer -analyzer-store=region %s

// Note that the target triple is important for this test case.  It specifies that we use the
// fragile Objective-C ABI.

@interface Foo {
  int x;
}
@end

@implementation Foo
static Foo* bar(Foo *p) {
  if (p->x)
   return ++p;  // This is only valid for the fragile ABI.

  return p;
}
@end
