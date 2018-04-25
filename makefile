CXX := g++
CXXFLAGS := -std=c++11 -g -pthread
GTKFLAGS := `pkg-config gtkmm-3.0 --cflags --libs`
TARGET := Librar.io

SRCS := $(wildcard *.cpp media/*.cpp terminal/*.cpp gui/*.cpp gui/dialogs/*.cpp gui/elements/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
	./$(TARGET)
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(GTKFLAGS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(GTKFLAGS)
clean:
	rm -rf $(TARGET) *.o media/*.o terminal/*.o gui/*.o gui/dialogs/*.o gui/elements/*.o
clean_gui:
	rm -rf gui/*.o gui/dialogs/*.o gui/elements/*.o