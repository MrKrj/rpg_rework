/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include "datastructure.h"
#include "prototypes.h"


static int event(__attribute__((unused)) core_t *core)
{
    return 0;
}

static int update(__attribute__((unused)) core_t *core)
{
    return 0;
}

static int display(__attribute__((unused)) core_t *core)
{
    sfRenderWindow_drawSprite(
        core->window->window,
        toGraphics(core->curr->entities->comps->getComp(core->curr->entities->comps, GRAPHICS))->sprite,
        NULL
    );
    return 0;
}

scene_t *Intro(core_t *core)
{
    scene_t *intro = malloc(sizeof(scene_t));

    if (intro == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }

    // Set methods
    intro->event = &event;
    intro->update = &update;
    intro->display = &display;
    intro->entities = core->entities->getEntity(core->entities, "contents/entities/background.ini")->gameObject;

    return intro;
}

void Dtr_Intro(scene_t *intro)
{
    free(intro);
}