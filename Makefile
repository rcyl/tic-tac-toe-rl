SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp, bin/%.o, $(SRC))
INC := -Iinclude
CC := g++
LD_FLAGS := 
CC_FLAGS := -Wall -g -std=c++11
OUT = main

$(OUT): $(OBJ)
	$(CC) $(LD_FLAGS) -o $@ $^
	@echo All done

bin/%.o: src/%.cpp
	$(CC) $(INC) $(CC_FLAGS) -c -o $@ $< 

clean:
	rm -rf bin/* $(OUT) $(OUT).exe
	@echo Clean done
	
shout:
	@echo $(SRC)
	@echo $(OBJ)
