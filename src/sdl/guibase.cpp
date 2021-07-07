#include "guibase.h"

GuiBase::GuiBase(SDL_Rect * a){
    this->rect.x = a->x;
    this->rect.y = a->y;
    this->rect.w = a->w;
    this->rect.h = a->h;
}

GuiBase::GuiBase(int x, int y, int w, int h){
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
}

GuiBase::~GuiBase(){

}
