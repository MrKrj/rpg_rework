/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "datastructure.h"
#include "prototypes.h"
#include "ret_values.h"


int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av)
{
    core_t *core = Core();

    if (core == NULL)
        return ERR_MEMORY;
    core->run(core);
    Dtr_Core(core);

    // void *data = malloc(sizeof(int));
    // *((int *)data) = 5;

    // void *tmp = malloc(sizeof(mdr_t));
    // *((mdr_t *)tmp) = (mdr_t){1};

    // ((mdr_t *)tmp)->a = 4;

    // free(data);


    // gameObject_t *parallax_background = gameObject("contents/entities/parallax_background.ini");    


    return SUCCESS;
}
