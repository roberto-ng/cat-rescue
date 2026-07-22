#include "Vetor2.h"

#include <cmath>

namespace jogo
{
    Vetor2::Vetor2(f32 x, f32 y)
    {
        X = x;
        Y = y;
    }

    f32 Vetor2::Comprimento()
    {
        return sqrt((X * X) + (Y * Y));
    }

    Vetor2 Vetor2::Unidade()
    {
        Vetor2 A(X, Y);
        return A / A.Comprimento();
    }

    Vetor2 Vetor2::operator+(Vetor2 B)
    {
        return Vetor2(this->X + B.X, this->Y + B.Y);
    }

    Vetor2 Vetor2::operator-(Vetor2 B)
    {
        return Vetor2(this->X - B.X, this->Y - B.Y);
    }

    void Vetor2::operator+=(Vetor2 B)
    {
        X += B.X;
        Y += B.Y;
    }

    void Vetor2::operator-=(Vetor2 B)
    {
        X -= B.X;
        Y -= B.Y;
    }

    Vetor2 Vetor2::operator*(Vetor2 B)
    {
        return Vetor2(X * B.X, Y * B.Y);
    }

    Vetor2 Vetor2::operator/(Vetor2 B)
    {
        return Vetor2(X / B.X, Y / B.Y);
    }

    Vetor2 Vetor2::operator*(f32 num)
    {
        return Vetor2(X * num, Y * num);
    }

    Vetor2 Vetor2::operator/(f32 num)
    {
        return Vetor2(X / num, Y / num);
    }

    bool Vetor2::operator==(Vetor2 B)
    {
        return this->X == B.X && this->Y == B.Y;
    }

    bool Vetor2::operator!=(Vetor2 B)
    {
        return this->X != B.X || this->Y != B.Y;
    }
}
