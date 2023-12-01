CC=g++
CFLAGS=-I. -g
OBJ = GameMechs.o objPos.o objPosArrayList.o MacUILib.o Player.o Project.o Food.o 
DEPS = *.h
#POSTLINKER = -lncurses   ## uncomment this if on Linux
EXEC = Project
#rm -r ${OBJ} ${EXEC} ${EXEC}.exe ## this line should be added under clean if on Linux!

%.o: %.cpp $(DEPENDS)
	$(CC) -c -o $@ $< $(CFLAGS)

${EXEC} : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) ${POSTLINKER}

clean :
	del *.o
