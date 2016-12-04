#############################
#                           #
#  Sport game's makefile	#
# author : @CésarCOllé 		#
#   19/09/2016              #
#############################
DEBUG=$(ARG)
COMP=gcc
FLAGS=-Wall -pthread  -lm  -std=c99 $(DEBUG) -O3
DSRC=src/
DOBJ=bin/
DINC=inc/
EXECUTABLE=$(DOBJ)executable.exe
GRAPH=-lSDL2-2.0


OBJ=$(DOBJ)elements.o $(DOBJ)main.o $(DOBJ)launcher_version.o $(DOBJ)threading_part.o  $(DOBJ)/movement.o \
$(DOBJ)multiple_threads.o $(DOBJ)designer.o $(DOBJ)movement_sem.o $(DOBJ)monitor.o $(DOBJ)movement_monitor.o

$(EXECUTABLE):$(OBJ)
	$(COMP) $(FLAGS) $(OBJ) -o $(EXECUTABLE)

$(DOBJ)main.o:$(DSRC)main.c
	$(COMP) $(FLAGS) -c $< -o $@

$(DOBJ)elements.o:$(DSRC)elements.c $(DINC)elements.h
	$(COMP) $(FLAGS) -c $< -o $@

$(DOBJ)launcher_version.o:$(DSRC)launcher_version.c $(DINC)launcher_version.h
	$(COMP) $(FLAGS) -c $< -o $@ -pthread

$(DOBJ)threading_part.o:$(DSRC)threading_part.c
	$(COMP) $(FLAGS) -c $< -o $@ -pthread

$(DOBJ)/movement.o:$(DSRC)movement.c
	$(COMP) $(FLAGS) -c $< -o $@ -pthread

$(DOBJ)multiple_threads.o:$(DSRC)multiple_threads.c
	$(COMP) $(FLAGS) -c $< -o $@ -pthread

$(DOBJ)designer.o:$(DSRC)designer.c
	$(COMP) $(FLAGS) -c $< -o $@ -pthread

$(DOBJ)movement_sem.o:$(DSRC)movement_sem.c
	$(COMP) $(FLAGS) -c $< -o $@ -pthread

$(DOBJ)monitor.o: $(DSRC)monitor.c
	$(COMP) $(FLAGS) -c $< -o $@ -pthread

$(DOBJ)movement_monitor.o:$(DSRC)movement_monitor.c
	$(COMP) $(FLAGS) -c $< -o $@

# $(DOBJ)UITools.o:$(DSRC)UITools.c $(DINC)UITools.h
# 	$(COMP) $(FLAGS) -c $< -o $@ -pthread

clean:
	rm -f ./src/*~ ./bin/*.o ./*~ ./inc/*~ ./bin/*.exe
