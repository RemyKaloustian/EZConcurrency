#include "../inc/elements.h"


void
set_x(cell *my_cell, int x) {
    my_cell->x = x;
}

void
set_y(cell *my_cell, int y) {
    my_cell->y = y;
}

void
set_cell_content(cell *my_cell, cell_content_type content) {
    my_cell->content = content;
}

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

void draw_entity(grid *map, int x, int y) {
    for (int i = y; i < y + DEFAULT_PEOPLE_SIZE; i++) {
        for (int j = x; j > x - DEFAULT_PEOPLE_SIZE; j--) {
            map->matrix[i][j].content = PERSON;
        }

    }
}

void delete_entity(grid *map, int x, int y) {
    for (int i = y; i < y + DEFAULT_PEOPLE_SIZE; i++) {
        for (int j = x; j > x - DEFAULT_PEOPLE_SIZE; j--) {
            map->matrix[i][j].content = EMPTY;
        }

    }
}

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
    printf("cpt ====== %d cpt1 = %d \n", cpt, cpt1);
}

void
init_grid(grid *my_grid, int width, int height) {
    printf("init \n");
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

int
is_available_coords(grid *my_grid, int x, int y) {
    if (x < 0 || x > my_grid->width - DEFAULT_PEOPLE_SIZE - 1
        || y < 0 || y > my_grid->height - DEFAULT_PEOPLE_SIZE - 1)
//
        return -1;
    for (int i = x; i < x + DEFAULT_PEOPLE_SIZE; i++) {
        for (int j = y; j < y + DEFAULT_PEOPLE_SIZE; j++) {
            if (my_grid->matrix[i][j].content != EMPTY)
                return -1;
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
    int x, y;
    int min_x = DEFAULT_WALL_2_X + DEFAULT_WALL_WIDTH;
    int max_x = DEFAULT_GRID_WIDTH - DEFAULT_PEOPLE_SIZE;
    int min_y = 0;
    int max_y = DEFAULT_GRID_HEIGHT - DEFAULT_PEOPLE_SIZE;
    printf("INIT GRID ==== %d\n",people);
    my_grid->population = calloc(people, sizeof(person));
    printf("random \n");
    //printf("minx:%d, maxx:%d, miny:%d maxY:%d", min_x, max_x, min_y, max_y);
    int tab[4] = {19, 3, 19,100 };
    //for (int i = 0; i < people; i++) {
        //x = rand() % (max_x - min_x + 1) + min_x;
        //y = rand() % (max_y - min_y + 1) + min_y;
        // printf("draw entity \n");
       // drawn_entity(my_grid, x, y);
    //}
    my_grid->population[0].x = tab[0];
    my_grid->population[0].y = tab[1];
    my_grid->population[0].current_status = AVAILABLE;

    my_grid->population[1].x = tab[2];
    my_grid->population[1].y = tab[3];
    my_grid->population[1].current_status = AVAILABLE;

    draw_entity(my_grid,tab[0], tab[1]);
    draw_entity(my_grid,tab[2], tab[3]);

    printf("fin \n\n\n");
    affic_grid(my_grid);
}


//function will be executed by the thread
void *
move_elem() {
    printf("In the thread, moving the elements !!\n");
    //sleep (1);
    return NULL;            //function must return something
}

void affic_grid(grid *map) {
    for (size_t i = 0; i < DEFAULT_GRID_HEIGHT; i++) {
        for (size_t j = 0; j < DEFAULT_GRID_WIDTH; j++) {
            switch (map->matrix[i][j].content) {
                case EMPTY:
                    putchar('-');
                    break;
                case WALL:
                    putchar('|');
                    break;
                case PERSON:
                    putchar('x');
                    break;
                default :
                    fprintf(stderr, "erreur affichage\n");
                    exit(1);
            }
        }
        printf("\n");
    }
}

/*
int main(){
    grid simulation_grid;
    for (size_t i = 0; i < DEFAULT_GRID_HEIGHT; i++) {
      memset(simulation_grid.matrix[i], 0,DEFAULT_WALL_WIDTH);

    }
    init_grid(&simulation_grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT);
    affic_grid(&simulation_grid);
    random_populate_grid(&simulation_grid, 32);
    printf("\n\n");
    affic_grid(&simulation_grid);
    return 0;
}
*/
