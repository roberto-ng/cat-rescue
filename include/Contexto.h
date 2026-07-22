#ifndef CONTEXTO_H
#define CONTEXTO_H

#include <vector>
#include <functional>

#include "tipos.h"
#include "Bruxa.h"
#include "Ave.h"
#include "Video.h"
#include "Agua.h"
#include "Ilha.h"
#include "Tubarao.h"
#include "Gato.h"
#include "Bala.h"

using std::vector;
using std::function;

namespace jogo
{
    enum EstadoJogo
    {
        JOGO_TITULO,
        JOGO_JOGANDO,
        JOGO_VITORIA,
        JOGO_FIM
    };

    class Contexto
    {
        public:
            static atores::Bruxa Bruxa;
            static atores::Ave Ave;
            static graficos::Video Video;
            static vector<atores::Agua> Aguas;
            static vector<atores::Ilha> Ilhas;
            static vector<atores::Gato> Gatos;
            static vector<atores::Bala> Balas;

            static bool Cima;
            static bool Baixo;
            static bool Esquerda;
            static bool Direita;
            static bool Confirmar;
            static EstadoJogo Estado;

            static void Atualizar();
            static void Reiniciar();
            static u8 ContarGatosAjudando();
            static u8 PosicaoGatosAjudando(atores::Gato *gatoProcurado);

            template <typename T>
            static void RemoverItemSe(vector<T> &lista, function<bool(T)> remover);
    };
}

#endif
