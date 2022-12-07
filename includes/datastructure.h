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
    #define TRUE 1
    #define FALSE 0

    struct core_s;

    /* UTILS */

    typedef struct ptrFct_s {
        char *name;
        void (*ptr)(struct core_s *, int);
    } ptrFct_t;

    /* FONT DICT */

    typedef struct fontEntry_s {
        unsigned int id;
        char *name;
        sfFont *font;

        struct fontEntry_s *next;
    } fontEntry_t;

    typedef struct fontDict_s {
        fontEntry_t *entries;

        sfFont *(*getFontByName)(struct fontDict_s *, char *);
        sfFont *(*addFont)(struct fontDict_s *, char *, char *);
    } fontDict_t;

    /* SPRITE DICT */

    typedef struct spriteEntry_s {
        unsigned int id;
        char *name;
        sfTexture *texture;
        sfSprite *sprite;

        struct spriteEntry_s *next;
    } spriteEntry_t;

    typedef struct spriteDict_s {
        spriteEntry_t *entries;

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
        GRAPHICS,
        TEXT,
        BUTTON,
        MUSIC,
        HOVER
    } compType_t;

    typedef struct {
        sfSprite *sprite;
        char animated;
        char parallax;
        int velocity;
        float elapsed;
        float passed;
        float opacity;
        sfVector2f pos;
        sfVector2f size;
        sfVector2f grid;
        sfVector2f scale;
    } graphics_t;

    typedef struct {
        void (*onHover)(struct core_s *, int);
    } hover_t;

    typedef struct {
        sfFont *font;
        sfText *text;
    } text_t;

    typedef struct {
        void (*onClicked)(struct core_s *, int);
    } button_t;

    typedef struct {
        sfMusic *music;
        int cooldown;
    } music_t;

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

    typedef struct {
        char *name;
        sfVideoMode mode;
        sfRenderWindow *window;
        sfVector2i currSize;
        sfEvent event;
    } window_t;

    typedef struct {
        sfClock *clock;
        float elapsed;
    } timed_t;

    typedef struct gameObject_s {
        char *name;
        compDict_t *comps;

        int (*event)(struct core_s *);
        int (*update)(struct core_s *);
        int (*display)(struct core_s *);
        struct gameObject_s *next;
    } gameObject_t;

    typedef enum scene_type_e {
        INTRO,
        MENU,
        GAME
    } scene_type_t;

    typedef struct {
        scene_type_t type;
        gameObject_t *entities;
        char canBeDestroyed;
        float elapsed;

        int (*event)(struct core_s *);
        int (*update)(struct core_s *);
        int (*display)(struct core_s *);
    } scene_t;

    typedef struct core_s {
        window_t *window;
        timed_t *time;
        spriteDict_t *sprites;
        fontDict_t *fonts;
        scene_t *curr;
        scene_t *tmp;

        int (*event)(struct core_s *);
        int (*update)(struct core_s *);
        int (*display)(struct core_s *);
        int (*run)(struct core_s *);
    } core_t;

#endif /* DATASTRUCTURE_H */