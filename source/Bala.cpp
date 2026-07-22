#include <cmath>
#include <cstdio>
#include "Bala.h"
#include "spritesheets/balas_spritesheet.h"
#include "Contexto.h"

namespace atores
{
    Bala::Bala(f32 x, f32 y, u8 tipo, f32 px, f32 py, u8 delay)
    {
        Pos  = Vetor2(x, y);
        Textura = sprite::TEX_BALAS;
        _tipo = tipo;
        Angulo = 1;
        FrameAtual = 0;
        AnimAtual = 0;
        Destruir = false;

        switch (tipo)
        {
            case BALA_OVAL_AZUL: {
                _colisaoTipo = COLISAO_DISTANCIA;
                _distanciaLimite = 13.0;
                _posGiro  = Vetor2(x, y);
                _vel = Vetor2(0, 0);
                _velMax = Vetor2(4, 0);
                _velMin = Vetor2(0, 0);
                _giro = 0.065;
                _raio = 40;
                _i = 0.0;
                _pivo = Vetor2(px, py);
                _dano = 1;
                Largura = 10;
                Altura = 14;

            } break;

            case BALA_ONDULAR_ROSA: {
                _colisaoTipo = COLISAO_AABB;
                _vel = Vetor2(0, 0);
                _velMax = Vetor2(2, 0);
                _velMin = Vetor2(0, 0);
                _dano = 1;
                Largura = 10;
                Altura = 38;
            } break;

            case BALA_FOGO_AMARELO_ROSA: {
                _colisaoTipo = COLISAO_DISTANCIA;
                _distanciaLimite = 14.0;
                _delay = delay;
                _vel = Vetor2(0, 0);
                _velMax = Vetor2(4, 4);
                _velMin = Vetor2(0, 0);
                _dano = 1;

                Vetor2 alvo(px, py);
                //valor unidade da diferença entre os pontos
                _direcao = (alvo - Pos).Unidade();

                Altura = 14;
                Largura = 14;
            } break;

            case BALA_FOGUETE_AZUL: {
                _colisaoTipo = COLISAO_AABB;
                Pos = Vetor2(x, y);
                _vel = Vetor2(0, 0);
                _velMax = Vetor2(1, 1);
                _velMin = Vetor2(-5, -5);
                _dano = 2;

                Largura = 12;
                Altura = 7;

            } break;

            case BALA_FOGUETE_AMARELO: {
                _colisaoTipo = COLISAO_AABB;
                Pos = Vetor2(x, y);
                _vel =  Vetor2(x, y);
                _vel = Vetor2(0, 0);
                _velMax = Vetor2(1, 1);
                _velMin = Vetor2(-5, -5);
                _dano = 4;

                Largura = 12;
                Altura = 7;
            } break;
        }
    }

    void Bala::Atualizar()
    {
        switch (_tipo)
        {
            case BALA_OVAL_AZUL: {
                GirarEmTorno();

                if (_vel.X < _velMax.X && _vel.X >= _velMin.X)
                {
                    _vel.X += 0.043;
                }

                _pivo     += _vel;
                _posGiro += _vel;

                bool colidindo = ChecarColisao();
                if (colidindo)
                {
                    Contexto::Bruxa.LevarDano();
                }
            } break;

            case BALA_ONDULAR_ROSA: {
                if (_vel.X < _velMax.X && _vel.X >= _velMin.X)
                {
                    _vel.X += 0.035;
                }
                Pos += _vel;

                if (ColidindoCom(Contexto::Bruxa))
                {
                    Contexto::Bruxa.LevarDano();
                }
            } break;

            case BALA_FOGO_AMARELO_ROSA: {
                if (_vel.X < _velMax.X && _vel.X >= _velMin.X)
                {
                    _vel.X += 0.065;
                }

                if (_vel.Y < _velMax.Y && _vel.Y >= _velMin.Y)
                {
                    _vel.Y += 0.065;
                }

                Pos += _direcao * _vel;

                bool colidindo = ChecarColisao();
                if (colidindo)
                {
                    Contexto::Bruxa.LevarDano();
                }
            } break;

            case BALA_FOGUETE_AZUL: {
                auto alvo = Contexto::Ave.Centro();
                //valor unidade da diferença entre os pontos
                auto direcao = (Pos - alvo).Unidade();

                if (_vel.X < _velMax.X && _vel.X > _velMin.X)
                {
                    _vel.X -= 0.085;
                }

                if (_vel.Y < _velMax.Y && _vel.Y > _velMin.Y)
                {
                    _vel.Y -= 0.085;
                }

                if (ColidindoCom(alvo, 10, 10))
                {
                    Contexto::Ave.LevarDano(_dano);
                    Destruir = true;
                }
                else
                {
                    Pos += direcao * _vel;
                }
            } break;

            case BALA_FOGUETE_AMARELO: {
                if (_vel.X < _velMax.X && _vel.X > _velMin.X)
                {
                    _vel.X -= 0.085;
                }

                if (!ColidindoCom(Contexto::Ave))
                {
                    Pos += _vel;
                }
                else
                {
                    Contexto::Ave.LevarDano(_dano);
                    Destruir = true;
                }
            } break;
        }

        Animar();
    }

    void Bala::GirarEmTorno()
    {
        Vetor2 tmp = (_posGiro - _pivo).Unidade() * _raio;
        _posGiro = _pivo + tmp;

        f32 novo_x = _pivo.X+(_posGiro.X-_pivo.X)*cos(_giro)-(_posGiro.Y-_pivo.Y)*sin(_giro);
        f32 novo_y = _pivo.Y+(_posGiro.X-_pivo.X)*sin(_giro)+(_posGiro.Y-_pivo.Y)*cos(_giro);

        _posGiro = Vetor2(novo_x, novo_y);
        Angulo += 10;

        Pos = _posGiro + Vetor2(_i, 0);
    }

    bool Bala::ChecarColisao()
    {
        switch (_colisaoTipo)
        {
            case COLISAO_DISTANCIA: {
                auto diferenca = Centro() - Contexto::Bruxa.Centro();
                if (diferenca.Comprimento() < _distanciaLimite)
                {
                    return true;
                }
            } break;

            case COLISAO_AABB: {
                if (ColidindoCom(Contexto::Bruxa))
                    return true;

                return false;
            } break;
        }

        return false;
    }

    void Bala::Animar()
    {
        auto &animacao = sprite::balas.at(_tipo).animacoes.at(0);

        if (Contexto::Video.frames % animacao.framerate == 0)
        {
            if (animacao.frames.size() > 1)
            {
                if (FrameAtual < animacao.frames.size() - 1)
                {
                    FrameAtual++;
                }
                else if (animacao.loop)
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
           Pos.X, Pos.Y, x, y, w, h, Angulo);
    }
}
