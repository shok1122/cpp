CC := gcc

CFLAGS :=
CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -std=c++11

TARGET := xecho

DEVROOT := ../..

INCLUDE_FILES :=
INCLUDE_FILES += $(DEVROOT)/include
INCLUDES := $(foreach INCLUDE_FILE, $(INCLUDE_FILES), -I$(INCLUDE_FILE))

OBJS :=
OBJS += xecho.o
SRCS := $(OBJS:.o=.cpp)

vpath %.cpp $(DEVROOT)/$(TARGET)/src

.PHONY: all clean distclean

all: $(TARGET)
	@echo finish!!!

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(TARGET)

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGET)
