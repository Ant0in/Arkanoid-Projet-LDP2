

CXXFLAGS += -std=c++2b -Wall -Werror -Wextra

# all warnings being treated as errors
CXXFLAGS += -fmax-errors=1 -g
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

CXXFLAGS += -Wnon-virtual-dtor 
CXXFLAGS += -Woverloaded-virtual 

CXXFLAGS += $(shell pkg-config allegro-5 allegro_font-5 --cflags)
LDLIBS += $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs)

SRCS := $(shell find . -name '*.cpp')   
HEADERS := $(shell find . -name '*.hpp')
TARGET := main                        

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(LDLIBS)

.PHONY: clean
clean:
	-rm -f $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)
