/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "datastructure.h"
#include "prototypes.h"

typedef struct {
    char *type;
    comp_t *(*createComp)(core_t *, FILE *);
} compCtor_t;

const compCtor_t compCtors[] = {
    {"[graphics]\n", &Graphics},
    {"[text]\n", &Text},
    {"[button]\n", &Button}
};

gameObject_t *GameObject(core_t *core, char *name, char *config)
{
    gameObject_t *gO = malloc(sizeof(gameObject_t));
    FILE *fp = fopen(config, "r");
    char *line = NULL;
    size_t len = 0;

    if (gO == NULL) {
        write(2, "Not enough memory to allocate\n", 30);
        return NULL;
    }
    if (fp == NULL) {
        free(gO);
        write(2, "Can't open file\n", 16);
        return NULL;
    }
    gO->comps = CompDict();
    while (getline(&line, &len, fp) != -1)
        for (int i = 0; i < (int)(sizeof(compCtors) / sizeof(compCtor_t)); ++i)
            if (strcmp(line, compCtors[i].type) == 0)
                gO->comps->addComp(gO->comps, compCtors[i].createComp(core, fp));
    gO->next = NULL;
    gO->name = strdup(name);
    return gO;
}

gameObject_t *addGameObject(core_t *core, gameObject_t *entities, char *name, char *config)
{
    gameObject_t *newGameObject = GameObject(core, name, config);
    gameObject_t *tmp = entities;

    if (entities == NULL)
        return newGameObject;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = newGameObject;
    return entities;
}

gameObject_t *GameObjectsFromConfig(core_t *core, char *config)
{
    FILE *fp = fopen(config, "r");
    char *line = NULL;
    size_t len = 0;
    tuple_t *tuple = NULL;
    gameObject_t *entities = NULL;

    if (fp == NULL) {
        write(2, "Can't open file\n", 16);
        return NULL;
    }
    while (getline(&line, &len, fp) != -1)
        if (strcmp(line, "[entities]\n") != 0) {
            tuple = Tuple(line);
            entities = addGameObject(core, entities, tuple->key, tuple->value);
            Dtr_Tuple(tuple);
        }
    return entities;
}

void Dtr_GameObject(gameObject_t *gO)
{
    free(gO);
}