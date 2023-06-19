CC := g++
CFLAGS := -std=c++11 -Wall -Wextra

SRCS := Main.cpp gate.cpp item.cpp move.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)
EXEC := program

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

-include $(DEPS)

%.o: %.cpp
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(EXEC)
