
CC            = g++
CFLAGS        = -Wall -std=c++0x -I./src
LDFLAGS       = -Wall


SRC := main.cpp Shop.cpp Product.cpp


OBJ := $(SRC:.cpp=.o)


all: task3

clean:
	-rm *.o


%.o : %.cpp
	g++ -std=c++11 -lpthread -c -o $@ $<

task3: $(OBJ)
	g++ -o $@ $^ -std=c++11 -lpthread
