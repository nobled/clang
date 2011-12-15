//===--- CC1Options.h - Clang Static Analyzer Options Table -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_STATICANALYZER_OPTIONS_H
#define CLANG_STATICANALYZER_OPTIONS_H

namespace clang {
namespace driver {
  class OptTable;
}

namespace analyzeroptions {
  enum ID {
    OPT_INVALID = 0, // This is not an option ID.
#define OPTION(NAME, ID, KIND, GROUP, ALIAS, FLAGS, PARAM, \
               HELPTEXT, METAVAR) OPT_##ID,
#include "clang/StaticAnalyzer/AnalyzerOptions.inc"
    NumOptions
#undef OPTION
  };
}

  driver::OptTable *createAnalyzerOptTable();
}

#endif
