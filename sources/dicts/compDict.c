/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "datastructure.h"
#include "ret_values.h"

static comp_t *getComp(compDict_t *dict, compType_t type)
{
    comp_t *copyList = dict->comps;

    if (copyList->type == type)
        return copyList;
    while (copyList->next != NULL) {
        if (copyList->type == type)
            return copyList;
        copyList = copyList->next;
    }
    return NULL;
}

static comp_t *addComp(compDict_t *dict, comp_t *new)
{
    comp_t *tmp = dict->comps;

    if (tmp == NULL) {
        dict->comps = new;
        return new;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return new;
}

static void deleteComp(comp_t *comp)
{
    // comp->Dtr(comp); CREER LE FREE DE CHAQUE COMPOSENT
    free(comp);
}

static void deleteAllComps(comp_t *comp)
{
    if (comp == NULL)
        return;
    deleteAllComps(comp->next);
    deleteComp(comp);
    comp = NULL;
}

compDict_t *CompDict(void)
{
    compDict_t *dict = malloc(sizeof(compDict_t));

    if (dict == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }

    dict->comps = NULL;
    dict->getComp = &getComp;
    dict->addComp = &addComp;
    return dict;
}

void Dtr_CompDict(compDict_t *compDict)
{
    deleteAllComps(compDict->comps);
    free(compDict);
}