/*
**
** My_RPG Rework
** Kevin Spegt
**
*/

#ifndef PROTOTYPES_H
    #define PROTOTYPES_H

    #include <stdio.h>
    #include "datastructure.h"

    /* CORE */

    core_t *Core(void);
    void Dtr_Core(core_t *);

    window_t *Window(char *, sfVector2i, int);
    void Dtr_Window(window_t *);

    timed_t *Timed(void);
    void Dtr_Timed(timed_t *);

    gameObject_t *GameObject(core_t *, char *, char *);
    gameObject_t *GameObjectsFromConfig(core_t *, char *);
    void Dtr_GameObject(gameObject_t *);


    /* UTILS */

    tuple_t *Tuple(char *);
    tuple_t *TupleFromFile(FILE *);
    void Dtr_Tuple(tuple_t *);


    /* DICTS */

    spriteDict_t *SpriteDict(void);
    void Dtr_SpriteDict(spriteDict_t *);

    compDict_t *CompDict(void);
    void Dtr_CompDict(compDict_t *);

    fontDict_t *FontDict(void);
    void Dtr_FontDict(fontDict_t *);


    /* COMPS */

    graphics_t *toGraphics(comp_t *);
    comp_t *Graphics(core_t *, FILE *);

    text_t *toText(comp_t *);
    comp_t *Text(core_t *, FILE *);

    button_t *toButton(comp_t *);
    comp_t *Button(core_t *, FILE *);



    /* SCENES */

    scene_t *Intro(core_t *);
    void Dtr_Intro(scene_t *);
    void Intro_passToMenu(core_t *);


    scene_t *Menu(core_t *);
    void Dtr_Menu(scene_t *);

#endif /* PROTOTYPES_H*/