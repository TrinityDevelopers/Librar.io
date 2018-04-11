CXX := g++
CXXFLAGS := -std=c++11
TARGET := Librario

SRCS := $(wildcard *.cpp media/*.cpp terminal/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
	./$(TARGET)
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -rf $(TARGET) *.o media/*.o terminal/*.o