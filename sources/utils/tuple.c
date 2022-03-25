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

static int getValueIndex(char *line)
{
    int i = 0;

    for (; line[i] != '\0' && line[i] != '='; ++i);
    return ++i;
}


static int getKeySize(char *line)
{
    int i = 0;

    for (; line[i] != '\0' && line[i] != '='; ++i);
    return i;
}

tuple_t *Tuple(char *line)
{
    int i = 0;
    tuple_t *tuple = malloc(sizeof(tuple_t));
    int valueSize = strlen(line) - getKeySize(line);

    tuple->key = malloc(sizeof(char) * (getKeySize(line) + 1));
    for (i = 0; line[i] != '='; ++i)
        tuple->key[i] = line[i];
    tuple->key[getKeySize(line)] = '\0';
    tuple->value = malloc(sizeof(char) * (valueSize));
    for (int j = 0, i = getValueIndex(line); line[i] != '\0'; ++i, ++j)
        tuple->value[j] = line[i];
    if (tuple->value[valueSize - 2] == '\n')
        tuple->value[valueSize - 2] = '\0';
    else
        tuple->value[valueSize - 1] = '\0';
    return tuple;
}

tuple_t *TupleFromFile(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    int read = 0;

    read = getline(&line, &len, fp);
    if (read > 1)
        return Tuple(line);
    return NULL;
}

void Dtr_Tuple(tuple_t *tuple)
{
    free(tuple->key);
    free(tuple->value);
    free(tuple);
}