// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-store=region -fblocks -verify %s

typedef void (^bptr)(void);

bptr bf(int j) {
  __block int i;
  const bptr &qq = ^{ i=0; }; // expected-note {{binding reference variable 'qq' here}}
  return qq; // expected-error {{returning block that lives on the local stack}}
}
