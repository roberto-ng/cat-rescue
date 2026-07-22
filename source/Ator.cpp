#include "Ator.h"

namespace atores
{
    bool Ator::ColidindoCom(Ator b)
    {
        if (Pos.X < b.Pos.X + b.Largura &&
            Pos.X + Largura > b.Pos.X   &&
            Pos.Y < b.Pos.Y + b.Altura  &&
            Altura + Pos.Y > b.Pos.Y)
        {
            return true;
        }

        return false;
    }

    bool Ator::ColidindoCom(Vetor2 b, u16 largura, u16 altura)
    {
        if (Pos.X < b.X + largura &&
            Pos.X + largura > b.X   &&
            Pos.Y < b.Y + altura  &&
            altura + Pos.Y > b.Y)
        {
            return true;
        }

        return false;
    }

    Vetor2 Ator::Centro()
    {
        Vetor2 centro(0, 0);

        centro.X = Pos.X + (Largura / 2);
        centro.Y = Pos.Y + (Altura  / 2);

        return centro;
    }
}
