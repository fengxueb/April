#makefile for discover

MAKE=make
CC=gcc
CXX=g++
AR=ar

TARGET = testProcess

INCLUDE_PATH :=-I../../build/process/include
LIBRARY_PATH :=-L../../build/process/lib
LIBS := -lProcess


TOPDIR=../../

CPP_SRCS:=$(wildcard *.cpp)
#CPP_OBJS:=$(CPP_SRCS:%.cpp=%.o)

H_SRCS:=$(wildcard *.h)
#SRCS_H+=$(wildcard ../common/*.h)

$(TARGET): $(CPP_SRCS) $(H_SRCS)
	$(CXX)  -o $(TARGET) $(CPP_SRCS) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS)  -std=c++11 -pthread 
	@test -d $(TOPDIR)build/process/bin || mkdir $(TOPDIR)build/process/bin
	@cp -rf $(TARGET) $(TOPDIR)build/process/bin
	
#$(CPP_OBJS): %.o:%.cpp $(SRCS_H)
#	$(CXX) $(INCLUDE_FILE) -c -fPIC -std=c++11 -pthread $< -o $@

clean:
	@rm -rf $(TOPDIR)/build/process/bin/$(TARGET)
	@rm -rf $(TARGET)
	