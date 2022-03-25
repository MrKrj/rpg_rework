/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include "prototypes.h"
#include "ret_values.h"

int main(UNUSED int ac, UNUSED char **av)
{
    core_t *core = Core();

    if (core == NULL)
        return ERR_MEMORY;
    core->run(core);
    Dtr_Core(core);
    return SUCCESS;
}
