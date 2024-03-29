################################################################################
# Makefile
################################################################################

# Makefile by fletcher97
# Version: 5.2
# Repo: www.github.com/fletcher97/utils

# v5.2: Added libflt seccion. All libflt specific configurations are now
# separated. Added timer configuration for libflt. A new task to generate
# coverage reports with lcov was added. All files generated will be stored in
# REP_ROOT. A new section dedicated to running tasks at the start was added
# (init). This was required fot the new vars task. Also fixed minor bugs when
# using iMac.

# v5: Added testing capabilities to the makefile. You can now places Tests in
# TST_ROOT or a subfolder and treat it the same as you would SRC_ROOT. For each
# executable a test executable is now generated. It will use the TST_DIRS that
# have the same index as SRC_DIRS to test them. An important change is that main
# functions should now be specified in a different variable. A merge function
# was also added to aide in the parsing of the required files for tests.

# v4.1: Added debug variable to specify what debug lvl the code should be
# compiled with. If the code is prepared to compile with this flag, it's
# behaviour should change depending on the level set. Setting this option with
# code that is not written with this in mind should not be affected.

# v4: Added templates and implementations folders. You can now specify folders
# with template and implementation files to be added to includes. The default
# for lib creation was changed to 0 and the undefine removed so that the library
# related variables are only created if necessary. Also fixed some small bugs
# due to using wrong variables.

# v3.1: Added debug coverage rules and fixed minor bugs. This Makefile can now
# compile binaries to produce coverage profile files in order to be used with
# gcov. Intermediary files are placed in the OBJ folder. After executing the
# programyou you can run gcov to generate the coverage reports. Alteratively the
# target cov can be used to do that. All generated files will be moved to a gcov
# folder.

# v3.0: Added support for multilanguage. Out of the box it accepts C and C++.
# It is possible to specify the compiler family to be used (LLVM for
# clang/clang++ and GNU for gcc/g++). Other compilers/languages can easily be
# added assuming the compilation process is similar to C.

# v2.4: Added PEDANTIC variable on configs section. If set to true a lot of
# warning flags will be added to use while compiling. By default this feature is
# turned on. Setting the variable to anything else will disable extra warnings.
# Turning it off will still compile with -Wall -Wextra -Werror.
#
# A LANG variable was aslo added to to specify what language the program is
# using so as to be able to detect the extentions of the files (not implemented)
# and enable more warnings.

# v2.3: A rule to check if a program can be compiled was added in other to be
# used for git hooks. A folder with hooks can be found in the same repository
# this makefile came from.

# As of version 2.2 this Makefile expects an asan.c file to be present in the
# asan folder inside the SRC_ROOT directory. A copy of the file is provided
# with the Makefile. Also it now uses clang instead of gcc.

# This makefile can be copied to a directory and it will generate the file
# structure and initialize a git repository with the .init rule. Any variables
# and rules for the specific project can be added in the appropriate section.

# By default this makefile assumes that libft, 42's student made library, a copy
# of which can be obtained by cloning https://github.com/fletcher97/libft.git,
# is being used. It can be removed by simply commenting any reference to it on
# the library section.

################################################################################
# Init
################################################################################

# List of default variables (used to filter out when printing own variables)
DEFAULT_VARS := ${.VARIABLES}

# List of variables that should be ignored when print own variables
IGNORE_VARS = DEFAULT_VARS

# Ignore functions
IGNORE_VARS += _index index lookup rmdup get_files get_files_tests
IGNORE_VARS += get_lib_target _merge merge

# Ignore templates
IGNORE_VARS += make_bin_def make_obj_def make_dep_def make_lib_def
IGNORE_VARS += make_compile_test_def make_compile_test_test_def

################################################################################
# Project Variables
################################################################################

# Name of a single binary. Add as many variables as required by the project
NAME1 := ircserv

# The names of all the binaries. Add aditional variables created above separated
# by space.
NAMES := ${NAME1}

################################################################################
# Configs
################################################################################

# Verbose levels
# 0: Make will be totaly silenced
# 1: Make will print echos and printf
# 2: Make will not be silenced but target commands will not be printed
# 3: Make will print each command
# 4: Make will print all debug info
#
# If no value is specified or an incorrect value is given make will print each
# command like if VERBOSE was set to 3.
VERBOSE := 1

# Debug level. This variable controls what the DEBUG macro the code will be
# compiled with is set to.
# none: undefine DEBUG macro
# trace/debug/info/warn/error/critical: set DEBUG macro to the given level
#
# By default debug is none.
LOG_LVL := none

# Timer switch. Turns compilation with timer support on or off. To turn the
# timer on simply set this variable to on. The timer in the FLT lib will be
# available for use in your program (assuming you are using the FLT lib)
#
# By default the timer is off
TIMER := off

# Name prefix for test executable
TEST_PREFIX := test_

# Version 2.1 and above of this makefile can generate targets to use other
# makefiles as dependencies. This feature will execute the rule of same name in
# an other makefile. This can be usefull in many situation but also a hinderence
# in others. If for example you just want to clean the root directory the clean
# rule will be executed in any other makefile specified. You can deactivate the
# creation of these targets by setting the bellow variable to 0.
CREATE_LIB_TARGETS := 1

# Pedantic allows for extra warning flags to be used while compiling. If set to
# true these flags are applied. If set to anything else the flags will not be
# used. By default it's turned on.
PEDANTIC := true

# Specify the language use by your program. This will allow to detect file
# extentions automatically (not implemented). It also allows fo warnings to be
# activated/deactivated based on the language used.
LANG := C++

# Specify the compiler to use. In conjuntion with the language it can pick the
# right compiler and the right version of the compiler (i.e. gcc vs g++).
# Supported option: LLVM, GNU
COMPILER = GNU

# If we are on OSX force compiler to be LLVM.
ifeq ($(shell uname),Darwin)
	COMPILER := LLVM
endif

################################################################################
# Compiler & Flags
################################################################################

# Compiler
ifeq (${LANG},C)
	ifeq (${COMPILER},LLVM)
		CC := clang
	endif
	ifeq (${COMPILER},GNU)
		CC := gcc
	endif
else ifeq (${LANG},C++)
	ifeq (${COMPILER},LLVM)
		CC := clang++
	endif
	ifeq (${COMPILER},GNU)
		CC := g++
	endif
endif

# Compiler flags
CFLAGS := -Wall -Wextra -Werror
ifeq (${LANG},C++)
	CFLAGS += -std=c++98
endif

# Pedantic flags
ifeq (${PEDANTIC},true)
	CFLAGS += -Wpedantic -Werror=pedantic -pedantic-errors -Wcast-align
	CFLAGS += -Wcast-qual -Wdisabled-optimization -Wformat=2 -Wuninitialized
	CFLAGS += -Winit-self -Wmissing-include-dirs -Wredundant-decls -Wshadow
	CFLAGS += -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option
	CFLAGS += -fstack-protector-all
	ifeq (${COMPILER},GNU)
		CFLAGS += -fstack-clash-protection -Wformat-signedness
		CFLAGS += -Wformat-truncation=2 -Wformat-overflow=2 -Wlogical-op
		CFLAGS += -Wstringop-overflow=4
	endif
	ifeq (${LANG},C++)
		CFLAGS += -Wctor-dtor-privacy -Wold-style-cast -Woverloaded-virtual
		CFLAGS += -Wsign-promo
		ifeq (${COMPILER},GNU)
			CFLAGS += -Wstrict-null-sentinel -Wnoexcept
		endif
	endif
endif

# Generic debug flags
DFLAGS := -g

# Coverage flags
COVFLAGS = -fprofile-arcs -ftest-coverage -O0

# Address sanitizing flags
ASAN := -fsanitize=address -fsanitize-recover=address
ASAN += -fno-omit-frame-pointer -fno-common
ASAN += -fsanitize=pointer-subtract -fsanitize=pointer-compare
# Technicaly UBSan but works with ASan
ASAN += -fsanitize=undefined
# Technicaly LSan but works with ASan
ASAN += -fsanitize=leak
# Thread sanitizing flags
TSAN := -fsanitize=thread
# Memory sanitizing flags
MSAN := -fsanitize=memory -fsanitize-memory-track-origins

################################################################################
# Root Folders
################################################################################

BIN_ROOT := bin/
DEP_ROOT := dep/
INC_ROOT := inc/
TPL_ROOT := ${INC_ROOT}tpl/
IMP_ROOT := ${INC_ROOT}imp/
LIB_ROOT := lib/
OBJ_ROOT := obj/
SRC_ROOT := src/
COV_ROOT := cov/
REP_ROOT := rep/
TST_ROOT := tst/

################################################################################
# Libraries
################################################################################

ifeq (${CREATE_LIB_TARGETS},1)

# Libflt
LIBFLT_ROOT := ${LIB_ROOT}libflt/
LIBFLT_INC := ${LIBFLT_ROOT}inc/ ${LIBFLT_ROOT}inc/tpl/ ${LIBFLT_ROOT}inc/imp/
LIBFLT := ${LIBFLT_ROOT}bin/libflt.a

INC_DIRS += ${LIBFLT_INC}
LIBS += -L${LIBFLT_ROOT}bin -lflt

# Libraries for which to create default targets. All libraries in this list will
# have targets created autimatically. The targets that are created are set in
# DEFAULT_LIB_RULES. The targets will have to format <library root>//<target>
# and it will invoke make as follows:
# `make -C <library root> <rule>`
DEFAULT_LIBS := ${LIBFLT_ROOT}

# Default targets to create for libraries specified in DEFAULT_LIBS. This is a
# small list of common targets in most makefiles.
DEFAULT_LIB_RULES := all clean re

# All projects with a copy of this makefile v2.1 and up ate garanteed to work
# with these targets. If you wish to not use them just comment the lines you
# don't want.
DEFAULT_LIB_RULES += fclean clean_all clean_dep
DEFAULT_LIB_RULES += debug debug_re debug_asan debug_asan_re

# All projects with a copy of this makefile v2.2 and up ate garanteed to work
# with these targets. If you wish to not use them just comment the lines you
# don't want.
DEFAULT_LIB_RULES += debug_tsan debug_tsan_re debug_msan debug_msan_re

endif

################################################################################
# Lib FLT
################################################################################

# Debug lvl flag
ifeq (${LOG_LVL},none)
	CFLAGS += -ULOG_LVL
else ifeq (${LOG_LVL}, trace)
	CFLAGS += -DLOG_LVL=FLT_LOG_TRACE_LVL
else ifeq (${LOG_LVL}, debug)
	CFLAGS += -DLOG_LVL=FLT_LOG_DEBUG_LVL
else ifeq (${LOG_LVL}, info)
	CFLAGS += -DLOG_LVL=FLT_LOG_INFO_LVL
else ifeq (${LOG_LVL}, warn)
	CFLAGS += -DLOG_LVL=FLT_LOG_WARN_LVL
else ifeq (${LOG_LVL}, error)
	CFLAGS += -DLOG_LVL=FLT_LOG_ERROR_LVL
else ifeq (${LOG_LVL}, fatal)
	CFLAGS += -DLOG_LVL=FLT_LOG_FATAL_LVL
endif

# Timer activation
ifeq (${TIMER},on)
	CFLAGS += -DFLT_TIMER
endif

################################################################################
# Content Folders
################################################################################

# Lists of ':' separated folders inside SRC_ROOT containing source files. Each
# folder needs to end with a '/'. The path to the folders is relative to
# SRC_ROOT. If SRC_ROOT contains files './' needs to be in the list. Each list
# is separated by a space or by going to a new line and adding onto the var.
#
# IMPORTANT: If you wish to use testing, DO NOT place any folders with files
# containing a main function in this list. The main file(s) should be be
# isolated in a separate folder (you can place it alone in SRC_ROOT and all src
# files in their own subfolder). The main file should be place in the FILES_MAIN
# list.
#
# Exemple:
# DIRS := folder1/:folder2/
# DIRS += folder1/:folder3/:folder4/
DIRS := log/:classes/:utils/:commands/

# List of directories with tests. Formating follows the same rules as DIRS
# above. All folders are relative to TST_ROOT. Each group of folder should only
# contain tests for the equivalent executable. The first group will test the
# files in the first group of DIRS (or the first executable specified in NAMES).
DIRS_TEST := unit_tests/

SRC_DIRS_LIST := $(addprefix ${SRC_ROOT},${DIRS})
SRC_DIRS_LIST := $(foreach dl,${SRC_DIRS_LIST},$(subst :,:${SRC_ROOT},${dl}))

TST_DIRS_LIST := $(addprefix ${TST_ROOT},${DIRS_TEST})
TST_DIRS_LIST := $(foreach dl,${TST_DIRS_LIST},$(subst :,:${TST_ROOT},${dl}))

SRC_DIRS = $(call rmdup,$(subst :,${SPACE},${SRC_DIRS_LIST}))

TST_DIRS = $(call rmdup,$(subst :,${SPACE},${TST_DIRS_LIST}))

OBJ_DIRS := $(addprefix ${OBJ_ROOT},${SRC_DIRS})
OBJ_DIRS += $(addprefix ${OBJ_ROOT},${TST_DIRS})

DEP_DIRS := $(addprefix ${DEP_ROOT},${SRC_DIRS})
DEP_DIRS += $(addprefix ${DEP_ROOT},${TST_DIRS})

# List of folders with header files.Each folder needs to end with a '/'. The
# path to the folders is relative to the root of the makefile. Library includes
# can be specified here.
INC_DIRS += ${INC_ROOT} ${INC_ROOT}/bots

# List of folders with templates and their implementations. Each folder needs to
# end with a '/'. The path to the folders is relative to the root of the
# makefile.
ifeq (${LANG},C++)
	TPL_DIRS := ${TPL_ROOT}
	IMP_DIRS := ${IMP_ROOT}
endif

################################################################################
# Files
################################################################################

ifeq (${LANG},C)
	SRC_FILE_EXT := c
	INC_FILE_EXT := h
else ifeq (${LANG},C++)
	SRC_FILE_EXT := cpp
	INC_FILE_EXT := hpp
	TPL_FILE_EXT := tpp
	IMP_FILE_EXT := ipp
endif

# List of src files containing the main function. This list should contain one
# entry per executable. All files are relative to SRC_ROOT
# Exemple:
MAIN_FILES := ${SRC_ROOT}main.${SRC_FILE_EXT}
# List of src files containing the main function for testing. This list should
# contain one entry per executable. All files are relative to SRC_ROOT
# Exemple:
MAIN_FILES_TEST := ${TST_ROOT}main.${SRC_FILE_EXT}

# Source files grouped by executable
SRCS_LIST_SIMPLE = $(foreach dl,${SRC_DIRS_LIST},$(subst ${SPACE},:,$(strip\
	$(foreach dir,$(subst :,${SPACE},${dl}),\
	$(wildcard ${dir}*.${SRC_FILE_EXT})))))
SRCS_LIST = $(call merge,${SRCS_LIST_SIMPLE},${MAIN_FILES})

# Test files grouped by executable
TSTS_LIST_SIMPLE = $(foreach dl,${TST_DIRS_LIST},$(subst ${SPACE},:,$(strip\
	$(foreach dir,$(subst :,${SPACE},${dl}),\
	$(wildcard ${dir}*.${SRC_FILE_EXT})))))
TSTS_LIST = $(call merge,$(call merge,${SRCS_LIST_SIMPLE},${TSTS_LIST_SIMPLE}),\
	${MAIN_FILES_TEST})

# Object files grouped by executable
OBJS_LIST = $(subst :,:${OBJ_ROOT},$(addprefix ${OBJ_ROOT},\
	$(subst .${SRC_FILE_EXT},.o,${SRCS_LIST})))

# Test object files grouped by executable
OBJS_LIST_TEST = $(subst :,:${OBJ_ROOT},$(addprefix ${OBJ_ROOT},\
	$(subst .${SRC_FILE_EXT},.o,${TSTS_LIST})))

# All source/dependancy files
SRCS_SUM = $(foreach dir,${SRC_DIRS},$(wildcard ${dir}*.${SRC_FILE_EXT}))
SRCS_SUM += $(foreach dir,${TST_DIRS},$(wildcard ${dir}*.${SRC_FILE_EXT}))
SRCS_SUM += ${MAIN_FILES} ${MAIN_FILES_TEST}
SRCS = $(call rmdup,${SRCS_SUM})
DEPS = $(addprefix ${DEP_ROOT},${SRCS:.${SRC_FILE_EXT}=.d})

INCS := ${addprefix -I,${INC_DIRS}}
INCS += ${addprefix -I,${TPL_DIRS}}
INCS += ${addprefix -I,${IMP_DIRS}}

BINS := ${addprefix ${BIN_ROOT},${NAMES}}
TESTS := ${addprefix ${BIN_ROOT}${TEST_PREFIX},${NAMES}}

################################################################################
# Conditions
################################################################################

ifeq ($(shell uname),Linux)
	SED := sed -i.tmp --expression
else ifeq ($(shell uname),Darwin)
	SED := sed -i.tmp
endif

ifeq ($(VERBOSE),0)
	MAKEFLAGS += --silent
	BLOCK := &>/dev/null
else ifeq ($(VERBOSE),1)
	MAKEFLAGS += --silent
else ifeq ($(VERBOSE),2)
	AT := @
else ifeq ($(VERBOSE),4)
	MAKEFLAGS += --debug=v
endif

################################################################################
# VPATHS
################################################################################

vpath %.o $(OBJ_ROOT)
vpath %.${INC_FILE_EXT} $(INC_ROOT)
vpath %.${SRC_FILE_EXT} $(SRC_DIRS) $(TST_DIRS)
vpath %.d $(DEP_DIRS)

################################################################################
# Project Target
################################################################################

all: ${BINS}
tests: ${TESTS}

.SECONDEXPANSION:
${BIN_ROOT}${NAME1}: ${LIBFLT} $$(call get_files,$${@F},$${OBJS_LIST})
	${AT}printf "\033[33m[CREATING ${@F}]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${@D} ${BLOCK}
	${AT}${CC} ${CFLAGS} ${INCS} ${ASAN_FILE}\
		$(call get_files,${@F},${OBJS_LIST}) ${LIBS} -o $@ ${BLOCK}

${BIN_ROOT}${TEST_PREFIX}${NAME1}: ${LIBFLT} $$(call get_files_tests,$${@F},$${OBJS_LIST_TEST})
	${AT}printf "\033[33m[CREATING ${@F}]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${@D} ${BLOCK}
	${AT}${CC} ${CFLAGS} ${INCS} ${ASAN_FILE}\
		$(call get_files_tests,${@F},${OBJS_LIST_TEST}) ${LIBS} -o $@ ${BLOCK}

${LIBFLT}: $$(call get_lib_target,$${DEFAULT_LIBS},all) ;

################################################################################
# Clean Targets
################################################################################

clean: $$(call get_lib_target,$${DEFAULT_LIBS},$$@)
	${AT}printf "\033[38;5;1m[REMOVING OBJECTS]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${OBJ_ROOT} ${BLOCK}
	${AT}find ${OBJ_ROOT} -type f -name "*.o" -delete ${BLOCK}
	${AT}printf "\033[38;5;1m[REMOVING COVERAGE]\033[0m\n" ${BLOCK}
	${AT}find ${OBJ_ROOT} -type f\
		-name "*.gcda" -delete -o -name "*.gcno" -delete ${BLOCK}
	${AT}mkdir -p ${COV_ROOT} ${BLOCK}
	${AT}find ${COV_ROOT} -type f -name "*.gcov" -delete ${BLOCK}
	${AT}mkdir -p ${REP_ROOT} ${BLOCK}
	${AT}find ${REP_ROOT} -type f -delete ${BLOCK}
	${AT}rm -f coverage.info ${BLOCK}

fclean: $$(call get_lib_target,$${DEFAULT_LIBS},$$@) clean
	${AT}printf "\033[38;5;1m[REMOVING BINARIES]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${BIN_ROOT} ${BLOCK}
	${AT}find ${BIN_ROOT} -type f -delete ${BLOCK}

clean_dep: $$(call get_lib_target,$${DEFAULT_LIBS},$$@)
	${AT}printf "\033[38;5;1m[REMOVING DEPENDENCIES]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${DEP_ROOT} ${BLOCK}
	${AT}find ${DEP_ROOT} -type f -name "*.d" -delete ${BLOCK}

clean_all: fclean clean_dep

re: fclean all

tests_re: fclean tests

################################################################################
# Debug Targets
################################################################################

debug: CFLAGS += ${DFLAGS}
debug: $$(call get_lib_target,$${DEFAULT_LIBS},$$@) all

debug_tests: CFLAGS += ${DFLAGS}
debug_tests: $$(call get_lib_target,$${DEFAULT_LIBS},$$@) tests

debug_cov: CFLAGS += ${COVFLAGS}
debug_cov: tests

cov:
	${AT}mkdir -p ${COV_ROOT} ${BLOCK}
	${AT}gcov -arHs $$(find ${OBJ_ROOT} -name "*.gc*") ${BLOCK}
	${AT}mv *.gcov ${COV_ROOT} ${BLOCK}

lcov:
	${AT}lcov -c -b . -d . -o coverage.info --no-external --rc lcov_branch_coverage=1 --filter branch,function --ignore-errors mismatch${BLOCK}
	${AT}mkdir -p ${REP_ROOT} ${BLOCK}
	${AT}genhtml coverage.info -o ${REP_ROOT} --rc genhtml_branch_coverage=1 --demangle-cpp --legend --filter branch,function --dark-mode${BLOCK}

obj/asan/asan.o: src/asan/asan.c
	${AT}mkdir -p ${@D} ${BLOCK}
	${AT}${CC} -o $@ -c $< ${BLOCK}

debug_asan: CFLAGS += ${DFLAGS} ${ASAN}
debug_asan: ASAN_FILE = obj/asan/asan.o
debug_asan: $$(call get_lib_target,$${DEFAULT_LIBS},$$@) obj/asan/asan.o all

debug_tsan: CFLAGS += ${DFLAGS} ${TSAN}
debug_tsan: $$(call get_lib_target,$${DEFAULT_LIBS},$$@) all

debug_msan: CFLAGS += ${DFLAGS} ${MSAN}
debug_msan: $$(call get_lib_target,$${DEFAULT_LIBS},$$@) all

debug_re: fclean debug

debug_tests_re: fclean debug_tests

debug_cov_re: fclean debug_cov

debug_asan_re: fclean debug_asan

debug_tsan_re: fclean debug_tsan

debug_msan_re: fclean debug_msan

################################################################################
# Utility Targets
################################################################################

.init:
	${AT}printf "\033[33m[CREATING FOLDER STRUCTURE]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${BIN_ROOT} ${BLOCK}
	${AT}mkdir -p ${DEP_ROOT} ${BLOCK}
	${AT}mkdir -p ${INC_ROOT} ${BLOCK}
	${AT}mkdir -p ${TPL_ROOT} ${BLOCK}
	${AT}mkdir -p ${IMP_ROOT} ${BLOCK}
	${AT}mkdir -p ${LIB_ROOT} ${BLOCK}
	${AT}mkdir -p ${OBJ_ROOT} ${BLOCK}
	${AT}mkdir -p ${SRC_ROOT} ${BLOCK}
	${AT}mkdir -p ${COV_ROOT} ${BLOCK}
	${AT}mkdir -p ${TST_ROOT} ${BLOCK}
	${AT}printf "\033[33m[INITIALIZING GIT REPOSITORY]\033[0m\n" ${BLOCK}
	${AT}git init ${BLOCK}
	${AT}echo -en ".DS_Store\na.out\n*.o"\
		"\n*.gcda\n*.gcno\n*.gcov\n*.d\n*.ignore\n.vscode/\nbin/"\
		> .gitignore ${BLOCK}
	${AT}date > $@ ${BLOCK}
	${AT}printf "\033[33m[CREATING FIRST COMMIT]\033[0m\n" ${BLOCK}
	${AT}git add .gitignore ${BLOCK}
	${AT}git add $@ ${BLOCK}
	${AT}git add Makefile ${BLOCK}
	${AT}git commit -m "init" ${BLOCK}

# Meta target to force a target to be executed
.FORCE: ;

# Print a specifique variable
print-%: ; @echo $*=$($*)

# List all the targets in alphabetical order
targets:
	${AT}${MAKE} LC_ALL=C -pRrq -f ${CURRENT_FILE} : 2>/dev/null\
		| awk -v RS= -F: '/^# File/,/^# files hash-table stats/\
			{if ($$1 !~ "^[#]") {print $$1}}\
			{if ($$1 ~ "# makefile") {print $$2}}'\
		| sort

vars:
	$(foreach v,\
		$(sort $(filter-out ${DEFAULT_VARS} ${IGNORE_VARS},${.VARIABLES})),\
		$(info ${v} = ${${v}}))

compile-test: CFLAGS += -DDEBUG_LVL=TRACE
compile-test: CFLAGS += -DFLT_TIMER
compile-test: ${addprefix compile-test/,${NAMES}}
compile-test: ${addprefix compile-test/${TEST_PREFIX},${NAMES}}

uncrustify-check:
	${AT}find . -name "*.[chit]pp" > uncrustify-targets.txt ${BLOCK}
	${AT}uncrustify -c uncrustify.cfg --check -F uncrustify-targets.txt -l CPP -q${BLOCK}

################################################################################
# .PHONY
################################################################################

# Phony clean targets
.PHONY: clean fclean clean_dep clean_all

# Phony debug targets
.PHONY: debug debug_re debug_asan debug_asan_re debug_tsan debug_tsan_re
.PHONY: debug_msan debug_msan_re

# Phony cov targets
.PHONY: debug_cov debug_cov_re cov lcov

# Phony utility targets
.PHONY: targets .FORCE compile-test vars uncrustify-check

# Phony execution targets
.PHONY: re tests_re all tests

################################################################################
# Constants
################################################################################

NULL =
SPACE = ${NULL} #
CURRENT_FILE = ${MAKEFILE_LIST}

################################################################################
# Functions
################################################################################

# Get the index of a given word in a list
_index = $(if $(findstring $1,$2),$(call _index,$1,\
	$(wordlist 2,$(words $2),$2),x $3),$3)
index = $(words $(call _index,$1,$2))

# Get value at the same index
lookup = $(word $(call index,$1,$2),$3)

# Remove duplicates
rmdup = $(if $1,$(firstword $1) $(call rmdup,$(filter-out $(firstword $1),$1)))

# Get files for a specific binary
get_files = $(subst :,${SPACE},$(call lookup,$1,${NAMES},$2))
get_files_tests = $(subst :,${SPACE},\
	$(call lookup,$1,$(addprefix ${TEST_PREFIX},${NAMES}),$2))

# Get default target for libs given a rule
get_lib_target = $(foreach lib,$1,${lib}/$2)

# Merge 2 lists concatenating element by element
_merge = $(foreach el,$1,$(if $(call lookup,${el},$1,$2),\
	$(addprefix ${el},:$(call lookup,${el},$1,$2)), ${el}))
merge = $(intcmp $(words $1),$(words $2),$(call _merge,$2,$1),\
	$(call _merge,$1,$2))

################################################################################
# Target Templates
################################################################################

define make_bin_def
${1}: ${2}
endef

define make_obj_def
${1}: ${2} ${3}
	$${AT}printf "\033[38;5;14m[OBJ]: \033[38;5;47m$$@\033[0m\n" $${BLOCK}
	$${AT}mkdir -p $${@D} $${BLOCK}
	$${AT}$${CC} $${CFLAGS} $${INCS} -c $$< -o $$@ $${BLOCK}
endef

define make_dep_def
${1}: ${2}
	$${AT}printf "\033[38;5;13m[DEP]: \033[38;5;47m$$@\033[0m\n" $${BLOCK}
	$${AT}mkdir -p $${@D} $${BLOCK}
	$${AT}$${CC} -MM $$< $${INCS} -MF $$@ $${BLOCK}
	$${AT}$${SED} 's|:| $$@ :|' $$@ $${SED_END} $${BLOCK}
	$${AT}$${SED} '1 s|^|$${@D}/|' $$@ && rm -f $$@.tmp $${BLOCK}
	$${AT}$${SED} '1 s|^$${DEP_ROOT}|$${OBJ_ROOT}|' $$@\
		&& rm -f $$@.tmp $${BLOCK}
endef

define make_lib_def
${1}/${2}: .FORCE
	make -C ${1} ${2}
endef

define make_compile_test_def
compile-test/${1}: .FORCE
	$${AT}printf "\033[33m[TESTING $${@F}]\033[0m\n" $${BLOCK}
	$${AT}$${CC} $${CFLAGS} -fsyntax-only $${INCS} $${ASAN_FILE}\
		$$(call get_files,$${@F},$${SRCS_LIST}) $${BLOCK}
endef

define make_compile_test_test_def
compile-test/${1}: .FORCE
	$${AT}printf "\033[33m[TESTING $${@F}]\033[0m\n" $${BLOCK}
	$${AT}$${CC} $${CFLAGS} -fsyntax-only $${INCS} $${ASAN_FILE}\
		$$(call get_files_tests,$${@F},$${TSTS_LIST}) $${BLOCK}
endef

################################################################################
# Target Generator
################################################################################

ifneq (${BIN_ROOT},./)
$(foreach bin,${BINS},$(eval\
$(call make_bin_def,$(notdir ${bin}),${bin})))
endif

ifneq (${BIN_ROOT},./)
$(foreach bin,${TESTS},$(eval\
$(call make_bin_def,$(notdir ${bin}),${bin})))
endif

$(foreach src,${SRCS},$(eval\
$(call make_dep_def,$(addprefix ${DEP_ROOT},\
${src:.${SRC_FILE_EXT}=.d}),${src})))

$(foreach src,${SRCS},$(eval\
$(call make_obj_def,$(addprefix ${OBJ_ROOT},\
${src:.${SRC_FILE_EXT}=.o}),${src},\
$(addprefix ${DEP_ROOT},${src:.${SRC_FILE_EXT}=.d}))))

$(foreach lib,${DEFAULT_LIBS},$(foreach target,${DEFAULT_LIB_RULES},$(eval\
$(call make_lib_def,${lib},${target}))))

$(foreach name,$(NAMES),$(eval\
$(call make_compile_test_def,${name})))

$(foreach name,$(NAMES),$(eval\
$(call make_compile_test_test_def,${TEST_PREFIX}${name})))

################################################################################
# Includes
################################################################################

-include ${DEPS}
