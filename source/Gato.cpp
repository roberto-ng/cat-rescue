#include "Gato.h"
#include "Contexto.h"
#include "spritesheets/gato_spritesheet.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>

namespace atores
{
    Gato::Gato(Vetor2 pos)
    {
        Textura = sprite::TEX_GATO;
        Largura = 23;
        Altura  = 21;
        Pos = pos - Vetor2(0, Altura);
        FrameAtual = 0;
        AnimAtual = GATO_ANIM_NORMAL;
        _estado = GATO_ESPERANDO;
        _alvo = Vetor2(-30, -30);

        //50% de chance do gato ser cinza
        //e 50% de ser rosa
        if ((rand() % 100) < 50)
        {
            _tipo = sprite::GATO_TIPO_CINZA;
        }
        else
        {
            _tipo = sprite::GATO_TIPO_ROSA;
        }
    }

    void Gato::Atualizar()
    {
        if (this->ColidindoCom(Contexto::Bruxa) && _estado == GATO_ESPERANDO)
        {
            if (Contexto::ContarGatosAjudando() < 3)
            {
                _estado = GATO_AJUDANDO;
                AnimAtual = GATO_ANIM_VOAR_INVERSO;
            }
            else
            {
                _estado = GATO_SUMINDO;
                AnimAtual = GATO_ANIM_PUFF;
                FrameAtual = 0;
            }
        }

        auto &Video = Contexto::Video;

        switch (_estado)
        {
            case GATO_ESPERANDO: {
                //mover junto com a ilha
                ++Pos.X;
            } break;

            case GATO_AJUDANDO: {
                //posição entre os gatos que estão ajudando
                auto pos = Contexto::PosicaoGatosAjudando(this);

                //calcula o ponto que o gato deve seguir
                if (pos == 0)
                {
                    _alvo = Contexto::Bruxa.Pos - Vetor2(41, -4);
                }
                else if (pos == 1)
                {
                    _alvo = Contexto::Bruxa.Pos - Vetor2(-30, -38);
                }
                else
                {
                    _alvo = Contexto::Bruxa.Pos - Vetor2(-30, 33);
                }

                Vetor2 diferenca_clique =
                        Video.CliqueAtualEscalado() - Video.CliqueAnteriorEscalado();

                if (Video.CliqueAnterior.X != -30 &&
                    Video.CliqueAtual.X    != -30)
                {
                    Pos += diferenca_clique;

                    if (Pos.Y < 0)
                        Pos.Y = 0;

                    if (Pos.Y + Altura > Video.Height - 16)
                        Pos.Y = Video.Height - 16 - 21;

                    if (Pos.X < 0)
                        Pos.X = 0;

                    if (Pos.X + Largura > Video.Width)
                        Pos.X = Video.Width - Largura;
                }

                //diferença entre a posição do gato e o ponto alvo
                Vetor2 diferenca =  _alvo - Pos;
                f32 velocidade = 2.0;

                //move o gato de acordo com a direção necessaria
                if (diferenca.X > 1)
                {
                    if (Pos.X + Largura < Video.Width)
                        Pos.X += velocidade;
                }
                else if (diferenca.X < -1)
                {
                    if (Pos.X > 0)
                        Pos.X -= velocidade;
                }

                if (diferenca.Y > 1)
                {
                    //impede que o gato passe da água
                    if (Pos.Y + Altura < Video.Height - 16)
                        Pos.Y += velocidade;
                }
                else if (diferenca.Y < -1)
                {
                    if (Pos.Y > 0)
                        Pos.Y -= velocidade;
                }

                //atacar a cada 30 frames
                if (Contexto::Video.frames % 30 == 0)
                {
                    Atacar(pos);
                }

            } break;
            case GATO_SUMINDO: {
                //mover junto com a ilha
                ++Pos.X;
            } break;
        }

        Animar();
    }

    void Gato::Atacar(u8 pos)
    {
        if (pos != 0)
        {
            Contexto::Balas.push_back(Bala(Pos.X - 9, Centro().Y, BALA_FOGUETE_AZUL));
        }
        else
        {
            Contexto::Balas.push_back(Bala(Pos.X - 9, Centro().Y, BALA_FOGUETE_AMARELO));
        }
    }

    void Gato::LevarDano()
    {
        _estado = GATO_SUMINDO;
        AnimAtual = GATO_ANIM_PUFF;
        FrameAtual = 0;
    }

    void Gato::Animar()
    {
        auto &animacao = sprite::gatos.at(_tipo).animacoes.at(AnimAtual);

        if ((Contexto::Video.frames % animacao.framerate) == 0)
        {
            if (FrameAtual + 1 < animacao.frames.size())
                FrameAtual++;
            else if (animacao.loop)
                FrameAtual = 0;
        }

        auto x = animacao.frames.at(FrameAtual).x;
        auto y = animacao.frames.at(FrameAtual).y;
        auto w = animacao.frames.at(FrameAtual).w;
        auto h = animacao.frames.at(FrameAtual).h;

        Contexto::Video.RenderizarTextura(Contexto::Video.Texturas.at(Textura),
            Pos.X, Pos.Y, x, y, w, h);
    }
}
