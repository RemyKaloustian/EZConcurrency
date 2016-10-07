#ifndef MOVEMENT
#define MOVEMENT


#define X_FINAL 15
struct movement{
    grid * ptr_grid;
    int left_bound;
    int right_bound;
    int top_bound;
    int bottom_bound;
};

void *  automata_movement(void * ptr_data );


int is_in_bounds( person *current_person, struct  movement *current_movement);


void move_person(grid * current_movement, person *current_person);

int is_in_bounds(person *current_person, struct movement *current_movement);


#endif
