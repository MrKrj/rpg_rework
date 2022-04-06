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

static sfFont *getFontByName(fontDict_t *dict, char *name)
{
    fontEntry_t *copyList = dict->entries;

    if (copyList == NULL)
        return NULL;
    if (strcmp(copyList->name, name) == 0)
        return copyList->font;
    while (copyList->next != NULL) {
        if (strcmp(copyList->name, name) == 0)
            return copyList->font;
        copyList = copyList->next;
    }
    return NULL;   
}

static fontEntry_t *createFont(char *path, char *name)
{
    static int id = 0;
    fontEntry_t *newEntry = malloc(sizeof(fontEntry_t));

    if (!newEntry) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }
    newEntry->id = id++;
    newEntry->name = strdup(name);
    newEntry->font = sfFont_createFromFile(path);
    if (!newEntry->font) {
        write(2, "Cannot create font\n", 20);
        return NULL;
    }
    newEntry->next = NULL;
    return newEntry;
}

static sfFont *addFont(fontDict_t *dict, char *path, char *name)
{
    fontEntry_t *newEntry = createFont(path, name);
    fontEntry_t *copyList = dict->entries;

    if (newEntry == NULL)
        return NULL;
    if (dict->entries == NULL) {
        dict->entries = newEntry;
    } else {
        while (copyList->next != NULL)
            copyList = copyList->next;
        copyList->next = newEntry;
    }
    return newEntry->font;
}

static void deleteFont(fontEntry_t *entry)
{
    free(entry->name);
    sfFont_destroy(entry->font);
    free(entry);
}

static void deleteAllFonts(fontEntry_t *entry)
{
    if (entry == NULL)
        return;
    deleteAllFonts(entry->next);
    deleteFont(entry);
    entry = NULL;
}

fontDict_t *FontDict(void)
{
    fontDict_t *dict = malloc(sizeof(fontDict_t));

    if (dict == NULL) {
        write(2, "Not enough memory to allocate !\n", 32);
        return NULL;
    }
    dict->entries = NULL;
    dict->getFontByName = &getFontByName;
    dict->addFont = &addFont;
    return dict;
}

void Dtr_FontDict(fontDict_t *fontDict)
{
    deleteAllFonts(fontDict->entries);
    free(fontDict);
}