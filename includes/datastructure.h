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


    /* COMPONENTS */

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
        unsigned int id;
        char *name;
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
        scene_t *curr;
        scene_t *tmp;

        int (*event)(struct core_s *);
        int (*update)(struct core_s *);
        int (*display)(struct core_s *);
        int (*run)(struct core_s *);
    } core_t;

#endif /* DATASTRUCTURE_H*/