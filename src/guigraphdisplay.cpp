#include "guigraphdisplay.h"
#include "core.h"

GuiGraphDisplay::GuiGraphDisplay(int x, int y, int w, GuiSdl *app):GuiBase(x,y,w,(w*numOfRow)/numOfColumn){
    this->app=app;
    w_cell=this->rect.w/numOfColumn;
    h_cell=this->rect.h/numOfRow;
}

void GuiGraphDisplay::drawCell(int column, int row){
    SDL_Rect rect{(column*w_cell)+1+this->rect.x,(row*h_cell)+1+this->rect.y,w_cell-2,h_cell-2};
    SDL_SetRenderDrawColor(app->getRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(app->getRenderer(),&rect);
}

void GuiGraphDisplay::drawRow(int row,unsigned char b){
    for(int i=0;i!=8;i++){
        if(b & 1)drawCell(i,row);
        b = b >> 1;
    }

}

void GuiGraphDisplay::draw(){
    //printf("x %i, y %i \n",rect.w,rect.h);
    SDL_SetRenderDrawColor(app->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(app->getRenderer(), &rect);
    for(int i=rect.x+w_cell;i<rect.w;i+=w_cell){
        SDL_RenderDrawLine(app->getRenderer(), i, rect.y, i, rect.y+rect.h);
    }
    for(int i=rect.y+h_cell;i<rect.h;i+=h_cell){
        SDL_RenderDrawLine(app->getRenderer(), rect.x, i, rect.x+rect.w, i);
    }
    for(int i = numOfRow-1;i>=0;i--)
        this->drawRow(i,memory[i]);
}

