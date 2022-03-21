/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "datastructure.h"

timed_t *Timed()
{
    timed_t *timed = malloc(sizeof(timed_t));

    if (timed == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }
    
    // Set variables
    timed->clock = sfClock_create();
    timed->elapsed = 0;
    return timed;
}

void Dtr_Timed(timed_t *timed)
{
    free(timed);
}