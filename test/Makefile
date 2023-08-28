CXX=g++
CXXFLAGS=-std=c++14 -I../include -Wall

TARGET=cfigout.test

$(TARGET):./main.cpp ../include/cfigout/cfigout.hpp
	$(CXX) $< -o $@ $(CXXFLAGS)
  
clean:
	rm -f $(TARGET)
