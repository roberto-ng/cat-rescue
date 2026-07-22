#ifndef TUBARAO_H
#define TUBARAO_H

#include "Ator.h"
#include "tipos.h"

using namespace jogo;

namespace atores
{
    enum TubaraoAnim
    { 
        TUBARAO_DERROTADO,
        TUBARAO_GRANDE,
        TUBARAO_GRANDE_INVERSO,
        TUBARAO_PEQUENO,
        TUBARAO_PEQUENO_INVERSO
    };

    enum TubaraoTipo { TUBARAO_TIPO_PEQUENO, TUBARAO_TIPO_GRANDE };

    class Tubarao : public Ator
    {
        private:
            u8     _tipo;
            Vetor2 _sentido;
        public:
            u8 AnimAtual;
            u8 FrameAtual;

            Tubarao(u8 tipo, Vetor2 pos);
            void Atualizar(s16 limite_comeco, s16 limite_fim);
    };
}

#endif
