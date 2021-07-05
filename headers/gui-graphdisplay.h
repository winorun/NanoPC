#ifndef GUI_GRAPHDISPLAY_H
#define GUI_GRAPHDISPLAY_H

namespace nsg {

    class GuiGraphDisplay : public GuiObject
    {
    public:
        GuiGraphDisplay (int , int , int , int );
    //    virtual ~GraphDisplay ();
        virtual void draw();
    private:
        /* data */
        const int numOfRow = 10;
        const int numOfColumn = 8;
        int w_cell;
        int h_cell;

        void drawCell(int column, int row);
        void drawRow(int row,unsigned char b);
    };

}

#endif /* GUI-GRAPHDISPLAY_H */
