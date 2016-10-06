#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/movement.h"

#define MIN_FINAL_X 60
#define MAX_FINAL_X 67



void *  automata_movement(void * param_ptr_data ){

  struct movement * ptr_data = param_ptr_data; 

  //going through the list of person
  for(int i = 0; ptr_data->ptr_grid->population  ; ++i){

//Checking if the person is within the bounds of the thread
    if(is_in_bounds(&ptr_data->ptr_grid->population[i], ptr_data)){
      //Move the person
      //We need the ptr_date cuz we need to check the bounds and the spaces around the current person
      //We also need the person coordinates, so we pass the person
      move_person( ptr_data, &ptr_data->ptr_grid->population[i]);


    }
  }
}//automata_movement()

int is_in_bounds( person *current_person, struct movement  * current_movement){

return (current_person->x > current_movement->left_bound && current_person->x < current_movement-> right_bound &&
  current_person->y > current_movement->top_bound && current_person->y< current_movement-> bottom_bound )
    //The person is on the right chunk of the map
    }//is_in_bounds()


int check_down(grid * map, int x, int y ){
  int line = y + DEFAULT_PEOPLE_SIZE;
  for (int j = x; j < x - DEFAULT_PEOPLE_SIZE; j--){
    if (map->matrix[line][j].content){
      return -1;
    }
  }
  return 1;
}

int check_up(grid * map, int x, int y ){
  if ()
  for (int j = y; j < y - DEFAULT_PEOPLE_SIZE; j--){
    if (map->matrix[x][j].content){
      return -1;
    }
  }
  return 1;
}


void move_person( struct movement * current_movement,  person * current_person){


if(current_person->y < MIN_FINAL_X && current_movement->ptr_grid->matrix[current_person->x][current_person->y+1]->){

}
else if(current_person->y > MAX_FINAL_X){

}

else {

}
//First we check if the place we wanna go is free, if not checking other places.
//Changing the person coordinates
}//move_person()
