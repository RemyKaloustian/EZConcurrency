#ifndef MOVEMENT
#define MOVEMENT

void *  automata_movement(void * ptr_data );


int is_in_bounds(struct * person current_person, struct * movement current_movement);


void move_person(struct movement * current_movement, struct * person current_person);



#endif
