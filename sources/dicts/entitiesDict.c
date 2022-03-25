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
#include "prototypes.h"
#include "ret_values.h"

static entity_t *getEntity(entitiesDict_t *dict, char *name)
{
    entity_t *copyList = dict->entities;

    if (strcmp(copyList->name, name) == 0)
        return copyList;
    while (copyList->next != NULL) {
        if (strcmp(copyList->name, name) == 0)
            return copyList;
        copyList = copyList->next;
    }
    return NULL;
}

static entity_t *addEntity(core_t *core, entitiesDict_t *dict, char *name)
{
    gameObject_t *newGameObject = GameObject(core, name);
    entity_t *newEntity = malloc(sizeof(entity_t));
    entity_t *tmp = dict->entities;

    newEntity->name = strdup(name);
    newEntity->gameObject = newGameObject;
    newEntity->next = NULL;
    if (tmp == NULL) {
        dict->entities = newEntity;
        return newEntity;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = newEntity;
    return newEntity;
}

static void deleteEntity(entity_t *comp)
{
    // comp->Dtr(comp); CREER LE FREE DE CHAQUE COMPOSENT
    free(comp);
}

static void deleteAllEntities(entity_t *comp)
{
    if (comp == NULL)
        return;
    deleteAllEntities(comp->next);
    deleteEntity(comp);
    comp = NULL;
}

entitiesDict_t *EntitiesDict(void)
{
    entitiesDict_t *dict = malloc(sizeof(entitiesDict_t));

    if (dict == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }

    dict->entities = NULL;
    dict->getEntity = &getEntity;
    dict->addEntity = &addEntity;
    return dict;
}

void Dtr_EntitiesDict(entitiesDict_t *entitiesDict)
{
    deleteAllEntities(entitiesDict->entities);
    free(entitiesDict);
}