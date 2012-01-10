// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core,osx.cocoa.RetainCount -plugin-arg-analyzer -analyzer-store=region -plugin-arg-analyzer -analyzer-constraints=basic -verify %s
// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core,osx.cocoa.RetainCount -plugin-arg-analyzer -analyzer-store=region -plugin-arg-analyzer -analyzer-constraints=range -verify %s

typedef struct CGColorSpace *CGColorSpaceRef;
extern CGColorSpaceRef CGColorSpaceCreateDeviceRGB(void);
extern CGColorSpaceRef CGColorSpaceRetain(CGColorSpaceRef space);
extern void CGColorSpaceRelease(CGColorSpaceRef space);

void f() {
  CGColorSpaceRef X = CGColorSpaceCreateDeviceRGB(); // expected-warning{{leak}}
  CGColorSpaceRetain(X);
}

void fb() {
  CGColorSpaceRef X = CGColorSpaceCreateDeviceRGB();
  CGColorSpaceRetain(X);
  CGColorSpaceRelease(X);
  CGColorSpaceRelease(X);  // no-warning
}
