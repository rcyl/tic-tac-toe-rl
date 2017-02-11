#SRC := $(wildcard src/*.cpp)
SRC_EXT := cpp 
PLAY := play
OUT = main
SRC := $(shell find src/* -type f -name *.$(SRC_EXT) ! -name $(PLAY).$(SRC_EXT) ! -name $(OUT).$(SRC_EXT))
OBJ := $(patsubst src/%.cpp, bin/%.o, $(SRC))
INC := -Iinclude
CC := g++
LD_FLAGS := 
CC_FLAGS := -Wall -g -std=c++11

all: $(OUT) $(PLAY)

$(OUT): $(OBJ) bin/$(OUT).o
	$(CC) $(LD_FLAGS) -o $@ $^
	@echo Main done
	
$(PLAY): $(OBJ) bin/$(PLAY).o
	$(CC) $(LD_FLAGS) -o $@ $^
	@echo Play done

bin/%.o: src/%.cpp
	$(CC) $(INC) $(CC_FLAGS) -c -o $@ $< 

clean:
	rm -rf bin/* $(OUT) $(OUT).exe $(PLAY) $(PLAY).exe
	@echo Clean done
	
shout:
	@echo $(SRC)
	@echo $(OBJ)
