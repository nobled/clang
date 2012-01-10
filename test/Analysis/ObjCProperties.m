// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core,experimental.core -plugin-arg-analyzer -analyzer-store=region -plugin-arg-analyzer -analyzer-constraints=basic %s -verify
// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core,experimental.core -plugin-arg-analyzer -analyzer-store=region -plugin-arg-analyzer -analyzer-constraints=range %s -verify

// The point of this test cases is to exercise properties in the static
// analyzer

@interface MyClass {
@private
    id _X;
}
- (id)initWithY:(id)Y;
@property(copy, readwrite) id X;
@end

@implementation MyClass
@synthesize X = _X;
- (id)initWithY:(id)Y {
  self.X = Y;
  return self;
}
@end
