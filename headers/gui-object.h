#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <SDL2/SDL.h> 

namespace nsg {
    class GuiObject
    {
    public:
        GuiObject(SDL_Rect * );
        GuiObject(int x, int y, int w, int h);
        virtual void draw()=0;
        // virtual ~GuiObject();
    protected:
        SDL_Rect rect;
    };
}

#endif /* GUI-OBJECT_H */
