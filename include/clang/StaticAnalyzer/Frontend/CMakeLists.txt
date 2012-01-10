clang_tablegen(AnalyzerOptions.inc -gen-opt-parser-defs
  -I ${CMAKE_CURRENT_SOURCE_DIR}/../../../
  SOURCE AnalyzerOptions.td
  TARGET ClangStaticAnalyzerOptions)
