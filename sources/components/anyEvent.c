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

anyEvent_t *toAnyEvent(comp_t *comp)
{
    if (comp->type != ANY_EVENT)
        return NULL;
    return (anyEvent_t *)comp->comp;
}

ptrFct_t anyEventPtrFct[] = {
    {"Intro_pass", &Intro_pass},
};

static void setOnKeyPressed(UNUSED core_t *core, anyEvent_t *component, tuple_t *tuple)
{
    for (int i = 0; i < (int)(sizeof(anyEventPtrFct) / sizeof(ptrFct_t)); ++i)
        if (strcmp(anyEventPtrFct[i].name, tuple->value) == 0)
            component->onKeyPressed = anyEventPtrFct[i].ptr;
}

static void setOnMousePressed(UNUSED core_t *core, anyEvent_t *component, tuple_t *tuple)
{
    for (int i = 0; i < (int)(sizeof(anyEventPtrFct) / sizeof(ptrFct_t)); ++i)
        if (strcmp(anyEventPtrFct[i].name, tuple->value) == 0)
            component->onMousePressed = anyEventPtrFct[i].ptr;
}

typedef struct {
    char *key;
    void (*setParam)(core_t *, anyEvent_t *, tuple_t *);
} anyEventParamsCtor_t;

const anyEventParamsCtor_t anyEventParamsCtors[] = {
    {"onKeyPressed", &setOnKeyPressed},
    {"onMousePressed", &setOnMousePressed},
};

comp_t *AnyEvent(core_t *core, FILE *fp)
{
    tuple_t *tuple = NULL;
    comp_t *comp = malloc(sizeof(comp_t));
    anyEvent_t *component = malloc(sizeof(anyEvent_t));

    if (comp == NULL || component == NULL)
        return NULL;
    component->onKeyPressed = NULL;
    component->onMousePressed = NULL;
    do {
        tuple = TupleFromFile(fp);
        if (tuple != NULL) {
            for (int i = 0; i < (int)(sizeof(anyEventParamsCtors) / sizeof(anyEventParamsCtor_t)); ++i)
                if (strcmp(tuple->key, anyEventParamsCtors[i].key) == 0)
                    anyEventParamsCtors[i].setParam(core, component, tuple);
            Dtr_Tuple(tuple);
        }
    } while (tuple != NULL);
    comp->type = ANY_EVENT;
    comp->comp = component;
    comp->next = NULL;
    return comp;
}

void Dtr_AnyEvent(anyEvent_t *anyEvent)
{
    free(anyEvent);
}