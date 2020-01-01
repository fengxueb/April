#makefile for discover

MAKE=make
CC=gcc
CXX=g++
AR=ar

TARGET = libProcess.so

INCLUDE_FILE :=-I./


TOPDIR=../

CPP_SRCS:=$(wildcard *.cpp)
CPP_OBJS:=$(CPP_SRCS:%.cpp=%.o)

SRCS_H:=$(wildcard *.h)
#SRCS_H+=$(wildcard ../common/*.h)

$(TARGET): $(CPP_OBJS)
	$(CXX) -shared -o $(TARGET) $(CPP_OBJS) -fPIC -std=c++11 -pthread
	@test -d $(TOPDIR)build/process/lib || mkdir $(TOPDIR)build/process/lib
	@cp -rf $(TARGET) $(TOPDIR)build/process/lib
	@test -d $(TOPDIR)build/process/include || mkdir $(TOPDIR)build/process/include
	@cp -rf *.h $(TOPDIR)build/process/include

$(CPP_OBJS): %.o:%.cpp $(SRCS_H)
	$(CXX) $(INCLUDE_FILE) -c -fPIC -std=c++11 -pthread $< -o $@

clean:
	@rm -rf $(TARGET) $(CPP_OBJS)
	@rm -rf $(TOPDIR)/build/process/lib/$(TARGET)
	@rm -rf $(TOPDIR)/build/process/include/*