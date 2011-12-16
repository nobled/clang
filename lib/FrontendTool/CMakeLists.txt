set(LLVM_USED_LIBS clangDriver clangFrontend clangRewrite clangCodeGen
    clangARCMigrate)

add_clang_library(clangFrontendTool
  ExecuteCompilerInvocation.cpp
  )

add_dependencies(clangFrontendTool
  ClangCC1Options
  ClangDiagnosticFrontend)
