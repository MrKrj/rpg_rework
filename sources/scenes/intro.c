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

/* BUTTON CALLS */

void Intro_passToMenu(UNUSED core_t *core) {
    gameObject_t *gameObject = getGameObjectByName(core->curr->entities, "music");
    comp_t *comp;
    music_t *music;
    
    comp = gameObject->comps->getComp(gameObject->comps, MUSIC);
    if (comp != NULL) {
        music = toMusic(comp);
        sfMusic_stop(music->music);
    }
    Dtr_Scene(core->curr);
    core->curr = Scene(core, "contents/game/game.ini", MENU, FALSE);
}
