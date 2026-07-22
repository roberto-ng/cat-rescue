#include <cstdlib>

#include "Tubarao.h"
#include "Contexto.h"
#include "spritesheets/tubarao_spritesheet.h"

namespace atores
{
    Tubarao::Tubarao(u8 tipo, Vetor2 pos)
    {
        _tipo = tipo;
        Textura = sprite::TEX_TUBARAO;
        FrameAtual = 0;

        switch (_tipo)
        {
            case TUBARAO_TIPO_PEQUENO:
                Largura = 14;
                Altura  = 12;
                AnimAtual = TUBARAO_PEQUENO_INVERSO;
                break;
            case TUBARAO_TIPO_GRANDE:
                Largura = 14;
                Altura  = 24;
                AnimAtual = TUBARAO_PEQUENO;
                break;
        }

        Pos = pos - Vetor2(0, Altura);
        _sentido = Vetor2(-1, 0);
    }

    void Tubarao::Atualizar(s16 limite_comeco, s16 limite_fim)
    {
        Vetor2 Vel(0, 0);
        Vel.X += 1; //mover junto com a ilha
        
        if (ColidindoCom(Contexto::Bruxa) && AnimAtual != TUBARAO_DERROTADO)
        {
            AnimAtual  = TUBARAO_DERROTADO;
            FrameAtual = 0;
            Vel.Y -= 3;
        }

        if (_tipo == TUBARAO_TIPO_PEQUENO && AnimAtual != TUBARAO_DERROTADO)
        {
            if (Pos.X <= limite_comeco)
            {
                _sentido.X = 1;
                FrameAtual = 0;
                AnimAtual = TUBARAO_PEQUENO_INVERSO;
            }
            else if (Pos.X + Largura >= limite_fim)
            {
                _sentido.X = -1;
                FrameAtual = 0;
                AnimAtual = TUBARAO_PEQUENO;
            }
        }

        Vel.X += _sentido.X * 2;
        
        if (AnimAtual == TUBARAO_DERROTADO)
        {
            Vel.Y += 1;
        }

        auto &animacoes = sprite::tubarao.animacoes;

        auto x = animacoes.at(AnimAtual).frames.at(FrameAtual).x;
        auto y = animacoes.at(AnimAtual).frames.at(FrameAtual).y;
        auto w = animacoes.at(AnimAtual).frames.at(FrameAtual).w;
        auto h = animacoes.at(AnimAtual).frames.at(FrameAtual).h;

        Pos += Vel;
        Contexto::Video.RenderizarTextura(Contexto::Video.Texturas[Textura],
            Pos.X, Pos.Y, x, y, w, h);

        if (FrameAtual + 1 < animacoes.at(AnimAtual).frames.size())
        {
            FrameAtual++;
        }
        else
        {
            FrameAtual = 0;
        }
    }
}
