#include <cstdint>

#include "Agua.h"
#include "Vetor2.h"
#include "Contexto.h"
#include "spritesheets/tiles_spritesheet.h"

using jogo::Contexto;

namespace atores
{
    Agua::Agua(s16 x, s16 y)
    {
        Pos = Vetor2(x, y);
        Textura = sprite::TEX_TILES;
    }

    void Agua::Inicializar()
    {
        u8  qtd = (Contexto::Video.Width / 16) + 1;
        s16 y   = (Contexto::Video.Height / 16 - 1 ) * 16;

        for (u8 i = 0; i < qtd; i++)
        {
            Contexto::Aguas.push_back(Agua((i * 16), y));
        }
    }

    void Agua::Atualizar()
    {
        auto &sprite = sprite::tiles.animacoes[0].frames[0];

        if (Pos.X >= Contexto::Video.Width)
        {
            Pos.X = -15;
        }
        else
        {
            Pos.X += 1;
        }

        Contexto::Video.RenderizarTextura(Contexto::Video.Texturas[Textura],
            Pos.X, Pos.Y, sprite.x, sprite.y, sprite.w, sprite.h);
    }
}
