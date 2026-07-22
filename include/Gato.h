#ifndef GATO_H
#define GATO_H

#include "Ator.h"
#include "Vetor2.h"
#include "tipos.h"

using jogo::Vetor2;

namespace atores
{
    enum estado_gato {
        GATO_ESPERANDO,
        GATO_AJUDANDO,
        GATO_SUMINDO
    };

    enum anim_gato {
        GATO_ANIM_PUFF,
        GATO_ANIM_NORMAL,
        GATO_ANIM_VOAR,
        GATO_ANIM_VOAR_INVERSO
    };

    class Gato : public Ator
    {
        private:
            u8 _tipo;
            u8 _estado;
            Vetor2 _alvo;

            void Animar();

        public:
            Gato(Vetor2 pos);
            void Atualizar();
            void Atacar(u8 pos);
            void LevarDano();
            u8 Estado() { return _estado; }
    };
}

#endif
