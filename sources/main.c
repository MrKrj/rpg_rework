/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include "prototypes.h"
#include "ret_values.h"

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av)
{
    core_t *core = Core();

    if (core == NULL)
        return ERR_MEMORY;
    core->run(core);
    Dtr_Core(core);
    return SUCCESS;
}
