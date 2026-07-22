#ifndef VETOR2_H
#define VETOR2_H

#include "tipos.h"

namespace jogo
{
    class Vetor2
    {
        public:
            f32 X;
            f32 Y;

            Vetor2() = default;

            /** Construtor
             * @param x Ponto X do vetor.
             * @param y Ponto Y do vetor.
             */
            Vetor2(f32 x, f32 y);

            /** Calcula o comprimento/módulo do vetor
             * @return Comprimento do vetor
             */
            f32 Comprimento();

            /** Deixa o vetor com o comprimento de 1.0
             * @return O vetor criado
             */
            Vetor2 Unidade();

            Vetor2 operator+(Vetor2 B);
            Vetor2 operator-(Vetor2 B);
            void operator+=(Vetor2 B);
            void operator-=(Vetor2 B);
            Vetor2 operator*(Vetor2 B);
            Vetor2 operator/(Vetor2 B);
            Vetor2 operator*(f32 num);
            Vetor2 operator/(f32 num);
            void operator*=(f32 num);
            void operator/=(f32 num);
            bool operator==(Vetor2 B);
            bool operator!=(Vetor2 B);
    };
}
#endif
