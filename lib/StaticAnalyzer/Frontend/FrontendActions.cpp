//===--- FrontendActions.cpp ----------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Frontend/AnalyzerOptions.h"
#include "clang/StaticAnalyzer/Frontend/FrontendActions.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/Driver/Arg.h"
#include "clang/Driver/ArgList.h"
#include "clang/Driver/DriverDiagnostic.h"
#include "clang/Driver/Option.h"
#include "clang/Driver/OptTable.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/ADT/StringSwitch.h"

#include "AnalysisConsumer.h"

using namespace clang;
using namespace ento;

bool AnalysisAction::BeginInvocation(CompilerInstance &CI) {
  // NOTE: This is treated by the preprocessor as if it were added by
  // the driver via -D: it's in the section marked by
  // "# 1 \"<command line>\" 1". See InitPreprocessor.cpp.
  // Maybe there should be two entry points, one for the driver, one
  // for clang internals?
  CI.getPreprocessorOpts().addMacroDef("__clang_analyzer__");
  return true;
}

ASTConsumer *AnalysisAction::CreateASTConsumer(CompilerInstance &CI,
                                               StringRef InFile) {
  // If -analyzer-checker-help was given, this should be a no-op.
  if (Opts.ShowCheckerHelp)
    return new ASTConsumer();

  return CreateAnalysisConsumer(CI.getPreprocessor(),
                                CI.getFrontendOpts().OutputFile,
                                this->Opts,
                                CI.getFrontendOpts().Plugins);
}

static bool ParseAnalyzerArgs(AnalyzerOptions &Opts, driver::ArgList &Args,
                              DiagnosticsEngine &Diags) {
  using namespace analyzeroptions;
  using namespace driver;
  bool Success = true;

  if (Arg *A = Args.getLastArg(OPT_analyzer_store)) {
    StringRef Name = A->getValue(Args);
    AnalysisStores Value = llvm::StringSwitch<AnalysisStores>(Name)
#define ANALYSIS_STORE(NAME, CMDFLAG, DESC, CREATFN) \
      .Case(CMDFLAG, NAME##Model)
#include "clang/Frontend/Analyses.def"
      .Default(NumStores);
    if (Value == NumStores) {
      Diags.Report(diag::err_drv_invalid_value)
        << A->getAsString(Args) << Name;
      Success = false;
    } else {
      Opts.AnalysisStoreOpt = Value;
    }
  }

  if (Arg *A = Args.getLastArg(OPT_analyzer_constraints)) {
    StringRef Name = A->getValue(Args);
    AnalysisConstraints Value = llvm::StringSwitch<AnalysisConstraints>(Name)
#define ANALYSIS_CONSTRAINTS(NAME, CMDFLAG, DESC, CREATFN) \
      .Case(CMDFLAG, NAME##Model)
#include "clang/Frontend/Analyses.def"
      .Default(NumConstraints);
    if (Value == NumConstraints) {
      Diags.Report(diag::err_drv_invalid_value)
        << A->getAsString(Args) << Name;
      Success = false;
    } else {
      Opts.AnalysisConstraintsOpt = Value;
    }
  }

  if (Arg *A = Args.getLastArg(OPT_analyzer_output)) {
    StringRef Name = A->getValue(Args);
    AnalysisDiagClients Value = llvm::StringSwitch<AnalysisDiagClients>(Name)
#define ANALYSIS_DIAGNOSTICS(NAME, CMDFLAG, DESC, CREATFN, AUTOCREAT) \
      .Case(CMDFLAG, PD_##NAME)
#include "clang/Frontend/Analyses.def"
      .Default(NUM_ANALYSIS_DIAG_CLIENTS);
    if (Value == NUM_ANALYSIS_DIAG_CLIENTS) {
      Diags.Report(diag::err_drv_invalid_value)
        << A->getAsString(Args) << Name;
      Success = false;
    } else {
      Opts.AnalysisDiagOpt = Value;
    }
  }

  if (Arg *A = Args.getLastArg(OPT_analyzer_purge)) {
    StringRef Name = A->getValue(Args);
    AnalysisPurgeMode Value = llvm::StringSwitch<AnalysisPurgeMode>(Name)
#define ANALYSIS_PURGE(NAME, CMDFLAG, DESC) \
      .Case(CMDFLAG, NAME)
#include "clang/Frontend/Analyses.def"
      .Default(NumPurgeModes);
    if (Value == NumPurgeModes) {
      Diags.Report(diag::err_drv_invalid_value)
        << A->getAsString(Args) << Name;
      Success = false;
    } else {
      Opts.AnalysisPurgeOpt = Value;
    }
  }

  Opts.ShowCheckerHelp = Args.hasArg(OPT_analyzer_checker_help);
  Opts.VisualizeEGDot = Args.hasArg(OPT_analyzer_viz_egraph_graphviz);
  Opts.VisualizeEGUbi = Args.hasArg(OPT_analyzer_viz_egraph_ubigraph);
  Opts.AnalyzeAll = Args.hasArg(OPT_analyzer_opt_analyze_headers);
  Opts.AnalyzerDisplayProgress = Args.hasArg(OPT_analyzer_display_progress);
  Opts.AnalyzeNestedBlocks =
    Args.hasArg(OPT_analyzer_opt_analyze_nested_blocks);
  Opts.EagerlyAssume = Args.hasArg(OPT_analyzer_eagerly_assume);
  Opts.AnalyzeSpecificFunction = Args.getLastArgValue(OPT_analyze_function);
  Opts.UnoptimizedCFG = Args.hasArg(OPT_analysis_UnoptimizedCFG);
  Opts.CFGAddImplicitDtors = Args.hasArg(OPT_analysis_CFGAddImplicitDtors);
  Opts.CFGAddInitializers = Args.hasArg(OPT_analysis_CFGAddInitializers);
  Opts.TrimGraph = Args.hasArg(OPT_trim_egraph);
  Opts.MaxNodes = Args.getLastArgIntValue(OPT_analyzer_max_nodes, 150000,Diags);
  Opts.MaxLoop = Args.getLastArgIntValue(OPT_analyzer_max_loop, 4, Diags);
  Opts.EagerlyTrimEGraph = !Args.hasArg(OPT_analyzer_no_eagerly_trim_egraph);
  Opts.InlineCall = Args.hasArg(OPT_analyzer_inline_call);

  Opts.CheckersControlList.clear();
  for (arg_iterator it = Args.filtered_begin(OPT_analyzer_checker,
                                             OPT_analyzer_disable_checker),
         ie = Args.filtered_end(); it != ie; ++it) {
    const Arg *A = *it;
    A->claim();
    bool enable = (A->getOption().getID() == OPT_analyzer_checker);
    // We can have a list of comma separated checker names, e.g:
    // '-analyzer-checker=cocoa,unix'
    StringRef checkerList = A->getValue(Args);
    SmallVector<StringRef, 4> checkers;
    checkerList.split(checkers, ",");
    for (unsigned i = 0, e = checkers.size(); i != e; ++i)
      Opts.CheckersControlList.push_back(std::make_pair(checkers[i], enable));
  }

  return Success;
}

bool AnalysisAction::ParseArgs(const CompilerInstance &CI,
                               const std::vector<std::string> &args) {
  using namespace driver;

  if (args.empty())
    return true;

  DiagnosticsEngine &Diags = CI.getDiagnostics();
  llvm::OwningPtr<OptTable> Table(createAnalyzerOptTable());

  // FIXME: This is an ugly kludge; switch Arg-parsing code to take
  // StringRef and ArrayRef. Then change this method's signature the same way
  // so it can just be passed right through.
  std::vector<const char*> cargs;
  for (unsigned i = 0, e = args.size(); i != e; ++i)
    cargs.push_back(args[i].c_str());

  const char *const *ArgBegin = &cargs[0];
  const char *const *ArgEnd = ArgBegin + cargs.size();
  unsigned MissingArgIndex, MissingArgCount;
  llvm::OwningPtr<InputArgList> Args(Table->ParseArgs(ArgBegin, ArgEnd,
                                     MissingArgIndex, MissingArgCount));
  assert(Args);

  if (MissingArgCount) {
    Diags.Report(diag::err_drv_missing_argument)
      << Args->getArgString(MissingArgIndex) << MissingArgCount;
    return false;
  }

  if (!ParseAnalyzerArgs(this->Opts, *Args, Diags))
    return false;

  if (this->Opts.ShowCheckerHelp)
    ento::printCheckerHelp(llvm::outs(), CI.getFrontendOpts().Plugins);

  return true;
}

static FrontendPluginRegistry::Add<AnalysisAction>
X("analyzer", "Run the static analyzer");

extern "C" void clang_LinkInStaticAnalyzerPlugin(void) { }
