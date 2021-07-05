#ifndef GUIBASE_H
#define GUIBASE_H

#include <SDL2/SDL.h>

class GuiBase
{
    public:
        GuiBase(SDL_Rect * );
        GuiBase(int x, int y, int w, int h);
        virtual void draw()=0;
        virtual ~GuiBase();
    protected:
        SDL_Rect rect;

};

#endif // GUIBASE_H
