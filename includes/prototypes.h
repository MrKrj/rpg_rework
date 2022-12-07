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
    gameObject_t *getGameObjectByName(gameObject_t *, char *);
    void Dtr_GameObject(gameObject_t *);
    void Dtr_AllGameObjects(gameObject_t *);


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
    void Dtr_Graphics(graphics_t *);
    void Graphics_updateSprite(core_t *, graphics_t *, char *);

    text_t *toText(comp_t *);
    comp_t *Text(core_t *, FILE *);
    void Dtr_Text(text_t *);

    button_t *toButton(comp_t *);
    comp_t *Button(core_t *, FILE *);
    void Dtr_Button(button_t *);

    music_t *toMusic(comp_t *);
    comp_t *Music(core_t *, FILE *);
    void Dtr_Music(music_t *);

    hover_t *toHover(comp_t *comp);
    comp_t *Hover(core_t *, FILE *);
    void Dtr_Hover(hover_t *);



    /* SCENES */

    scene_t *Scene(core_t *, char *, scene_type_t, int);
    void Dtr_Scene(scene_t *);

    void Intro_passToMenu(core_t *);

    void Game_changeLeft(core_t *, int);
    void Game_changeRight(core_t *, int);
    void Game_hover_ChangeRight(core_t *, int);
    void Game_hover_ChangeLeft(core_t *, int);


#endif /* PROTOTYPES_H */