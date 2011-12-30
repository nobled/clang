//===--- ArgUtil.h - Common Argument Parsing Utilities ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_BASIC_ARG_UTIL_H_
#define CLANG_BASIC_ARG_UTIL_H_

#include "clang/Basic/LLVM.h"

namespace clang {
  /// ArgStringList - Type used for constructing argv lists for subprocesses.
  typedef SmallVector<const char*, 16> ArgStringList;
} // end namespace clang

#endif
