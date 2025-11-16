#include "render.h"
#include "logic.h"
#include "raylib.h"

void DrawGameGrid()
{
  // DrawLine(startX, startY, endX, endY, color);

  // Linhas verticais
  DrawLine(CELL_SIZE, 0, CELL_SIZE, SCREEN_HEIGHT, DARKGRAY);
  DrawLine(2 * CELL_SIZE, 0, 2 * CELL_SIZE, SCREEN_HEIGHT, DARKGRAY);

  // Linhas horizontais
  DrawLine(0, CELL_SIZE, SCREEN_WIDTH, CELL_SIZE, DARKGRAY);
  DrawLine(0, 2 * CELL_SIZE, SCREEN_WIDTH, 2 * CELL_SIZE, DARKGRAY);
}

/* ----- Desenha o jogador X ----- */
void DrawX(int x, int y, Texture2D tex){

  // !! AJUSTE PARA O SHELDON CABER NA CÉLULA !!
  double scale_ajust = 0.58f;

  // Calcula a escala para a imagem entrar no quadrante.
  double scale = (double)CELL_SIZE / (double)tex.width * scale_ajust;

  // Calcula a posição dos pixels
  int pixel_x = x * CELL_SIZE;
  int pixel_y = y * CELL_SIZE;

  // !! CENTRALIZAÇÃO DO SHELDON !!
  double image_swidth  = tex.width  * scale;
  double image_sheight = tex.height * scale;

  double offset_x = (CELL_SIZE - image_swidth)  / 2.0f;
  double offset_y = (CELL_SIZE - image_sheight) / 2.0f;

  // Desenha a imagem (CENTRALIZADA PARA O SHELDON)
  // DrawTextureEx(textura, posição, rotação, escala, cor_de_fundo)
  DrawTextureEx(tex, (Vector2){pixel_x + offset_x,pixel_y + offset_y}, 0.0f, scale, WHITE);
}

/* ----- Desenha o jogador O -----*/
void DrawO(int x, int y, Texture2D tex){
  
  double scale = (double)CELL_SIZE / (double)tex.width;

  int pixel_x = x * CELL_SIZE;
  int pixel_y = y * CELL_SIZE;

  DrawTextureEx(tex, (Vector2){pixel_x,pixel_y}, 0.0f, scale, WHITE);
}

/* ----- Desenha o estado atual do tabuleiro ----- */
void DrawBoard(Board b, Texture2D tX, Texture2D tO){

  // Loop para percorrer todos as células.
  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 3 ; x++)
    {
      char cell = GetBoardCell(b,x,y);

      // Desenha o conteúdo da célula.
      if (cell == 'X')
      {
        DrawX(x,y,tX);
      }
      else if (cell == 'O')
      {
        DrawO(x,y,tO);
      }
    }
  }
}

