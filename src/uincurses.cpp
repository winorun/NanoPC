#include "uincurses.h"
#include <ncurses.h>
#include <locale.h>
#include "core.h"

UINcurses::UINcurses(bool step)
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    keypad(stdscr,true);
    curs_set(0);
    timeout(step?-1:0);
    win_reg     = newwin(5,58,20,0);
    win_memory  = newwin(20,58,0,0);
    win_graphic = newwin(18,10,2,59);
    win_displ   = newwin(5,18,26,0);
    win_status  = newwin(5,13,26,20);

}

UINcurses::~UINcurses(){
    endwin();
}

unsigned char UINcurses::uiKeybord(){
    int ch = getch();
    switch (ch) {
        case KEY_F(2): return 0;
    }
    if(ch >= 0x20 && ch < 0x7f) return (unsigned char)ch;
    return 1;
}

void UINcurses::drawWindows(){
    refresh();
    drawWindowsReg();
    drawWindowsMemory();
    drawWindowsGDisplay();
    drawWindowsDisplay();
    drawWindowsStatus();
}

void UINcurses::exit(){
    refresh();
    drawWindowsReg();
    drawWindowsMemory();
    drawWindowsGDisplay();
    drawWindowsDisplay();
    drawWindowsStatus();
    timeout(-1);
    getch();
}

void UINcurses::drawWindowsReg(){
    wmove(win_reg,0,0);
    wprintw(win_reg,"╔════╤═════════════════════════╤═════════════════════════╗");
    wprintw(win_reg,"║REG | 00 01 02 03 04 05 SP SV | SD TV TD KV KC RC PS PC ║");
    wprintw(win_reg,"╠════╪═════════════════════════╪═════════════════════════╣");
    wprintw(win_reg,"║    |                         |                         ║");
    wprintw(win_reg,"╚════╧═════════════════════════╧═════════════════════════╝");
    wmove(win_reg,3,7);
    for(int i=0;i<=0xf;i++){
        if(i==8)wprintw(win_reg,"│ ");
        wprintw(win_reg,"%02X ",reg[i]);
    }
    wrefresh(win_reg);
}

void UINcurses::drawWindowsStatus(){
    char str[9];
    str[8] = 0;
    box(win_status,0,0);
    wmove(win_status,0,0);
    wprintw(win_status,"╔═ STATUS ══╗");
    wprintw(win_status,"║  EDSTCPNZ ║");
    wprintw(win_status,"╠═══════════╣");
    for (int y(0),i(0x80);i>0;i/= 0x02,y++){
        str[y] = ( reg[REG_PC_STATUS] & i )?(char ) '1':'0';
    }
    wprintw(win_status,"║  %08s ║",str);
    wprintw(win_status,"╚═══════════╝");
    wrefresh(win_status);
}

void UINcurses::drawWindowsMemory(){
    wmove(win_memory,0,0);
    wprintw(win_memory,"╔════╤═════════════════════════╤═════════════════════════╗");
    wprintw(win_memory,"║MEM | 00 01 02 03 04 05 06 07 | 08 09 0A 0B 0C 0D 0E 0F ║");
    wprintw(win_memory,"╠════╪═════════════════════════╪═════════════════════════╣");
    for (int i=0;i<0xFF;i+=0x10) {
        wprintw(win_memory,"║ %02X | ", i);
        for (int j=0;j<0x10;j++) {
            if(j == 8) wprintw(win_memory,"| ");
            if(reg[REG_PROGRAM_COUNTER] == (i+j)){
                wprintw(win_memory,"%02X<",memory[i+j]);
            }else{
                wprintw(win_memory,"%02X ",memory[i+j]);
            }
        }
        wprintw(win_memory,"║");
    }
    wprintw(win_memory,"╚════╧═════════════════════════╧═════════════════════════╝");
    wrefresh(win_memory);
}

void UINcurses::drawWindowsDisplay(){
    char str[17];
    str[16] = 0;
    box(win_displ,0,0);
    wmove(win_displ,0,0);
    wprintw(win_displ,"╔═ DISPLAY ══════╗");
    wprintw(win_displ,"║0123456789ABCDEF║");
    wprintw(win_displ,"╠════════════════╣");
    for (int i=0;i<0x10;i++){
        str[i] = (memory[i]>31 & memory[i]<128)?(char ) memory[i]:' ';
    }
    wprintw(win_displ,"║%s║",str);
    wprintw(win_displ,"╚════════════════╝");
    wrefresh(win_displ);
}

void UINcurses::drawWindowsGDisplay(){
    auto spaceChar="□";
    auto trueChar="■";
    wmove(win_graphic,0,0);
    wprintw(win_graphic,"╔ DISP ══╗");
    for (int i = 0; i < 0x10; ++i) {
        waddstr(win_graphic,"║");
        waddstr(win_graphic,(memory[i]&0b00000001)?trueChar:spaceChar);
        waddstr(win_graphic,(memory[i]&0b00000010)?trueChar:spaceChar);
        waddstr(win_graphic,(memory[i]&0b00000100)?trueChar:spaceChar);
        waddstr(win_graphic,(memory[i]&0b00001000)?trueChar:spaceChar);
        waddstr(win_graphic,(memory[i]&0b00010000)?trueChar:spaceChar);
        waddstr(win_graphic,(memory[i]&0b00100000)?trueChar:spaceChar);
        waddstr(win_graphic,(memory[i]&0b01000000)?trueChar:spaceChar);
        waddstr(win_graphic,(memory[i]&0b10000000)?trueChar:spaceChar);
        waddstr(win_graphic,"║");
    }
    waddstr(win_graphic,"╚════════╝");
    wrefresh(win_graphic);
}
