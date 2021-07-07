#ifndef UI
#define UI

class UIBase {
public:
    virtual void drawWindows() = 0;
    virtual unsigned char uiKeybord() = 0;
    virtual ~UIBase(){};
};

#endif
