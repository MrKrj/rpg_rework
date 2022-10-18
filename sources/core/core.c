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


static int event(core_t *core)
{
    while (sfRenderWindow_pollEvent(core->window->window, &core->window->event)) {
        if (core->window->event.type == sfEvtClosed)
            sfRenderWindow_close(core->window->window);
        core->curr->event(core);
    }
    return 0;
}

static int update(core_t *core)
{
    core->curr->update(core);
    return 0;
}

static int display(core_t *core)
{
    sfRenderWindow_clear(core->window->window, sfBlack);
    core->curr->display(core);
    sfRenderWindow_display(core->window->window);
    return 0;
}

static int run(core_t *core)
{
    sfClock_restart(core->time->clock);
    while (sfRenderWindow_isOpen(core->window->window)) {
        core->event(core);
        core->time->elapsed = sfClock_restart(core->time->clock)MICRO;
        core->update(core);
        core->display(core);
    }
    return 0;
}

core_t *Core(void)
{
    core_t *core = malloc(sizeof(core_t));

    if (core == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }

    // Set methods
    core->event = &event;
    core->update = &update;
    core->display = &display;
    core->run = &run;

    // Set variables
    core->window = Window("my_rpg", (sfVector2i){1280, 768}, 32);
    if (core->window->window == NULL)
        return NULL;
    core->time = Timed();
    core->sprites = SpriteDict();
    core->fonts = FontDict();
    // core->curr = Game(core);
    core->curr = Scene(core, "contents/game/game.ini", GAME, TRUE);
    return core;
}

void Dtr_Core(core_t* core)
{
    Dtr_Window(core->window);
    Dtr_Timed(core->time);
    Dtr_SpriteDict(core->sprites);
    Dtr_FontDict(core->fonts);
    Dtr_Scene(core->curr);
    free(core);
}