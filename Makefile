CXXFLAGS += -std=c++2b -Wall -Werror -fmax-errors=2 -g
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

