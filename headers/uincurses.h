#ifndef UINCURSES_H
#define UINCURSES_H

#include <ui.h>
#include <ncurses.h>

class UINcurses : public UIBase
{
public:
    UINcurses();
   ~UINcurses() override;
    virtual void drawWindows() override;
    virtual unsigned char uiKeybord() override;
    void drawWindowsReg();
    void drawWindowsGDisplay();
    void drawWindowsMemory();
    void drawWindowsDisplay();
private:
    WINDOW *win_reg;
    WINDOW *win_memory;
    WINDOW *win_graphic;
    WINDOW *win_displ;
};

#endif // UINCURSES_H
