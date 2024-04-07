#ifndef BTN_H
#define BTN_H

#include "gl_canvas2d.h"

class Btn
{
    public:
        Btn(float _x, float _y, float _width, float _height, char *_label);
        void Render(void);
        bool wasClicked(int mouseX, int mouseY);

    private:
        float height, width, x, y;
        char label[100];
};

#endif // BTN_H
