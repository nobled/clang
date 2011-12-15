//===----- AnalyzerOptions.cpp - Clang Static Analyzer Options Table ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/StaticAnalyzer/AnalyzerOptions.h"
#include "clang/Driver/Option.h"
#include "clang/Driver/OptTable.h"

using namespace clang;
using namespace clang::driver;
using namespace clang::driver::options; // XXX: shouldn't need this!
using namespace clang::analyzeroptions;

static const OptTable::Info AnalyzerInfoTable[] = {
#define OPTION(NAME, ID, KIND, GROUP, ALIAS, FLAGS, PARAM, \
               HELPTEXT, METAVAR)   \
  { NAME, HELPTEXT, METAVAR, Option::KIND##Class, PARAM, FLAGS, \
    OPT_##GROUP, OPT_##ALIAS },
#include "clang/StaticAnalyzer/AnalyzerOptions.inc"
};

namespace {

class AnalyzerOptTable : public driver::OptTable {
public:
  AnalyzerOptTable()
    : OptTable(AnalyzerInfoTable,
               sizeof(AnalyzerInfoTable) / sizeof(AnalyzerInfoTable[0])) {}
};

}

driver::OptTable *clang::createAnalyzerOptTable() {
  return new AnalyzerOptTable();
}
