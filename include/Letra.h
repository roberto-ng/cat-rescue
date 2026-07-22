#ifndef LETRA_HEADER
#define LETRA_HEADER

#include "Ator.h"
#include <vector>
#include <string>
#include <cctype>

using std::vector;
using std::string;

namespace atores
{
    class Letra : public Ator
    {
        private:
            u8 _tipo;

        public:
            Letra(f32 x, f32 y, u8 letra);
            void Renderizar(f32 escala = 0.4);
    };

    vector<Letra> CarregarFrase(string frase, f32 x, f32 y, f32 escala = 0.138);
    void RenderizarFrase(vector<Letra> letras, f32 escala = 0.138);
}

#endif // LETRA_HEADER
