#ifndef BRUXA_H
#define BRUXA_H

#include "Ator.h"
#include "Video.h"
#include "Vetor2.h"

namespace atores
{
    enum BruxaAnim { BRUXA_VOAR, BRUXA_VOAR_BAIXO, BRUXA_VOAR_CIMA };

    class Bruxa : public Ator
    {
        private:
            /** Duração da invencibilidade, quando a bruxa leva dano */
            const u8 _FramesInvencibilidadeMax = 60;

            /** Frames de invencibilidade restantes */
            u8 _FramesInvencibilidade;

        public:
            bool Invencivel;

            Bruxa();
            void Atualizar();
            void LevarDano();
            void Animar();
    };
}

#endif
