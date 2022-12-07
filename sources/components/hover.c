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

hover_t *toHover(comp_t *comp)
{
    if (comp->type != HOVER)
        return NULL;
    return (hover_t *)comp->comp;
}

ptrFct_t ptrFct[] = {
    {"Game_hover_ChangeRight", &Game_hover_ChangeRight},
    {"Game_hover_ChangeLeft", &Game_hover_ChangeLeft}
};

static void setOnHover(UNUSED core_t *core, hover_t *component, tuple_t *tuple)
{
    for (int i = 0; i < (int)(sizeof(ptrFct) / sizeof(ptrFct_t)); ++i)
        if (strcmp(ptrFct[i].name, tuple->value) == 0)
            component->onHover = ptrFct[i].ptr;
}

typedef struct {
    char *key;
    void (*setParam)(core_t *, hover_t *, tuple_t *);
} hoverParamsCtor_t;

const hoverParamsCtor_t hoverParamsCtors[] = {
    {"onHover", &setOnHover},
};

comp_t *Hover(core_t *core, FILE *fp)
{
    tuple_t *tuple = NULL;
    comp_t *comp = malloc(sizeof(comp_t));
    hover_t *component = malloc(sizeof(hover_t));

    if (comp == NULL || component == NULL)
        return NULL;
    component->onHover = NULL;
    do {
        tuple = TupleFromFile(fp);
        if (tuple != NULL) {
            for (int i = 0; i < (int)(sizeof(hoverParamsCtors) / sizeof(hoverParamsCtor_t)); ++i)
                if (strcmp(tuple->key, hoverParamsCtors[i].key) == 0)
                    hoverParamsCtors[i].setParam(core, component, tuple);
            Dtr_Tuple(tuple);
        }
    } while (tuple != NULL);
    comp->type = HOVER;
    comp->comp = component;
    comp->next = NULL;
    return comp;
}

void Dtr_Hover(hover_t *hover)
{
    free(hover);
}