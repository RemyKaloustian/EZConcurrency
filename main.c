//Install SDL2 : sudo apt-get install libsdl2-dev
//Basic command to compile : gcc main.c -lSDL2-2.0
//Run : ./a.out

#include "UITools.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* args[] )
{

  //CE main récapitule comment ça va se passer
  //T'as qu'à installer SDL (voir plus haut), rajouter l'option à la compilation et exécuter

  //J'ai tout mis dans un fichier UITools.h. Les fonctions dont tu as besoin commencent par "UI_".

  printf("WORKED ! \n");

//Pour initialiser la fenêtre, t'as juste à l'appeler une fois au début du programme.
  UI_Init();


  int quit = 0;
//t'embêtes pas avec la boucle, je l'ai mise pour que tu voies à quoi ça ressemble.
//Comme on va dessiner & update à chaque déplacement, c'est pas la peine de faire une boucle
  while(quit != 1)
  {
    //Donc à chaque déplacement
    //On dessine les murs
    UI_draw_walls();

    //for each personne dans la liste des personnes
    //{
        //Tu passes le x et y de la personne, &person c'est le pixel de personne, j'ai essayé sans, ça marche pas (nik ses morh la SDL)
        UI_draw_person(&person,400,100);
    //}

    //On update la fenêtre
    UI_update();


//ça c'est à mettre juste après update
//vire le quit = 1; et le break; pour l'instant
    if(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
          quit = 1;
          break;
      }
    }
  }

  return 0;
}
