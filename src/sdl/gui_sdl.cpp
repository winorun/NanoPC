#include <gui_sdl.h>
#include <SDL2/SDL.h> 
//#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <iostream>

#include "guibase.h"
#include "guigraphdisplay.h"
#include <stdio.h>

#include <core.h>
#include <font.h>


class GuiTextDisplay : public GuiBase {
public:
    GuiTextDisplay(int,int,GuiSdl *,TTF_Font *font);
    virtual ~GuiTextDisplay();
    virtual void draw();
private:
    char text[17];
    void setText(const char *text);
    GuiSdl *app;
    TTF_Font *font;
    SDL_Texture * textTexture;
};

void GuiTextDisplay::setText(const char *text){
    const SDL_Color defauldTextColor = {255,255,255,0};
    auto *textSurface = TTF_RenderUTF8_Blended_Wrapped(font,text, defauldTextColor,900);
    textTexture = SDL_CreateTextureFromSurface(app->getRenderer(), textSurface);
    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

GuiTextDisplay::GuiTextDisplay(int x, int y, GuiSdl *app, TTF_Font *font):GuiBase(x,y,0,0){
    this->app = app;
    this->font = font;
}

GuiTextDisplay::~GuiTextDisplay(){
    SDL_DestroyTexture(textTexture);
}

void GuiTextDisplay::draw(){
    for (int i = 0; i < 16; ++i) {
        if((memory[i]>32)&&(memory[i]<127)){
            text[i]=memory[i];
        }else
            text[i]=' ';
    }
    text[16] = 0;
    setText(text);
    SDL_RenderCopy(app->getRenderer(), textTexture, nullptr, &rect);
    SDL_SetRenderDrawColor(app->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(app->getRenderer(),rect.x,rect.y,rect.x+rect.w,rect.y);
    SDL_RenderDrawLine(app->getRenderer(),rect.x,rect.y+rect.h,rect.x+rect.w,rect.y+rect.h);
}



class GuiLabel : public GuiBase {
public:
    GuiLabel(int,int,GuiSdl *,TTF_Font *font, const char * );
    virtual ~GuiLabel();
    virtual void draw();
private:
    GuiSdl *app;
    TTF_Font *font;
    SDL_Texture * textTexture;
};

GuiLabel::GuiLabel(int x, int y, GuiSdl *app, TTF_Font *font, const char * text):GuiBase(x,y,0,0){
    const SDL_Color defauldTextColor = {255,255,255,0};
    auto *textSurface = TTF_RenderUTF8_Blended_Wrapped(font,text, defauldTextColor,900);
    textTexture = SDL_CreateTextureFromSurface(app->getRenderer(), textSurface);
    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);

    this->app = app;
    this->font = font;
}

GuiLabel::~GuiLabel(){
    SDL_DestroyTexture(textTexture);
}

void GuiLabel::draw(){
    SDL_RenderCopy(app->getRenderer(), textTexture, nullptr, &rect);
    SDL_SetRenderDrawColor(app->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(app->getRenderer(),rect.x,rect.y,rect.x+rect.w,rect.y);
    SDL_RenderDrawLine(app->getRenderer(),rect.x,rect.y+rect.h,rect.x+rect.w,rect.y+rect.h);
}

class GuiMemoryDisplay : public GuiBase {
public:
    GuiMemoryDisplay (int , int ,GuiSdl *,TTF_Font *font);
    virtual ~GuiMemoryDisplay();
    virtual void draw();
private:
    GuiSdl *app;
    TTF_Font *font;
    SDL_Texture * textTexture;
};

GuiMemoryDisplay::GuiMemoryDisplay(int x, int y, GuiSdl *app, TTF_Font *font):GuiBase(x,y,0,0){
    const SDL_Color defauldTextColor = {255,255,255,0};
    auto *textSurface = TTF_RenderUTF8_Blended_Wrapped(font,
                                                       //"╔════╤═════════════════════════╤═════════════════════════╗\n"
                                                       "║    │ 00 01 02 03 04 05 06 07 │ 08 09 0A 0B 0C 0D 0E 0F ║\n"
                                                       //"╠════╪═════════════════════════╪═════════════════════════╣\n"
                                                       "║ 00 │ 68 65 6C 6C 6F 20 77 6F │ 72 6C 64 21 FF 00 F0 0F ║\n"
                                                       "║ 10 │ 11 07 D0 F1 07 12 02 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ 20 │ E5 07 00 E5 07 01 15 02 │ 01 81 02 0F 21 02 E0 81 ║\n"
                                                       "║ 30 │ 01 F0 C1 01 04 21 01 E0 │ 11 03 0E 1A 03 01 11 03 ║\n"
                                                       "║ 40 │ 0F 1A 03 02 09 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ 50 │ 00 00 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ 60 │ 00 00 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ 70 │ 00 00 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ 80 │ 00 00 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ 90 │ 00 00 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ A0 │ 00 00 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ B0 │ 00 00 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ C0 │ 00 00 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ D0 │ 00 12 00 00 00 00 00 00 │ 00 00 00 00 00 00 00 00 ║\n"
                                                       "║ E0 │ 30 31 32 33 34 35 36 37 │ 38 39 41 42 43 44 45 46 ║\n"
                                                       "║ F0 │ 68 65 6C 6C 6F 20 77 6F │ 72 6C 64 00 00 00 00 00 ║\n"
                                                       //"╚════╧═════════════════════════╧═════════════════════════╝\n"
                                                             , defauldTextColor,900);
    textTexture = SDL_CreateTextureFromSurface(app->getRenderer(), textSurface);
    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);

    this->app = app;
    this->font = font;
}

GuiMemoryDisplay::~GuiMemoryDisplay(){
    SDL_DestroyTexture(textTexture);
}

void GuiMemoryDisplay::draw(){
    SDL_RenderCopy(app->getRenderer(), textTexture, nullptr, &rect);
}


SDL_Renderer * GuiSdl::getRenderer(){
    return renderer;
};

GuiSdl::GuiSdl(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    if(TTF_Init()==-1) {
        SDL_Log("TTF_Init: %s", TTF_GetError());
        exit(2);
    }
};

GuiSdl::~GuiSdl(){

    for(auto *obj:objs)
        delete obj;

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window)   SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

/** 
 * @brief Получить список всех режимов экранна
 * @return std::vector<SDL_DisplayMode> 
*/
std::vector<SDL_DisplayMode> GuiSdl::getAllDisplayMode(){

    std::vector<SDL_DisplayMode> mResolutions;
    int display_count = SDL_GetNumVideoDisplays();
    for (int display_index = 0; display_index <= display_count; display_index++){
        int modes_count = SDL_GetNumDisplayModes(display_index);
        for (int mode_index = 0; mode_index <= modes_count; mode_index++){
            SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, nullptr };
            if (SDL_GetDisplayMode(display_index, mode_index, &mode) == 0){
                mResolutions.push_back(mode);
            }
        }
    }
    return mResolutions;
}

void GuiSdl::printDisplayMode(std::vector<SDL_DisplayMode> &modes){
    int i = 0;
        for(auto mode:modes){
            SDL_Log("(%02i) %i bpp\t%i x %i @ %iHz",i++,
                   SDL_BITSPERPIXEL(mode.format),
                   mode.w, mode.h, mode.refresh_rate);
        }
}

void GuiSdl::drawSDLWindow(int flag){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for(auto *obj:objs)
        obj->draw();

    SDL_RenderPresent(renderer);

};

bool GuiSdl::delay(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN){
            return false;
        }
    }
    return true;
};

void GuiSdl::init(SDL_DisplayMode mode){
    this->mode = mode;
    this->window = SDL_CreateWindow(
            "NanoPC",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            mode.w,mode.h,
            SDL_WINDOW_FULLSCREEN);

    renderer = SDL_CreateRenderer(
            window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    {
        auto *obj = new GuiGraphDisplay(0,40,200,this);
        this->addW(obj);
    }
    SDL_RWops* DroidSans_ttf_buf = SDL_RWFromConstMem(DroidSans_ttf,DroidSans_ttf_len);

    //!@todo Сделать удаление font
    auto *font = TTF_OpenFontRW(DroidSans_ttf_buf, 1,30);
    if(!font){
        SDL_Log("Font load: %s", SDL_GetError());
    }
    {
        auto *obj = new GuiLabel(0,0,this,font,"DISPLAY");
        this->addW(obj);
    }
    {
        auto *obj = new GuiTextDisplay(0,600,this,font);
        this->addW(obj);
    }
    {
        auto *obj = new GuiMemoryDisplay(300,0,this,font);
        this->addW(obj);
    }
};

void GuiSdl::addW(GuiBase *w){
    this->objs.push_back(w);
}
