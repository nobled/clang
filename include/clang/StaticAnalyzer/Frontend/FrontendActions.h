//===-- FrontendActions.h - Useful Frontend Actions -------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_GR_FRONTENDACTIONS_H
#define LLVM_CLANG_GR_FRONTENDACTIONS_H

#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/AnalyzerOptions.h"

extern "C" void clang_LinkInStaticAnalyzerPlugin(void);

namespace clang {

namespace ento {

//===----------------------------------------------------------------------===//
// AST Consumer Actions
//===----------------------------------------------------------------------===//

class AnalysisAction : public PluginASTAction {
protected:
  AnalyzerOptions Opts;

  virtual bool BeginInvocation(CompilerInstance &CI);
  virtual ASTConsumer *CreateASTConsumer(CompilerInstance &CI,
                                         StringRef InFile);
public:
  virtual bool ParseArgs(const CompilerInstance &CI,
                         const std::vector<std::string> &arg);
  void toArgs(std::vector<std::string> &args);
};

void printCheckerHelp(raw_ostream &OS, ArrayRef<std::string> plugins);

} // end GR namespace

} // end namespace clang

#endif
