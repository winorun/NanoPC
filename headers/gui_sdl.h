#ifndef GUI_SDL_H
#define GUI_SDL_H

#include <SDL2/SDL.h>
#include <vector>

class GuiBase;
class GuiSdl
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_DisplayMode mode; // curentMode;
    std::vector<GuiBase *> objs;
    bool run=true;    
public:
    GuiSdl();
    virtual ~GuiSdl();
    void drawSDLWindow(int flag);
    bool delay();
    void init(SDL_DisplayMode mode);
    void addW(GuiBase *);
    SDL_Renderer *getRenderer();
    std::vector<SDL_DisplayMode> getAllDisplayMode();
    void printDisplayMode(std::vector<SDL_DisplayMode> &modes);
};

#endif /* GUI-SDL_H */
