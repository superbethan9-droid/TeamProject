
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -Iinclude

SRC_DIR = src
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

APP = $(BUILD_DIR)/app

all: $(APP)

$(APP): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(OBJECTS:.o=.d)

run: $(APP)
	./$(APP)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
