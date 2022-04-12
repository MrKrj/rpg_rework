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

button_t *toButton(comp_t *comp)
{
    if (comp->type != BUTTON)
        return NULL;
    return (button_t *)comp->comp;
}

ptrFct_t buttonPtrFct[] = {
    {"Intro_passToMenu", &Intro_passToMenu}
};

static void setOnClicked(UNUSED core_t *core, button_t *component, tuple_t *tuple)
{
    for (int i = 0; i < 1; ++i)
        if (strcmp(buttonPtrFct[i].name, tuple->value) == 0)
            component->onClicked = buttonPtrFct[i].ptr;
}

typedef struct {
    char *key;
    void (*setParam)(core_t *, button_t *, tuple_t *);
} buttonParamsCtor_t;

const buttonParamsCtor_t buttonParamsCtors[] = {
    {"onClicked", &setOnClicked},
};

comp_t *Button(core_t *core, FILE *fp)
{
    tuple_t *tuple = NULL;
    comp_t *comp = malloc(sizeof(comp_t));
    button_t *component = malloc(sizeof(button_t));

    if (comp == NULL || component == NULL)
        return NULL;
    component->onClicked = NULL;
    do {
        tuple = TupleFromFile(fp);
        if (tuple != NULL) {
            for (int i = 0; i < (int)(sizeof(buttonParamsCtors) / sizeof(buttonParamsCtor_t)); ++i)
                if (strcmp(tuple->key, buttonParamsCtors[i].key) == 0)
                    buttonParamsCtors[i].setParam(core, component, tuple);
            Dtr_Tuple(tuple);
        }
    } while (tuple != NULL);
    comp->type = BUTTON;
    comp->comp = component;
    comp->next = NULL;
    return comp;
}

void Dtr_Button(button_t *button)
{
    free(button);
}