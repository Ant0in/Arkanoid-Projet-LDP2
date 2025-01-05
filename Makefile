# Compilation flags
CXXFLAGS += -std=c++2b -Wall -Wextra

# All warnings being treated as errors and debugging flags
CXXFLAGS += -Werror -g

# Additional warning flags for robust code
CXXFLAGS += -Wpedantic
CXXFLAGS += -Wconversion
CXXFLAGS += -Wshadow 
CXXFLAGS += -Wold-style-cast 
CXXFLAGS += -Wcast-align 
CXXFLAGS += -Wunused 
CXXFLAGS += -Wmisleading-indentation 
CXXFLAGS += -Wduplicated-cond 
CXXFLAGS += -Wnull-dereference 
CXXFLAGS += -Wdouble-promotion

# Flags for polymorphism-related issues
CXXFLAGS += -Wnon-virtual-dtor 
CXXFLAGS += -Woverloaded-virtual 

# Memory sanitization flags (DONT ENABLE PLEASE IM BEGGING YOU)
# CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
# LDFLAGS += -fsanitize=address

# Allegro library configuration
CXXFLAGS += $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --cflags)
LDLIBS += $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --libs)


# Source and header files
SRCS := $(shell find . -name '*.cpp')   
HEADERS := $(shell find . -name '*.hpp')
TARGET := main                        

# Default rule
.PHONY: all
all: $(TARGET)

# Linking
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(LDLIBS) $(LDFLAGS)

# Clean rule
.PHONY: clean
clean:
	-rm -f $(TARGET)

# Run rule
.PHONY: run
run: $(TARGET)
	./$(TARGET)
