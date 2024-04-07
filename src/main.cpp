/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2024
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> // callback da wheel do mouse

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "Btn.h"
#include "Bmp.h"

// largura e altura inicial da tela
// alteram com o redimensionamento de tela
int screenWidth = 500, screenHeight = 500;

Btn *btn = NULL; //se a aplicacao tiver varios botoes, sugiro implementar um manager de botoes.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render()

Bmp *par;
unsigned char *data;

void DrawMouseScreenCoords()
{
    char str[100];
    sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
    CV::text(10,300, str);
    sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
    CV::text(10,320, str);
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
   DrawMouseScreenCoords();

   btn->Render();
}

// função chamada toda vez que uma tecla é pressionada
void keyboard(int key)
{
    printf("\nTecla: %d" , key);
    if(key == 27)
        exit(0);
}

// função para tratamento do mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mouseX = x; // guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

    if( state == 0 ) // clicou
    {
        if( btn->wasClicked(x, y) )
        {
            printf("\nClicou no botao\n");
        }
    }
}

void drawImage(unsigned char* data) {
    int bytesPerLine = (3 * (screenWidth + 1) / 4) * 4;
    // Use a pointer to iterate through imageData and draw each pixel onto the screen
    for (int y = 0; y < screenHeight; y++){
        for (int x = 0; x < screenWidth * 3; x += 3){
            // Calculate index into imageData for the current pixel
            int index = y * bytesPerLine + x;

            // Extract RGB values from imageData
            unsigned char r = data[index];
            unsigned char g = data[index + 1];
            unsigned char b = data[index + 2];

            // Draw the pixel at position (x, y) with color (r, g, b)
            CV::color(r / 255.0f, g / 255.0f, b / 255.0f); // Convert RGB values to range [0, 1]
            CV::point(x, y);
        }
    }
}

int main(void)
{
    par = new Bmp(".\\Trab1Rodrigo\\images\\par.bmp");
    par->convertBGRtoRGB();
    data = par->getImage();

    drawImage(data);

    btn = new Btn(200, 400, 140, 50, "botao");

    CV::init(screenWidth, screenHeight, "Trab1Rodrigo");
    CV::run();
}
