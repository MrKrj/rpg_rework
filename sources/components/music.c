/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "datastructure.h"
#include "prototypes.h"

music_t *toMusic(comp_t *comp)
{
    if (comp->type != MUSIC)
        return NULL;
    return (music_t *)comp->comp;
}

static void setPath(UNUSED core_t *core, music_t *component, tuple_t *tuple)
{
    component->music = sfMusic_createFromFile(tuple->value);
}

static void setNow(UNUSED core_t *core, music_t *component, tuple_t *tuple)
{
    if (strcmp(tuple->value, "true") == 0 && component->music != NULL)
        sfMusic_play(component->music);
}

static void setLoop(UNUSED core_t *core, music_t *component, tuple_t *tuple)
{
    if (strcmp(tuple->value, "true") == 0 && component->music != NULL)
        sfMusic_setLoop(component->music, sfTrue);
}

static void setVolume(UNUSED core_t *core, music_t *component, tuple_t *tuple)
{
    if (component->music != NULL)
        sfMusic_setLoop(component->music, atof(tuple->value));
}

static void setCooldown(UNUSED core_t *core, music_t *component, tuple_t *tuple)
{
    component->cooldown = atoi(tuple->value);
}

typedef struct {
    char *key;
    void (*setParam)(core_t *, music_t *, tuple_t *);
} musicParamsCtor_t;

const musicParamsCtor_t musicParamsCtors[] = {
    {"path", &setPath},
    {"now", &setNow},
    {"loop", &setLoop},
    {"volume", &setVolume},
    {"cooldown", &setCooldown},
};

comp_t *Music(core_t *core, FILE *fp)
{
    tuple_t *tuple = NULL;
    comp_t *comp = malloc(sizeof(comp_t));
    music_t *component = malloc(sizeof(music_t));

    if (comp == NULL || component == NULL)
        return NULL;
    component->music = NULL;
    component->cooldown = 0;
    do {
        tuple = TupleFromFile(fp);
        if (tuple != NULL) {
            for (int i = 0; i < (int)(sizeof(musicParamsCtors) / sizeof(musicParamsCtor_t)); ++i)
                if (strcmp(tuple->key, musicParamsCtors[i].key) == 0)
                    musicParamsCtors[i].setParam(core, component, tuple);
            Dtr_Tuple(tuple);
        }
    } while (tuple != NULL);
    comp->type = MUSIC;
    comp->comp = component;
    comp->next = NULL;
    return comp;
}

void Dtr_Music(music_t *music)
{
    sfMusic_destroy(music->music);
    free(music);
}