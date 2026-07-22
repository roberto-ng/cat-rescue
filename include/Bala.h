#ifndef BALA_H
#define BALA_H

#include "Ator.h"

namespace atores
{
    enum BalaColisaoTipo {
        COLISAO_AABB,
        COLISAO_DISTANCIA
    };

    enum BalaTipo {
        BALA_OVAL_AZUL,
        BALA_ONDULAR_ROSA,
        BALA_FOGO_AMARELO_ROSA,
        BALA_FOGUETE_AZUL,
        BALA_FOGUETE_AMARELO
    };

    class Bala : public Ator
    {
        private:
            u8 _tipo;
            u8 _colisaoTipo;
            u8 _delay;
            u16 _dano;
            f32 _giro;
            f32 _i;
            f32 _raio;
            f32 _distanciaLimite;
            Vetor2 _posGiro;
            Vetor2 _vel;
            Vetor2 _velMax;
            Vetor2 _velMin;
            Vetor2 _pivo;
            Vetor2 _direcao;

        public:
            f32 Angulo;
            bool Destruir;

            /** Construtor da bala.
             * @param x Ponto X da bala.
             * @param y Ponto Y da bala.
             * @param px Pivo X, ou ponto X do alvo caso a bala seja do tipo fogo.
             * @param py Pivo Y, ou ponto Y do alvo caso a bala seja do tipo fogo.
             * @param tipo Tipo da bala, usando o enum BalaTipo.
             */
            Bala(f32 x, f32 y, u8 tipo, f32 px = 0, f32 py = 0, u8 delay = 0);

            /** Atualiza a bala de acordo com o tipo. */
            void Atualizar();

            /** Faz a bala girar em torno do pivo */
            void GirarEmTorno();

            /** Checa se a bala está colidindo com a bruxa
             *  por AABB ou pela distância entre os pontos,
             *  de acordo com o tipo da bala.
             * @brief Checa se a bruxa está colidindo com a bruxa.
             * @return true caso a bala esteja colidindo com a bruxa
             */
            bool ChecarColisao();

            /** Anima o objeto */
            void Animar();
    };
}

#endif // BALA_H
