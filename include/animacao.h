#ifndef ANIMACAO_H
#define ANIMACAO_H

#include <string>
#include <vector>

#include "tipos.h"

namespace sprite
{
    enum TEXTURA {
        TEX_BRUXA,
        TEX_AVE, 
        TEX_TILES, 
        TEX_TUBARAO,
        TEX_GATO,
        TEX_BALAS,
        TEX_BARRA_VIDA,
        TEX_FONTE
    };

    struct frame
    {
        u16 x;
        u16 y;
        u16 w;
        u16 h;
    };

    struct animacao
    {
        bool loop;
        u8 framerate;
        std::string nome;
        std::vector<frame> frames;
    };

    struct spritesheet
    {
        std::string nome;
        std::vector<animacao> animacoes;
    };
}
#endif
