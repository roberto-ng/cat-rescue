#ifndef AGUA_H
#define AGUA_H

#include <vector>

#include "Ator.h"
#include "Vetor2.h"
#include "Video.h"
#include "animacao.h"
#include "tipos.h"

namespace atores
{
    class Agua : public Ator
    {
        public:
            static void Inicializar();

            Agua(s16 x = 0, s16 y = 0);
            void Atualizar();
    };
}

#endif
