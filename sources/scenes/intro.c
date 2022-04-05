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


static int event(UNUSED core_t *core)
{
    return 0;
}

static int update(UNUSED core_t *core)
{
    return 0;
}

static int display(UNUSED core_t *core)
{
    gameObject_t *tmp = core->curr->entities;

    while (tmp != NULL) {
        sfRenderWindow_drawSprite(
            core->window->window,
            toGraphics(tmp->comps->getComp(tmp->comps, GRAPHICS))->sprite,
            NULL
        );
        tmp = tmp->next;
    }
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
    intro->entities = GameObjectsFromConfig(core, "contents/scenes/intro.ini");

    return intro;
}

void Dtr_Intro(scene_t *intro)
{
    free(intro);
}