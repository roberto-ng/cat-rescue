#include "Ave.h"
#include "spritesheets/ave_spritesheet.h"
#include "Contexto.h"
#include "animacao.h"
#include "Bala.h"

#include <cstdlib>

using jogo::Contexto;

namespace atores
{
    Ave::Ave()
    {
        Textura    = sprite::TEX_AVE;
        AnimAtual  = AVE_VOAR;
        FrameAtual = 0;

        Largura = 45;
        Altura  = 35;
        _Estado = AVE_ESTADO_VOANDO;

        Pos     = jogo::Vetor2(30, 120);
        Sentido = jogo::Vetor2(0,  1);

        _HP = 2000;
    }

    void Ave::Atualizar()
    {
        switch (_Estado)
        {
            case AVE_ESTADO_VOANDO: {
                if (Pos.Y < Contexto::Video.Height / 10 ||
                    Pos.Y + Altura > Contexto::Video.Height / 10 * 7.5)
                {
                    Sentido.Y *= -1;
                }

                if (Contexto::Video.frames % 40 == 0 && (rand() % 100) < 50)
                {
                    if ((rand() % 100) > 40) //40% de chance do ataque azul
                    {
                        Atacar(BALA_OVAL_AZUL);
                    }
                    else
                    {
                        if ((rand() % 100) > 50) //50% de chance do ataque rosa
                        {
                            Atacar(BALA_ONDULAR_ROSA);
                        }
                        else
                        {
                            Atacar(BALA_FOGO_AMARELO_ROSA);
                        }
                    }
                }

                Pos += Sentido;
            } break;

            case AVE_ESTADO_PARADO: {
                auto &animacao = sprite::ave.animacoes[AnimAtual];
                if (FrameAtual >= animacao.frames.size() - 1)
                {
                    _Estado = AVE_ESTADO_VOANDO;
                    AnimAtual = AVE_VOAR;
                    FrameAtual = 0;
                }
            } break;
        }

        Animar();
    }

    void Ave::Atacar(u8 tipo_bala)
    {
        switch (tipo_bala)
        {
            case BALA_OVAL_AZUL: {
                _Estado = AVE_ESTADO_PARADO;
                AnimAtual = AVE_ATACAR;
                FrameAtual = 0;

                Vetor2 centro = Centro();

                Contexto::Balas.push_back(Bala(
                    centro.X + 50, centro.Y + 50, BALA_OVAL_AZUL,
                    centro.X - 5, centro.Y - 5
                ));
                Contexto::Balas.push_back(Bala(
                    centro.X - 50, centro.Y - 50, BALA_OVAL_AZUL,
                    centro.X - 5, centro.Y - 5
                ));
                Contexto::Balas.push_back(Bala(
                    centro.X + 50, centro.Y - 50, BALA_OVAL_AZUL,
                    centro.X - 5, centro.Y - 5
                ));
                Contexto::Balas.push_back(Bala(
                    centro.X - 50, centro.Y + 50, BALA_OVAL_AZUL,
                    centro.X - 5, centro.Y - 5
                ));

            } break;

            case BALA_ONDULAR_ROSA: {
                _Estado = AVE_ESTADO_PARADO;
                AnimAtual = AVE_ATACAR;
                FrameAtual = 0;

                Contexto::Balas.push_back(Bala(Pos.X + Largura, Pos.Y - (Altura/2) - 5,
                    BALA_ONDULAR_ROSA));

                Contexto::Balas.push_back(Bala(Pos.X + Largura, Pos.Y + (Altura/2) + 5,
                    BALA_ONDULAR_ROSA));
            } break;

            case BALA_FOGO_AMARELO_ROSA: {
                _Estado = AVE_ESTADO_PARADO;
                AnimAtual = AVE_ATACAR;
                FrameAtual = 0;

                Contexto::Balas.push_back(
                    Bala(
                        Pos.X + Largura, Pos.Y,
                        BALA_FOGO_AMARELO_ROSA,
                        Contexto::Bruxa.Pos.X,
                        Contexto::Bruxa.Pos.Y
                    )
                );

                Contexto::Balas.push_back(
                    Bala(
                        Pos.X, Pos.Y + 40,
                        BALA_FOGO_AMARELO_ROSA,
                        Contexto::Bruxa.Pos.X,
                        Contexto::Bruxa.Pos.Y
                    )
                );

                Contexto::Balas.push_back(
                    Bala(
                        Pos.X, Pos.Y - 40,
                        BALA_FOGO_AMARELO_ROSA,
                        Contexto::Bruxa.Pos.X,
                        Contexto::Bruxa.Pos.Y
                    )
                );
            } break;
        }
    }

    void Ave::LevarDano(u16 dano)
    {
        if (_HP > 0 && (_HP - dano) > 0)
        {
            _HP -= dano;
        }
        else
        {
            _HP = 0;
        }
    }

    void Ave::Animar()
    {
        auto &animacao = sprite::ave.animacoes[AnimAtual];

        if (Contexto::Video.frames % animacao.framerate == 0)
        {
            if (animacao.frames.size() > 1)
            {
                if (FrameAtual < animacao.frames.size() || animacao.loop)
                {
                    FrameAtual++;
                }

                if (FrameAtual >= animacao.frames.size() && animacao.loop)
                {
                    FrameAtual = 0;
                }
            }
        }

        auto x = animacao.frames[FrameAtual].x;
        auto y = animacao.frames[FrameAtual].y;
        auto w = animacao.frames[FrameAtual].w;
        auto h = animacao.frames[FrameAtual].h;

        Contexto::Video.RenderizarTextura(Contexto::Video.Texturas[Textura],
           Pos.X, Pos.Y, x, y, w, h);

        Contexto::Video.RenderizarTextura(
            Contexto::Video.Texturas[sprite::TEX_BARRA_VIDA],
            5, 5, 0, 0, _HP/20, 20, 0.0
        );
    }
}
