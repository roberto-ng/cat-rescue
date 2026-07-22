#ifndef ATOR_H
#define ATOR_H

#include "Video.h"
#include "Vetor2.h"
#include "tipos.h"

using jogo::Vetor2;

namespace atores
{
    class Ator
    {
        public:
            Vetor2 Pos;
            u8  Textura;
            u8  FrameAtual;
            u8  AnimAtual;
            u16 Largura;
            u16 Altura;
	    
	        bool ColidindoCom(Ator b);
            bool ColidindoCom(Vetor2 b, u16 largura, u16 altura);
            Vetor2 Centro();
    };
}

#endif
