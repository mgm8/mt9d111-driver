TARGET = example
DRIVER_PATH = ../src
SOURCE = main.cpp $(DRIVER_PATH)/debug.cpp $(DRIVER_PATH)/gpio.cpp $(DRIVER_PATH)/i2c.cpp $(DRIVER_PATH)/mt9d111.cpp

CC = g++
FLAGS = -std=c++11 -o
INCLUDE = ../src/

all:
	$(CC) -I$(INCLUDE) $(FLAGS) $(TARGET).x $(SOURCE)

clean:
	rm *.x
