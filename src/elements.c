/**
 * this part will manage all the element needed by the map .
 * Indeed we insert the declaration of these elemets and
 * also the initialisation.
 *
 * author : @CésarCollé
 * 08/10/2016
 *
 **/


#include "../inc/elements.h"
#include "../inc/designer.h"

void
init_cell(cell *my_cell, int x, int y, cell_content_type content) {
    my_cell->x = x;
    my_cell->y = y;
    my_cell->content = content;
}

void
add_cell_to_grid(grid *my_grid, int x, int y, cell my_cell) {
    my_grid->matrix[x][y] = my_cell;
}

/**
 * Adding all the walls on the map.
 * We produce hard values because these values will stay the same
 * in the customer's specifications.
 * */

void
add_walls(grid *my_grid) {
    // creation 1st wall
    int cpt = 0;
    int cpt1 = 0;
    for (int y = 0; y < DEFAULT_GRID_HEIGHT; ++y) {
        for (int x = 0; x < DEFAULT_GRID_WIDTH  ; ++x) {
            if ( y < 60 && x < 16){
                cpt++;
                my_grid->matrix[y][x].content = WALL;
            }
            if ( y > 67 && x < 16){
                cpt++;
                my_grid->matrix[y][x].content = WALL;
            }
            if ( y < (128/2 - 8 ) && (x < 128 && x > (128-16) )){
                my_grid->matrix[y][x].content = WALL;
                cpt1++;
            }
            if ( y > (128/2 + 8) && ( x > (128 - 16)) && (x < 128) ){
                my_grid->matrix[y][x].content = WALL;
                cpt1++;
            }

        }

    }
}

void
init_grid(grid *my_grid, int width, int height) {
    my_grid->height = height;
    my_grid->width = width;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cell new_cell;
            init_cell(&new_cell, x, y, EMPTY);
            add_cell_to_grid(my_grid, x, y, new_cell);
        }
    }
    add_walls(my_grid);
}

int  is_available_coords(grid *my_grid, int x, int y) {
    for (int i = y; i < y + DEFAULT_PEOPLE_SIZE-1; i++) {
        for (int j = x; j > x - DEFAULT_PEOPLE_SIZE; j--) {
            if (my_grid->matrix[i][j].content != EMPTY) {
                return 1;
            }
        }
    }
    //success
    return 0;
}

/*
    This function place some people at random place inside the left area after the 2 walls
*/
void
random_populate_grid(grid *my_grid, int people) {
    unsigned int x, y;
    int min_x = DEFAULT_WALL_2_X + DEFAULT_WALL_WIDTH;
    int max_x = DEFAULT_GRID_WIDTH - DEFAULT_PEOPLE_SIZE;
    int min_y = 0;
    int max_y = DEFAULT_GRID_HEIGHT - DEFAULT_PEOPLE_SIZE;
    my_grid->population = calloc(people, sizeof(person));
    for (int i = 0; i < people; ++i) {
        //going through all the persons
        do{
            //Setting the coordinates
            x = rand() % (max_x - min_x + 1) + min_x;
            y = rand() % (max_y - min_y + 1) + min_y;
        }while(is_available_coords(my_grid, x, y) && x > 12 && y > 0);
        // fill the grid with ew value
        my_grid->population[i].x = x;
        my_grid->population[i].y = y;
        my_grid->population[i].current_status = AVAILABLE;
        // put entity On the grid !
        draw_entity(my_grid,x, y);
    }
}
