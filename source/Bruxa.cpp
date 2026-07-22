#include <vector>

#include "Bruxa.h"
#include "Contexto.h"
#include "animacao.h"
#include "spritesheets/witch_spritesheet.h"

using jogo::Contexto;
using std::string;

namespace atores
{
    Bruxa::Bruxa()
    {
        Altura  = 32;
        Largura = 32;
        AnimAtual = BRUXA_VOAR;
        FrameAtual = 0;
        Textura = sprite::TEX_BRUXA;
        Pos = jogo::Vetor2(300, 120);
        Invencivel = false;
        _FramesInvencibilidade = 0;
        HP = 3;
    }

    void Bruxa::Reiniciar()
    {
        Pos = jogo::Vetor2(300, 120);
        AnimAtual = BRUXA_VOAR;
        FrameAtual = 0;
        Invencivel = false;
        _FramesInvencibilidade = 0;
        HP = 3;
    }

    void Bruxa::Atualizar()
    {
        if ((!Contexto::Cima && !Contexto::Baixo) || (Contexto::Cima && Contexto::Baixo))
        {
            if (AnimAtual != BRUXA_VOAR)
            {
                AnimAtual = BRUXA_VOAR;
                FrameAtual = 0;
            }
        }

        Vetor2 direcao(0, 0);

        if (Contexto::Cima && !Contexto::Baixo)
        {
            AnimAtual = BRUXA_VOAR_CIMA;
            FrameAtual = 0;
            direcao.Y = -1;
        }

        if (Contexto::Baixo && !Contexto::Cima)
        {
            AnimAtual = BRUXA_VOAR_BAIXO;
            FrameAtual = 0;
            direcao.Y = 1;
        }

        if (Contexto::Esquerda && !Contexto::Direita)
        {
            direcao.X = -1;
        }

        if (Contexto::Direita && !Contexto::Esquerda)
        {
            direcao.X = 1;
        }

        // Normalize digital movement so diagonal travel has the same speed
        // as horizontal or vertical travel.
        if (direcao != Vetor2(0, 0))
        {
            Pos += direcao.Unidade() * 2.0;

            if (Pos.X < 0)
                Pos.X = 0;
            if (Pos.X + Largura > Contexto::Video.Width)
                Pos.X = Contexto::Video.Width - Largura;
            if (Pos.Y < 0)
                Pos.Y = 0;
            if (Pos.Y + Altura > Contexto::Video.Height - 16)
                Pos.Y = Contexto::Video.Height - 16 - Altura;
        }

        if ((Contexto::Video.CliqueAnterior.X != -30) &&
            (Contexto::Video.CliqueAtual.X != -30))
        {
            Vetor2 cliqueAnterior = Contexto::Video.CliqueAnteriorEscalado();
            Vetor2 cliqueAtual = Contexto::Video.CliqueAtualEscalado();
            Vetor2 diferenca = cliqueAtual - cliqueAnterior;

            Pos += diferenca;

            const s32 aguaTamanho = 16; //altura e largura da água

            if (Pos.Y < 0)
                Pos.Y = 0;

            if (Pos.Y + Altura > Contexto::Video.Height - aguaTamanho)
                Pos.Y = Contexto::Video.Height - aguaTamanho - Altura;

            if (Pos.X < 0)
                Pos.X = 0;

            if (Pos.X + Largura > Contexto::Video.Width)
                Pos.X = Contexto::Video.Width - Largura;
        }

        Animar();

        if (Invencivel)
        {
            if (_FramesInvencibilidade > 0)
                _FramesInvencibilidade -= 1;
            else
                Invencivel = false;
        }
    }

    void Bruxa::LevarDano()
    {
        if (!Invencivel)
        {
            Invencivel = true;
            _FramesInvencibilidade = _FramesInvencibilidadeMax;

            u8 qtd = Contexto::ContarGatosAjudando();
            if (qtd > 0)
            {
                u8 qtd = Contexto::ContarGatosAjudando();
                //procura o gato ajudando que esta na ultima pos
                for (auto &gato : Contexto::Gatos)
                {
                    if (Contexto::PosicaoGatosAjudando(&gato) == qtd - 1)
                    {
                        gato.LevarDano();
                        break;
                    }
                }
            }
            else if (HP > 0)
            {
                --HP;
            }
        }
    }

    void Bruxa::Animar()
    {
        auto &animacoes = sprite::bruxa.animacoes;

        if (Contexto::Video.frames % animacoes[AnimAtual].framerate == 0)
        {
            if (animacoes[AnimAtual].frames.size() > 1)
            {
                if (animacoes[AnimAtual].loop || FrameAtual < animacoes[AnimAtual].frames.size())
                    FrameAtual++;
            }

            if (FrameAtual >= animacoes[AnimAtual].frames.size())
            {
                if (animacoes[AnimAtual].loop)
                    FrameAtual = 0;
            }
        }

        auto x = animacoes[AnimAtual].frames[FrameAtual].x;
        auto y = animacoes[AnimAtual].frames[FrameAtual].y;
        auto w = animacoes[AnimAtual].frames[FrameAtual].w;
        auto h = animacoes[AnimAtual].frames[FrameAtual].h;

        //caso a bruxa esteja nos frames de invencibilidade
        //só renderizar a cada 3 frames
        if (!Invencivel || (Contexto::Video.frames % 3 == 0))
        {
            Contexto::Video.RenderizarTextura(
                Contexto::Video.Texturas[Textura],
                Pos.X, Pos.Y, x, y, w, h
            );
        }
    }
}
