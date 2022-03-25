/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#ifndef DATASTRUCTURE_H
    #define DATASTRUCTURE_H

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Config.h>
    #include <SFML/System.h>
    
    #define MICRO .microseconds / 1000000.f;
    #define UNUSED __attribute__((unused))

    /* ENTITIES DICT */

    struct gameObject_s;
    struct core_s;

    typedef struct entity_s {
        char *name;
        struct gameObject_s *gameObject;

        struct entity_s *next;
    } entity_t;

    typedef struct entitiesDict_s {
        entity_t *entities;

        entity_t *(*getEntity)(struct entitiesDict_s *, char *);
        entity_t *(*addEntity)(struct core_s *, struct entitiesDict_s *, char *);
    } entitiesDict_t;

    /* SPRITE DICT */

    typedef struct entry_s {
        unsigned int id;
        char *name;
        sfTexture *texture;
        sfSprite *sprite;

        struct entry_s *next;
    } entry_t;

    typedef struct spriteDict_s {
        entry_t *entries;

        sfSprite *(*getSpriteById)(struct spriteDict_s *, unsigned int);
        sfSprite *(*getSpriteByName)(struct spriteDict_s *, char *);
        sfSprite *(*addSprite)(struct spriteDict_s *, char *, char *);
    } spriteDict_t;


    /* COMPONENTS DICT */

    typedef struct {
        char *key;
        char *value;
    } tuple_t;

    typedef enum compType {
        GRAPHICS
    } compType_t;

    typedef struct {
        sfSprite *sprite;
    } graphics_t;

    typedef struct comp_s {
        compType_t type;
        void *comp;

        struct comp_s *next;
    } comp_t;

    typedef struct compDict_s {
        comp_t *comps;

        comp_t *(*getComp)(struct compDict_s *, compType_t);
        comp_t *(*addComp)(struct compDict_s *, comp_t *);
    } compDict_t;


    /* CORE */

    struct core_s;

    typedef struct {
        char *name;
        sfVideoMode mode;
        sfRenderWindow *window;
        sfEvent event;
    } window_t;

    typedef struct {
        sfClock *clock;
        float elapsed;
    } timed_t;

    typedef struct gameObject_s {
        compDict_t *comps;

        int (*event)(struct core_s *);
        int (*update)(struct core_s *);
        int (*display)(struct core_s *);
        struct gameObject_s *next;
    } gameObject_t;

    typedef struct {
        char *name;
        gameObject_t *entities;
        char canBeDestroyed;

        int (*event)(struct core_s *);
        int (*update)(struct core_s *);
        int (*display)(struct core_s *);
    } scene_t;

    typedef struct core_s {
        window_t *window;
        timed_t *time;
        spriteDict_t *sprites;
        entitiesDict_t *entities;
        scene_t *curr;
        scene_t *tmp;

        int (*event)(struct core_s *);
        int (*update)(struct core_s *);
        int (*display)(struct core_s *);
        int (*run)(struct core_s *);
    } core_t;

#endif /* DATASTRUCTURE_H*/