
# gobang: board.o game_logic.o game_state.o input.o main.o
# 	gcc -o gobang board.o game_logic.o game_state.o input.o main.o
# objects作为变量代替所有的.o
objects = board.o game_logic.o game_state.o input.o main.o
gobang: $(objects)
	gcc -o gobang $(objects)

# 使用gcc -M board.c可以查看.o的依赖
# board.o: board.c board.h constants.h
# 	gcc -c board.c

# game_logic.o: game_logic.c game_logic.h constants.h board.h
# 	gcc -c game_logic.c

# game_state.o: game_state.c game_state.h constants.h board.h game_logic.h
# 	gcc -c game_state.c

# input.o: input.c input.h
# 	gcc -c input.c
	
# main.o: main.c board.h constants.h game_state.h input.h
# 	gcc -c main.c

# 自动推导规则
board.o: board.h constants.h
game_logic.o: game_logic.h constants.h board.h
game_state.o: game_state.h constants.h board.h game_logic.h
input.o: input.h
main.o: board.h constants.h game_state.h input.h

.PHONY: clean
clean:
	-rm -rf gobang $(objects)
#	-rm -rf board.o game_logic.o game_state.o input.o main.o
