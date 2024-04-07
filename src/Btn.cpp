#include "Btn.h"

Btn::Btn(float _x, float _y, float _width, float _height, char *_label)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    strcpy(label, _label);
}

void Btn::Render()
{
    CV::color(0, 1, 0);
    CV::rectFill(x, y, x + width, y + height);
    CV::color(0, 0, 0);
    CV::text(x + width / 3.2, y + height / 2.5, label); // escreve a label mais ou menos ao centro do botão
}

    // verifica se o cursor do mouse está dentro do botão ou não
bool Btn::wasClicked(int mouseX, int mouseY)
{
    if(mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
        return true;
    return false;
}
