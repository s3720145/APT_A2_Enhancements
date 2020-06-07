# .default: all

# all: APT_A2

# src = $(wildcard src/*.cpp) \
# 		$(wildcard src/tests/*.cpp)
# obj = $(src:.cpp=.o)

# APT_A2: $(obj)
# 	g++ -Wall -Werror -std=c++14 -O -o $@ $^

# %.o: %.cpp
# 	g++ -Wall -Werror -std=c++14 -O -c $^

# .PHONY: clean
# clean:
# 	rm -rf $(obj) *.o APT_A2

SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) \
			$(wildcard $(SRC_DIR)/tests/*.cpp) \
			$(wildcard $(SRC_DIR)/tests/gameBoardUnitTests/*.cpp) \
			$(wildcard $(SRC_DIR)/tests/playerUnitTests/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
CPPFLAGS := -Wall -Werror -std=c++14 -O

APT_A2: $(OBJ_FILES)
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -Wall -Werror -std=c++14 -O -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJ_FILES) *.o APT_A2 