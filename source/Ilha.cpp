#include <cstdlib>
#include <cstdio>

#include "Ilha.h"
#include "Tubarao.h"
#include "Gato.h"
#include "Contexto.h"
#include "spritesheets/tiles_spritesheet.h"

using namespace sprite;
using namespace jogo;

namespace atores 
{
    u8 Ilha::_qtd_horizontal = 6;
    u8 Ilha::_qtd_vertical   = 3;
    vector< vector<u8> > Ilha::_mapa {
        { GRAMA_1, GRAMA_2, GRAMA_2, GRAMA_2, GRAMA_2, GRAMA_3 },
        { CHAO_1,  CHAO_2,  CHAO_2,  CHAO_2,  CHAO_2,  CHAO_3  },
        { CHAO_1,  CHAO_2,  CHAO_2,  CHAO_2,  CHAO_2,  CHAO_3  }
    };

    Ilha::Ilha()
    {
        Textura  = sprite::TEX_TILES;

        Largura = 16 * _qtd_horizontal;
        Altura  = 16 * _qtd_vertical;

        Pos.X = 0 - Largura;
        Pos.Y = Contexto::Video.Height - Altura;

        //65% de chance da ilha ser habitada
        if ((rand() % 100) < 65)
        {
            //80% de chance de ter um gato na ilha
            if ((rand() % 100) < 80)
            {
                Contexto::Gatos.push_back(Gato(Pos + Vetor2(Largura / 2, 0)));
            }

            //50% de chance de ter apenas 1 tubarao
            //e 50% de ter 2
            if ((rand() % 100) < 50)
            {
                _tubaroes.push_back(
                    Tubarao(
                        TUBARAO_TIPO_PEQUENO,
                        Pos + Vetor2(Largura / 2, 0)
                    )
                );
            }
            else
            {
                _tubaroes.push_back(
                    Tubarao(
                        TUBARAO_TIPO_PEQUENO,
                        Pos + Vetor2(Largura / 4, 0)
                    )
                );

                _tubaroes.push_back(
                    Tubarao(
                        TUBARAO_TIPO_PEQUENO,
                        Pos + Vetor2(Largura / 4 * 3, 0)
                    )
                );
            }
        }
    }

    void Ilha::Atualizar()
    {
        auto &animacoes = tiles.animacoes;

        Pos.X += 1;

        for (u8 i = 0; i < _mapa.size(); i++)
        {
            auto &linha = _mapa.at(i);

            for (u8 j = 0; j < linha.size(); j++)
            {
                auto tile_tipo = linha.at(j);

                auto x = animacoes.at(tile_tipo).frames.at(0).x;
                auto y = animacoes.at(tile_tipo).frames.at(0).y;
                auto w = animacoes.at(tile_tipo).frames.at(0).w;
                auto h = animacoes.at(tile_tipo).frames.at(0).h;

                Contexto::Video.RenderizarTextura(Contexto::Video.Texturas[Textura],
                    Pos.X + 16 * j, Pos.Y + 16 * i, x, y, w, h);
            }
        }
        
        for (auto &tubarao : _tubaroes)
        {
            tubarao.Atualizar(Pos.X, Pos.X + Largura);
        }
    }
}
