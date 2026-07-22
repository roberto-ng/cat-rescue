#ifdef _3DS
#include <3ds.h>
#include <spritetools.h>
#endif

#ifdef EMSCRIPTEN
#include<emscripten.h>
#endif

#include <stdio.h>
#include <time.h>

#include "Contexto.h"
#include "Bala.h"

using namespace jogo;

int main(int argv, char** args)
{
    srand(time(NULL));

    Contexto::Video.CarregarTextura("witch.png");
    Contexto::Video.CarregarTextura("ave.png");
    Contexto::Video.CarregarTextura("tiles.png");
    Contexto::Video.CarregarTextura("tubarao.png");
    Contexto::Video.CarregarTextura("gatos.png");
    Contexto::Video.CarregarTextura("balas.png");
    Contexto::Video.CarregarTextura("barra_de_vida.png");
    Contexto::Video.CarregarTextura("boxy_bold_font.png");

    atores::Agua::Inicializar();

#ifdef _3DS
    ST_RenderSetBackground(0xCC, 0xFF, 0x66);
    printf("Oi Ju \\o\n");
    while (aptMainLoop() && !Contexto::Video.sair)
    {
        Contexto::Atualizar();
    }

    //destructor precisa ser chamado manualmente no 3DS
    Contexto::Video.~Video();
#else
    SDL_SetRenderDrawColor(Contexto::Video.Renderer(), 204, 255, 102, 1);
#ifdef EMSCRIPTEN
    emscripten_set_main_loop(Contexto::Atualizar, 0, 1);
#else
    while (!Contexto::Video.sair)
    {
        Contexto::Atualizar();
    }
#endif
#endif

    return 0;
}

