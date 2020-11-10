SRC_DIR := src
OBJ_DIR := obj
OUT_DIR := out
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS :=
CPPFLAGS := -std=c++11
CXXFLAGS :=

$(info Compiling sources...)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p ${OBJ_DIR}
	@g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(info Generating executable...)

out/a.exe: $(OBJ_FILES)
	@g++ $(LDFLAGS) -o $@ $^

$(info Build complete (out/a.exe).)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/* ${OUT_DIR}/main.exe