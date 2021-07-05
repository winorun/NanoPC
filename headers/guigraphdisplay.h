#ifndef GUIGRAPHDISPLAY_H
#define GUIGRAPHDISPLAY_H

#include <SDL2/SDL.h>
#include "guibase.h"
#include <gui_sdl.h>

class GuiGraphDisplay : public GuiBase {
public:
    GuiGraphDisplay (int, int, int, GuiSdl *);
//    virtual ~GraphDisplay ();
    virtual void draw();
private:
    /* data */
    static const int numOfRow = 16;
    static const int numOfColumn = 8;
    int w_cell;
    int h_cell;

    GuiSdl *app;

    void drawCell(int column, int row);
    void drawRow(int row,unsigned char b);
};

#endif // GUIGRAPHDISPLAY_H
