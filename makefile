#############################
#                           #
#  Sport game's makefile    #
#                           #
#############################

OBJ="LOL"
SOURCE=$(OBJ:.o=.cpp)
EXECUTABLE=executable.exe




clean:
	rm -f ./src/*~ ./obj/*.o ./*~ ./inc/*~ ./*.exe
