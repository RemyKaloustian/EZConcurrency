#include "../inc/elements.h"


void
set_x (cell * my_cell, int x)
{
  my_cell->x = x;
}

void
set_y (cell * my_cell, int y)
{
  my_cell->y = y;
}

void
set_cell_content (cell * my_cell, cell_content_type content)
{
  my_cell->content = content;
}

void
init_cell (cell * my_cell, int x, int y, cell_content_type content)
{
  my_cell->x = x;
  my_cell->y = y;
  my_cell->content = content;
}

void
add_cell_to_grid (grid * my_grid, int x, int y, cell my_cell)
{
  my_grid->matrix[x][y] = my_cell;
}

void drawn_entity(grid * map, int x, int y){
  for(int i=x; i<x+DEFAULT_PEOPLE_SIZE; i++){
      for(int j=y; j<y+DEFAULT_PEOPLE_SIZE; j++){
          //printf("Add PERSON at x:%d y:%d\n", i, j);
          map->matrix[i][j].content = PERSON;
      }

    }
}

void
add_walls (grid * my_grid)
{
  //First WALL
  for (int x = DEFAULT_WALL_1_X; x < DEFAULT_WALL_WIDTH; x++)
    {
      for (int y = 0; y < my_grid->height; y++)
	{
	  // exit
	  if (y < (my_grid->height / 2) - (DEFAULT_EXIT_HEIGHT_WALL_1 / 2)
	      || y >=
	      (my_grid->height / 2) + (DEFAULT_EXIT_HEIGHT_WALL_1 / 2))
	    {
	      my_grid->matrix[x][y].content = WALL;
	    }
	}
    }
  //Second WALL
  for (int x = 0; x < DEFAULT_WALL_WIDTH; x++)
    {
      for (int y = 0; y < my_grid->height; y++)
	{
	  // exit
	  if (y < (my_grid->height / 2) - (DEFAULT_EXIT_HEIGHT_WALL_2 / 2)
	      || y >=
	      (my_grid->height / 2) + (DEFAULT_EXIT_HEIGHT_WALL_2 / 2))
	    {
	      my_grid->matrix[x + DEFAULT_WALL_2_X][y].content = WALL;
	    }
	}
    }
}

void
init_grid (grid * my_grid, int width, int height)
{
  my_grid->height = height;
  my_grid->width = width;

  for (int x = 0; x < width; x++)
    {
      for (int y = 0; y < height; y++)
	{
	  cell new_cell;
	  init_cell (&new_cell, x, y, EMPTY);
	  add_cell_to_grid (my_grid, x, y, new_cell);
	}
    }
  add_walls (my_grid);
}

int
is_available_coords (grid * my_grid, int x, int y)
{
  if (x < 0 || x > my_grid->width - DEFAULT_PEOPLE_SIZE - 1
      || y < 0 || y > my_grid->height - DEFAULT_PEOPLE_SIZE - 1)
//
    return -1;
  for (int i = x; i < x + DEFAULT_PEOPLE_SIZE; i++)
    {
      for (int j = y; j < y + DEFAULT_PEOPLE_SIZE; j++)
	{
	  if (my_grid->matrix[i][j].content != EMPTY)
	    return -1;
	}
    }
  //success
  return 0;
}

/*
    This function place some peapole at random place inside the left area after the 2 walls
*/
void
random_populate_grid (grid * my_grid, int people)
{
  int x, y;
  int min_x = DEFAULT_WALL_2_X + DEFAULT_WALL_WIDTH;
  int max_x = my_grid->width - DEFAULT_PEOPLE_SIZE;
  int min_y = 0;
  int max_y = my_grid->height - DEFAULT_PEOPLE_SIZE;
  my_grid->population = calloc (people, sizeof (person));

  //printf("minx:%d, maxx:%d, miny:%d maxY:%d", min_x, max_x, min_y, max_y);
  for (int i = 0; i < people; i++)
    {
      // find coord not given by user
      do
	{
	  //rand()%(max-min+1) + min;
	  x = rand () % (max_x - min_x + 1) + min_x;
	  y = rand () % (max_y - min_y + 1) + min_y;
	}
      while (is_available_coords (my_grid, x, y) < 0);
      drawn_entity(my_grid, x, y);
    }

}


//function will be executed by the thread
void *
move_elem ()
{
  printf ("In the thread, moving the elements !!\n");
  sleep (1);
  return NULL;			//function must return something
}

void affic_grid(grid * map){
  for (size_t i = 0; i < DEFAULT_GRID_HEIGHT; i++) {
    for (size_t j = 0; j < DEFAULT_GRID_WIDTH; j++) {
      switch ( map->matrix[i][j].content) {
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
    putchar("\n");
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
