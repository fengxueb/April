TARGET=libsecurity.so

CC=g++-4.9
FLAG := -std=c++11 -shared -fPIC

INCLUDE:=-I./include -I.
LIBS:= -lssl -lcrypto

LIB:=-L./lib 

SRCS =OpenSSLInterface.cpp

$(TARGET):$(SRCS:.cpp=.o)
	$(CC) $(INCLUDE) $(FLAG) -o $@ $^ $(LIB) $(LIBS)
	-rm -f *.o *.d

%.o:%.cpp
	$(CC) $(FLAG) $(INCLUDE) -c -o $@ $<
	
clean:
	-rm -f *.o *.d  $(TARGET)
