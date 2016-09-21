#############################
#                           #
#  Sport game's makefile		#
# author : @CésarCOllé 			#
#   19/09/2016              #
#############################


EXECUTABLE=executable.exe
COMP=gcc
FLAGS=-Wall -pthread -lm
DSRC=src/
DOBJ=obj/
DINC=inc/

OBJ=$(DOBJ)elements.o $(DOBJ)main.o $(DOBJ)launcher_version.o

$(EXECUTABLE):$(OBJ)
	$(COMP) $(FLAGS) $(OBJ) -o $(EXECUTABLE)

$(DOBJ)main.o:$(DSRC)main.c
	$(COMP) $(FLAGS) -c $< -o $@

$(DOBJ)elements.o:$(DSRC)elements.c $(DINC)elements.h
	$(COMP) $(FLAGS) -c $< -o $@

$(DOBJ)launcher_version.o:$(DSRC)launcher_version.c $(DINC)launcher_version.h
	$(COMP) $(FLAGS) -c $< -o $@ -pthread



clean:
	rm -f ./src/*~ ./obj/*.o ./*~ ./inc/*~ ./*.exe
