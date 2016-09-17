#EZCONCURRENCE

## By Matthieu Berger, César Collé, Rémy Kaloustian

##Thread application in C

tutorial thread : https://computing.llnl.gov/tutorials/pthreads/
Principle: Simulation of people moving on a grid and trying to get through an exit.

A person can either move towards the exit or not, but cannot go backwards.

Two execution times will be measured : One for the consumed CPU, another one for the real time (in seconds).



REPORT : We are graded on teh report, therefore, it must be excellent.

The report and the code must be coherent.
4-6 pages

Title, date, authors, introduction, what we did and understood, comment on our experience with the points described in teacher's powerpoint, Conclusion (what's good, not good, fast, slow , what did we detect...)


WHAT REALLY INTERESTS THE TEACHER : SYNCHRONIZATION.



"César: Invariant de boucle " <3


####Thursday 15/09/2016

Coding ideas : 

struct person with coordinates
struct map with matrix

Need an algorithm for map initialization and random person placement.

Need an algorithm for the shortest path (person movement)

Good habits (of César the maxi BG of the death):
-Modular
-Makefile
-indent
- '_' between words in names
-#define
-perror

