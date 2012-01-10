// RUN: %clang_cc1 -triple x86_64-apple-darwin10 -plugin analyzer -plugin-arg-analyzer -analyzer-checker=core -plugin-arg-analyzer -analyzer-store=region -plugin-arg-analyzer -analyzer-output=text -verify %s

// This file is for testing enhanced diagnostics produced by the default BugReporterVisitors.

int getPasswordAndItem()
{
  int err = 0;
  int *password; // expected-note {{Variable 'password' declared without an initial value}}
  if (password == 0) { // expected-warning {{The left operand of '==' is a garbage value}} // expected-note {{The left operand of '==' is a garbage value}}
    err = *password;
  }
  return err;
}
