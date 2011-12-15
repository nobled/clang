//===--- AnalyzerOptions.td - Options for the static analyzer plugin ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  This file defines the options accepted by the static analyzer plugin.
//
//===----------------------------------------------------------------------===//

// Include the common option parsing interfaces.
include "../Basic/OptParser.td"

//===----------------------------------------------------------------------===//
// Analyzer Options
//===----------------------------------------------------------------------===//

def analysis_UnoptimizedCFG : Flag<"-unoptimized-cfg">,
  HelpText<"Generate unoptimized CFGs for all analyses">;
def analysis_CFGAddImplicitDtors : Flag<"-cfg-add-implicit-dtors">,
  HelpText<"Add C++ implicit destructors to CFGs for all analyses">;
def analysis_CFGAddInitializers : Flag<"-cfg-add-initializers">,
  HelpText<"Add C++ initializers to CFGs for all analyses">;

def analyzer_store : Separate<"-analyzer-store">,
  HelpText<"Source Code Analysis - Abstract Memory Store Models">;
def analyzer_store_EQ : Joined<"-analyzer-store=">, Alias<analyzer_store>;

def analyzer_constraints : Separate<"-analyzer-constraints">,
  HelpText<"Source Code Analysis - Symbolic Constraint Engines">;
def analyzer_constraints_EQ : Joined<"-analyzer-constraints=">,
  Alias<analyzer_constraints>;

def analyzer_output : Separate<"-analyzer-output">,
  HelpText<"Source Code Analysis - Output Options">;
def analyzer_output_EQ : Joined<"-analyzer-output=">,
  Alias<analyzer_output>;

def analyzer_purge : Separate<"-analyzer-purge">,
  HelpText<"Source Code Analysis - Dead Symbol Removal Frequency">;
def analyzer_purge_EQ : Joined<"-analyzer-purge=">, Alias<analyzer_purge>;

def analyzer_opt_analyze_headers : Flag<"-analyzer-opt-analyze-headers">,
  HelpText<"Force the static analyzer to analyze functions defined in header files">;
def analyzer_opt_analyze_nested_blocks : Flag<"-analyzer-opt-analyze-nested-blocks">,
  HelpText<"Analyze the definitions of blocks in addition to functions">;
def analyzer_display_progress : Flag<"-analyzer-display-progress">,
  HelpText<"Emit verbose output about the analyzer's progress">;
def analyze_function : Separate<"-analyze-function">,
  HelpText<"Run analysis on specific function">;
def analyze_function_EQ : Joined<"-analyze-function=">, Alias<analyze_function>;
def analyzer_eagerly_assume : Flag<"-analyzer-eagerly-assume">,
  HelpText<"Eagerly assume the truth/falseness of some symbolic constraints">;
def analyzer_no_eagerly_trim_egraph : Flag<"-analyzer-no-eagerly-trim-egraph">,
  HelpText<"Don't eagerly remove uninteresting ExplodedNodes from the ExplodedGraph">;
def trim_egraph : Flag<"-trim-egraph">,
  HelpText<"Only show error-related paths in the analysis graph">;
def analyzer_viz_egraph_graphviz : Flag<"-analyzer-viz-egraph-graphviz">,
  HelpText<"Display exploded graph using GraphViz">;
def analyzer_viz_egraph_ubigraph : Flag<"-analyzer-viz-egraph-ubigraph">,
  HelpText<"Display exploded graph using Ubigraph">;
def analyzer_inline_call : Flag<"-analyzer-inline-call">,
  HelpText<"Experimental transfer function inlining callees when its definition is available.">;
def analyzer_max_nodes : Separate<"-analyzer-max-nodes">,
  HelpText<"The maximum number of nodes the analyzer can generate (150000 default, 0 = no limit)">;
def analyzer_max_loop : Separate<"-analyzer-max-loop">,
  HelpText<"The maximum number of times the analyzer will go through a loop">;

def analyzer_checker : Separate<"-analyzer-checker">,
  HelpText<"Choose analyzer checkers to enable">;
def analyzer_checker_EQ : Joined<"-analyzer-checker=">,
  Alias<analyzer_checker>;

def analyzer_disable_checker : Separate<"-analyzer-disable-checker">,
  HelpText<"Choose analyzer checkers to disable">;
def analyzer_disable_checker_EQ : Joined<"-analyzer-disable-checker=">,
  Alias<analyzer_disable_checker>;

def analyzer_checker_help : Flag<"-analyzer-checker-help">,
  HelpText<"Display the list of analyzer checkers that are available">;

