CXXFLAGS += -std=c++2b -pedantic -Wall -Wextra -Walloc-zero -Wcast-align -Wconversion -Wctad-maybe-unsupported -Wctor-dtor-privacy -Wdeprecated-copy-dtor -Wduplicated-branches -Wduplicated-cond -Weffc++ -Wextra-semi -Wfatal-errors -Wfloat-equal -Wformat-signedness -Wformat=2 -Winit-self -Wlogical-op -Wmismatched-tags -Wnoexcept -Wnon-virtual-dtor -Wnull-dereference -Wold-style-cast -Woverloaded-virtual -Wredundant-tags -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wsuggest-attribute=cold -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wuseless-cast -Wvolatile -Wzero-as-null-pointer-constant -fmax-errors=2 -fsanitize=undefined,address,leak -Wno-unused-command-line-argument -Wno-unknown-warning-option
# The flags -Wno-unknown-warning-option and -Wno-unused-command-line-argument are for clang users

CXXFLAGS += $(shell pkg-config allegro-5 allegro_font-5 --cflags)
LDLIBS += $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs)

SRCS := $(shell find src -name '*.cpp')
TARGETS := $(patsubst %.cpp,%,$(SRCS))
ALL_SOURCES := $(filter-out example.cpp, $(wildcard *.cpp))
ALL_HEADERS := $(shell find src -name '*.hpp')


.PHONY: all
all: LSanSuppress.supp $(TARGETS)
	@echo '==> To hide memory leaks from GLX, export LSAN_OPTIONS="suppressions=LSanSuppress.supp" <=='

LSanSuppress.supp:
	@echo 'leak:libGLX' >>  LSanSuppress.supp
	@sort -u LSanSuppress.supp > LSSSorted
	@mv LSSSorted LSanSuppress.supp

$(TARGETS): %:%.cpp
	${CXX} ${CXXFLAGS} -o $@ $<  $$(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs --cflags) -lallegro_main -lstdc++

########### Format

FORMATTER = clang-format -i

.PHONY: format
format: ${ALL_SOURCES} ${ALL_HEADERS}
	${FORMATTER} $+

########### Check

CLANG_CHECK=clang-check-18
CLANG_TIDY=clang-tidy-18
SCAN_BUILD=scan-build-18

.PHONY: check
check: ${ALL_SOURCES} ${ALL_HEADERS}
	# -cppcheck --language='c++' --enable=all --platform=unix64 --suppress=unusedFunction --suppress=ctuOneDefinitionRuleViolation ${SOLUTION_SOURCES}
	-cpplint --verbose=3 --filter=-legal,-build ${SOLUTION_SOURCES}
	-${CLANG_CHECK} ${SOLUTION_SOURCES}
	-${CLANG_TIDY} ${SOLUTION_SOURCES}
	${SCAN_BUILD} ${MAKE} all

.PHONY: clean
clean:
	-rm -rf $(TARGETS)
