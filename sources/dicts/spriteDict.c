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

static sfSprite *getSpriteById(spriteDict_t *dict, unsigned int id)
{
    spriteEntry_t *copyList = dict->entries;

    if (copyList == NULL)
        return NULL;
    if (copyList->id == id)
        return sfSprite_copy(copyList->sprite);
    while (copyList->next != NULL) {
        if (copyList->id == id)
            return sfSprite_copy(copyList->sprite);
        copyList = copyList->next;
    }
    return NULL;
}

static sfSprite *getSpriteByName(spriteDict_t *dict, char *name)
{
    spriteEntry_t *copyList = dict->entries;

    if (copyList == NULL)
        return NULL;
    if (strcmp(copyList->name, name) == 0)
        return sfSprite_copy(copyList->sprite);
    while (copyList->next != NULL) {
        if (strcmp(copyList->name, name) == 0)
            return sfSprite_copy(copyList->sprite);
        copyList = copyList->next;
    }
    return NULL;   
}

static spriteEntry_t *createSprite(char *path, char *name)
{
    static int id = 0;
    spriteEntry_t *newEntry = malloc(sizeof(spriteEntry_t));

    if (!newEntry) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }
    newEntry->id = id++;
    newEntry->name = strdup(name);
    newEntry->texture = sfTexture_createFromFile(path, NULL);
    if (!newEntry->texture) {
        write(2, "Cannot create texture\n", 22);
        return NULL;
    }
    newEntry->sprite = sfSprite_create();
    sfSprite_setTexture(newEntry->sprite, newEntry->texture, sfTrue);
    newEntry->next = NULL;
    return newEntry;
}

static sfSprite *addSprite(spriteDict_t *dict, char *path, char *name)
{
    spriteEntry_t *newEntry = createSprite(path, name);
    spriteEntry_t *copyList = dict->entries;

    if (newEntry == NULL)
        return NULL;
    if (dict->entries == NULL) {
        dict->entries = newEntry;
    } else {
        while (copyList->next != NULL)
            copyList = copyList->next;
        copyList->next = newEntry;
    }
    return sfSprite_copy(newEntry->sprite);
}

static void deleteSprite(spriteEntry_t *entry)
{
    free(entry->name);
    sfSprite_destroy(entry->sprite);
    sfTexture_destroy(entry->texture);
    free(entry);
}

static void deleteAllSprites(spriteEntry_t *entry)
{
    if (entry == NULL)
        return;
    deleteAllSprites(entry->next);
    deleteSprite(entry);
    entry = NULL;
}

spriteDict_t *SpriteDict(void)
{
    spriteDict_t *dict = malloc(sizeof(spriteDict_t));

    if (dict == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }
    dict->entries = NULL;
    dict->getSpriteById = &getSpriteById;
    dict->getSpriteByName = &getSpriteByName;
    dict->addSprite = &addSprite;
    return dict;
}

void Dtr_SpriteDict(spriteDict_t *SpriteDict)
{
    deleteAllSprites(SpriteDict->entries);
    free(SpriteDict);
}