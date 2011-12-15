//===--- FrontendActions.cpp ----------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/StaticAnalyzer/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "AnalysisConsumer.h"
using namespace clang;
using namespace ento;

ASTConsumer *AnalysisAction::CreateASTConsumer(CompilerInstance &CI,
                                               StringRef InFile) {
  return CreateAnalysisConsumer(CI.getPreprocessor(),
                                CI.getFrontendOpts().OutputFile,
                                CI.getAnalyzerOpts(),
                                CI.getFrontendOpts().Plugins);
}

bool AnalysisAction::ParseArgs(const CompilerInstance &CI,
                               const std::vector<std::string> &args) {
  if (args.empty())
    return true;

  DiagnosticsEngine &D = CI.getDiagnostics();
  unsigned DiagID = D.getCustomDiagID(DiagnosticsEngine::Error,
    "ParseArgs() not implemented (" __FILE__ ")");
  D.Report(DiagID);

  return false; // error
}

static FrontendPluginRegistry::Add<AnalysisAction>
X("analyzer", "Run the static analyzer");
