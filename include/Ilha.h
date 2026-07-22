#ifndef ILHA_H
#define ILHA_H

#include <vector>

#include "Ator.h"
#include "Tubarao.h"
#include "tipos.h"

using std::vector;

namespace atores
{
    class Ilha : public Ator
    {
        private:
            static u8 _qtd_horizontal; 
            static u8 _qtd_vertical;
            static vector< vector<u8> > _mapa;
            vector<Tubarao> _tubaroes;
        public:
            Ilha();
            void Atualizar();
    };
}

#endif
