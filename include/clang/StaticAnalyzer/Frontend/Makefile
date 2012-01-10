CLANG_LEVEL := ../../../..
BUILT_SOURCES = AnalyzerOptions.inc

TABLEGEN_INC_FILES_COMMON = 1

include $(CLANG_LEVEL)/Makefile

OptParser = ../../Basic/OptParser.td

$(ObjDir)/AnalyzerOptions.inc.tmp : AnalyzerOptions.td $(OptParser) $(CLANG_TBLGEN) $(ObjDir)/.dir
	$(Echo) "Building Clang Static Analyzer Option tables with tblgen"
	$(Verb) $(ClangTableGen) -gen-opt-parser-defs -o $(call SYSPATH, $@) \
	  -I $(PROJ_SRC_DIR)/../../.. $<
