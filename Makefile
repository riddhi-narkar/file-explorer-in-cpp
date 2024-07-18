CC = g++
CFLAGS = -std=c++11

SRCS = main.cpp file_explorer.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = file_explorer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
