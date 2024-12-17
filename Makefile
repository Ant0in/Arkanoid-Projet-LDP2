CXXFLAGS += -std=c++2b -pedantic -Wall -Wextra -Walloc-zero -Wcast-align -Wconversion -Wctad-maybe-unsupported -Wctor-dtor-privacy -Wdeprecated-copy-dtor -Wduplicated-branches -Wduplicated-cond -Weffc++ -Wextra-semi -Wfatal-errors -Wfloat-equal -Wformat-signedness -Wformat=2 -Winit-self -Wlogical-op -Wmismatched-tags -Wnoexcept -Wnon-virtual-dtor -Wnull-dereference -Wold-style-cast -Woverloaded-virtual -Wredundant-tags -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wsuggest-attribute=cold -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wuseless-cast -Wvolatile -Wzero-as-null-pointer-constant -fmax-errors=2 -fsanitize=undefined,address,leak -Wno-unused-command-line-argument -Wno-unknown-warning-option
# The flags -Wno-unknown-warning-option and -Wno-unused-command-line-argument are for clang users

CXXFLAGS += $(shell pkg-config allegro-5 allegro_font-5 --cflags)
LDLIBS += $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs)

SRCS := $(shell find . -name '*.cpp')   # Trouve tous les fichiers .cpp
HEADERS := $(shell find . -name '*.hpp')
TARGET := main                         # Nom de l'exécutable final

.PHONY: all
all: $(TARGET)

# Compilation de l'exécutable principal
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(LDLIBS)

.PHONY: clean
clean:
	-rm -f $(TARGET)

