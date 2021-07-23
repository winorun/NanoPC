#ifndef UINCURSES_H
#define UINCURSES_H

#include <ui.h>
#include <ncurses.h>

class UINcurses : public UIBase
{
public:
    UINcurses(bool step);
   ~UINcurses() override;
    virtual void drawWindows() override;
    virtual void exit() override;
    virtual unsigned char uiKeybord() override;
    void drawWindowsReg();
    void drawWindowsGDisplay();
    void drawWindowsMemory();
    void drawWindowsDisplay();
    void drawWindowsStatus();
private:
    WINDOW *win_reg;
    WINDOW *win_memory;
    WINDOW *win_graphic;
    WINDOW *win_displ;
    WINDOW *win_status;
};

#endif // UINCURSES_H
