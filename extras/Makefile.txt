# CC = g++
# CFLAGS = -std=c++11

# SRCS = main.cpp normal_mode.cpp command_mode.cpp file_operations.cpp
# OBJS = $(SRCS:.cpp=.o)
# TARGET = file_explorer

# all: $(TARGET)

# $(TARGET): $(OBJS)
# 	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# main.o: main.cpp normal_mode.h command_mode.h
# 	$(CC) $(CFLAGS) -c main.cpp

# normal_mode.o: normal_mode.cpp normal_mode.h file_operations.h
# 	$(CC) $(CFLAGS) -c normal_mode.cpp

# command_mode.o: command_mode.cpp command_mode.h file_operations.h
# 	$(CC) $(CFLAGS) -c command_mode.cpp

# file_operations.o: file_operations.cpp file_operations.h
# 	$(CC) $(CFLAGS) -c file_operations.cpp

# clean:
# 	rm -f $(OBJS) $(TARGET)

CC = g++
CFLAGS = -std=c++11

SRCS = main.cpp normal_mode.cpp command_mode.cpp file_operations.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = file_explorer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
