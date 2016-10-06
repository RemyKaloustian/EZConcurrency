#ifndef MOVEMENT
#define MOVEMENT

void *  automata_movement(void * ptr_data );


int is_in_bounds( person *current_person, struct  movement *current_movement);


void move_person(struct movement * current_movement, person *current_person);

struct movement{
    grid * ptr_grid;
    int left_bound;
    int right_bound;
    int top_bound;
    int bottom_bound;
};




#endif
