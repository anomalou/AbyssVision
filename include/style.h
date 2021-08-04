#ifndef STYLE_H
#define STYLE_H

#include <SDL.h>
#include <agl.h>
#include <colors.h>

namespace AbyssCore{
    typedef struct{
        aColor background;
        aColor border;
        aColor shadow;
        int shadow_size;
        aColor control;
        aColor enabled;
        aColor disabled;
        aColor focus;
        aColor nofocus;
        aColor selected;
        aColor hover;
    }Style;

    typedef enum{
        Idle,
        Pressed,
        Hovered
    }State;
}


#endif