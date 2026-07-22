#ifndef MAGO_H
#define MAGO_H

#include "Ator.h"

namespace atores
{
    enum AveAnim { AVE_VOAR, AVE_ATACAR, AVE_DERROTADO };
    enum AveEstado { AVE_ESTADO_VOANDO, AVE_ESTADO_PARADO };

    class Ave : public Ator
    {
        private:
            u8 _Estado;
            u16 _HP;

            void Atacar(u8 tipo_bala);
            void Animar();

        public:
            jogo::Vetor2 Sentido;

            Ave();
            void Atualizar();
            void LevarDano(u16 dano);
            u16 HP() const { return _HP; }
    };
}

#endif
