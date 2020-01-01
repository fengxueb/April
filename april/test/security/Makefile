TARGET=TestOpenssl

CC=g++-4.9
MAKE=make
FLAG := -std=c++11 -fPIC
FLAG += -DNDEBUG -g -O2 -Wall

TOPDIR=../../
INCLUDE:=-I$(TOPDIR)security
LIBS:=-lsecurity -lcrypto -lssl
LIB:=-L$(TOPDIR)security

SRCS = TestOpenssl.cpp

$(TARGET):$(SRCS:.cpp=.o)
	$(MAKE) -C $(TOPDIR)security
	$(CC) $(INCLUDE) $(FLAG) -o $@ $^ $(LIB) $(LIBS)
	-rm -f *.o *.d

%.o:%.cpp
	$(CC) $(FLAG) $(INCLUDE) -c -o $@ $<
	
clean:
	-rm -f *.o *.d  $(TARGET)
	cd $(TOPDIR)security  && $(MAKE) clean
