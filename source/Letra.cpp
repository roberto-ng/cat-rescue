#include "Letra.h"
#include "spritesheets/letra_spritesheet.h"
#include "Contexto.h"

using namespace sprite;

namespace atores
{
    vector<Letra> CarregarFrase(string frase, f32 x, f32 y, s32 escala)
    {
        vector<Letra> letras;

        for (s32 i = 0; i < frase.size(); ++i)
        {
            if (frase[i] == 0)
                return letras;

            if (i == 0)
            {
                letras.push_back(Letra(x, y, frase[i]));
            }
            else
            {
                Letra anterior = letras[i - 1];
                s32 novoX = anterior.Pos.X + anterior.Largura/7;

                letras.push_back(Letra(novoX, y, frase[i]));
            }
        }

        return letras;
    }
    
    void RenderizarFrase(vector<Letra> letras, f32 escala)
    {
        for (auto &letra : letras)
        {
            letra.Renderizar(escala);
        }
    }

    Letra::Letra(f32 x, f32 y, u8 letra)
    {
        Pos = Vetor2(x, y);
        Textura = TEX_FONTE;
        letra = toupper(letra);
        switch (letra)
        {
            case '0':
                _tipo = LETRA_0;
                break;
            case '1':
                _tipo = LETRA_1;
                break;
            case '2':
                _tipo = LETRA_2;
                break;
            case '3':
                _tipo = LETRA_3;
                break;
            case '4':
                _tipo = LETRA_4;
                break;
            case '5':
                _tipo = LETRA_5;
                break;
            case '6':
                _tipo = LETRA_6;
                break;
            case '7':
                _tipo = LETRA_7;
                break;
            case '8':
                _tipo = LETRA_8;
                break;
            case '9':
                _tipo = LETRA_9;
                break;
            case '>':
                _tipo = LETRA_MAIOR_QUE;
                break;
            case 'A':
                _tipo = LETRA_A;
                break;
            case 'B':
                _tipo = LETRA_B;
                break;
            case 'C':
                _tipo = LETRA_C;
                break;
            case 'D':
                _tipo = LETRA_D;
                break;
            case 'E':
                _tipo = LETRA_E;
                break;
            case 'F':
                _tipo = LETRA_F;
                break;
            case 'G':
                _tipo = LETRA_G;
                break;
            case 'H':
                _tipo = LETRA_H;
                break;
            case 'I':
                _tipo = LETRA_I;
                break;
            case 'J':
                _tipo = LETRA_J;
                break;
            case 'K':
                _tipo = LETRA_K;
                break;
            case 'L':
                _tipo = LETRA_L;
                break;
            case 'M':
                _tipo = LETRA_M;
                break;
            case 'N':
                _tipo = LETRA_N;
                break;
            case 'O':
                _tipo = LETRA_O;
                break;
            case 'P':
                _tipo = LETRA_P;
                break;
            case 'Q':
                _tipo = LETRA_Q;
                break;
            case 'R':
                _tipo = LETRA_R;
                break;
            case 'S':
                _tipo = LETRA_S;
                break;
            case 'T':
                _tipo = LETRA_T;
                break;
            case 'U':
                _tipo = LETRA_U;
                break;
            case 'V':
                _tipo = LETRA_V;
                break;
            case 'W':
                _tipo = LETRA_W;
                break;
            case 'X':
                _tipo = LETRA_X;
                break;
            case 'Y':
                _tipo = LETRA_Y;
                break;
            case 'Z':
                _tipo = LETRA_Z;
                break;
            case ' ':
                _tipo = LETRA_ESPACO;
                break;
            case ':':
                _tipo = LETRA_DOIS_PONTOS;
                break;
            case '-':
                _tipo = LETRA_TRACINHO;
                break;
            case '/':
                _tipo = LETRA_BARRA;
                break;
            case '.':
                _tipo = LETRA_PONTO;
                break;
            default:
                _tipo = LETRA_INVALIDA;
                Altura = 0;
                Largura = 0;
                return;
        }

        Altura = sprite_letra.animacoes[_tipo].frames[0].h;
        Largura = sprite_letra.animacoes[_tipo].frames[0].w;
    }

    void Letra::Renderizar(f32 escala)
    {
        if (_tipo == LETRA_INVALIDA || _tipo == LETRA_ESPACO)
        {
            return;
        }

        auto &sprite = sprite_letra.animacoes[_tipo].frames[0];

        auto x = sprite.x;
        auto y = sprite.y;
        auto w = sprite.w;
        auto h = sprite.h;

        Contexto::Video.RenderizarTextura(
            Contexto::Video.Texturas[Textura],
            Pos.X, Pos.Y, x, y, w, h, 0.0, escala
        );
    }
}
