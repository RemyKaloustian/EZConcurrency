#include "../inc/elements.h"
#include "../inc/launcher_version.h"


struct movement{
  struct grid * ptr_grid;
  int left_bound;
  int right_bound;
  int top_bound;
  int bottom_bound;
}




void *  automata_movement(void * param_ptr_data ){

  struct movement * ptr_data = param_ptr_data; 

  //going through the list of person
  for(int i = 0; ptr_data->ptr_grid->population  ; ++i){

//Checking if the person is within the bounds of the thread
    if(is_in_bounds(ptr_data->ptr_grid->population[i], ptr_data)){
      //Move the person
      //We need the ptr_date cuz we need to check the bounds and the spaces around the current person 
      //We also need the person coordinates, so we pass the person
      move_person( ptr_data, ptr_data->ptr_grid->population[i]){


      }

    }
  }
}//automata_movement()

int is_in_bounds(struct * person current_person, struct * movement current_movement){

  
  int to_return = 0;
  if(current_person->x > current_movement->left_bound && current_person->x < current_movement-> right_bound &&
  current_person->y > current_movement->top_bound && current_person->y< current_movement-> bottom_bound ){
    //The person is on the right chunk of the map
    to_return = 1;
  }

  return to_return;
}//is_in_bounds()


void move_person(struct movement * current_movement, struct * person current_person){

//First we check if the place we wanna go is free, if not checking other places.
//Changing the person coordinates
}//move_person()
