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
    {"[graphics]\n", &Graphics}
};

gameObject_t *GameObject(core_t *core, char *config)
{
    static int id = 0;
    gameObject_t *gO = malloc(sizeof(gameObject_t));
    FILE *fp = fopen(config, "r");
    char *line = NULL;
    size_t len = 0;

    if (gO == NULL || fp == NULL)
        return NULL;

    gO->id = id++;
    gO->comps = CompDict();
    while (getline(&line, &len, fp) != -1)
        for (int i = 0; i < 1; ++i)
            if (strcmp(line, compCtors[i].type) == 0)
                gO->comps->addComp(gO->comps, compCtors[i].createComp(core, fp));
    return gO;
}

void Dtr_GameObject(gameObject_t *gO)
{
    free(gO);
}