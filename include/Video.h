#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <vector>

#ifdef _3DS
#include <spritetools.h>
#include <sf2d.h>
typedef st_spritesheet textura;
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef SDL_Texture textura;
#endif

#include "tipos.h"
#include "Vetor2.h"

using jogo::Vetor2;

namespace graficos
{
    class Video
    {
        private:
#ifndef _3DS
           SDL_Window   *_janela; 
           SDL_Renderer *_ren;
           SDL_Event _evento;
#endif
        public: 
            Vetor2 CliqueAtual;
            Vetor2 CliqueAnterior;
            u16 frames = 0;
            const static u16 Width  = 400; 
            const static u16 Height = 240;
            bool sair = false;
            std::vector<textura*> Texturas;

#ifndef _3DS
            SDL_Window   *Janela() { return _janela; }
            SDL_Renderer *Renderer() { return _ren; }
#endif

            /** Faz as preparações necessarias para iniciar o jogo */
            Video();

            /** Limpa as texturas e prepara para encerrar o programa */
            ~Video();

            /** Esala o clique atual de acordo com o tamanho da tela
             * @return O clique escalado
             */
            Vetor2 CliqueAtualEscalado();

            /** Esala o clique do frame anterior de acordo com o tamanho da tela
             * @return O clique escalado
             */
            Vetor2 CliqueAnteriorEscalado();

            /** Carrega uma textura, as texturas devem ser carregadas
             * de acordo com a ordem do enum TEXTURA no arquivo "animacao.h"
             * @brief Carrega uma textura.
             * @param arquivo Nome do arquivo a ser carregado.
             */
            void CarregarTextura(const std::string arquivo);

            /** Inicia um frame */
            void IniciarFrame();

            /** Encerra um frame */
            void EncerrarFrame();

            /** Checa o input do usuario e atualiza a classe Contexto */
            void ChecarEntrada();

            /** Renderiza uma textura
             * @param tex Textura a ser renderizada
             * @param x Ponto X onde a textura vai ser desenhada
             * @param y Ponto Y onde a textura vai ser desenhada
             * @param corte_x Ponto X da localização do sprite na textura
             * @param corte_y Ponto Y da localização do sprite na textura
             * @param corte_w Largura do sprite
             * @param corte_h Altura do sprite
             * @param angulo Angulo em que o sprite deve ser desenhado
             * @param escala Altera o tamanho do sprite
             */
            void RenderizarTextura(textura *tex, s16 x, s16 y,
                u16 corte_x, u16 corte_y, u16 corte_w, u16 corte_h,
                f32 angulo = 0.0, f32 escala = 1.0);

            /** Limpa a tela */
            void LimparTela();
    };
}

#endif
