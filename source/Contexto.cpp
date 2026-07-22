#include "Contexto.h"
#include "Letra.h"

#include <algorithm>
#include <memory>
#include <string>

using std::string;
using atores::CarregarFrase;
using atores::RenderizarFrase;

namespace jogo
{
    atores::Bruxa           Contexto::Bruxa;
    atores::Ave             Contexto::Ave;
    graficos::Video         Contexto::Video;
    vector<atores::Agua>    Contexto::Aguas;
    vector<atores::Ilha>    Contexto::Ilhas;
    vector<atores::Gato>    Contexto::Gatos;
    vector<atores::Bala>    Contexto::Balas;

    bool Contexto::Cima     = false;
    bool Contexto::Baixo    = false;
    bool Contexto::Esquerda = false;
    bool Contexto::Direita  = false;

    void Contexto::Atualizar()
    {
        Video.IniciarFrame();
        Video.frames++;
        Video.ChecarEntrada();

        if (Video.frames % 200 == 0)
        {
            //A cada 200 frames, 40% de chance de uma nova ilha
            if ((rand() % 100) < 40)
            {
                Ilhas.push_back(atores::Ilha());
            }
        }

        //remove a ilha caso ela saia da tela
        RemoverItemSe<atores::Ilha>(Ilhas, [](atores::Ilha ilha) -> bool {
            if (ilha.Pos.X > Video.Width)
                return true;

            return false;
        });

        //remove o gato caso ele saia da tela e não esteja ajudando
        RemoverItemSe<atores::Gato>(Gatos, [](atores::Gato gato) -> bool {
            if (gato.Pos.X > Video.Width && gato.Estado() != atores::GATO_AJUDANDO)
                return true;

            return false;
        });

        //remove bala se ela sair fora da tela ou se for destruida
        RemoverItemSe<atores::Bala>(Balas, [](atores::Bala bala) -> bool {
            if (bala.Destruir)
                return true;

            if (bala.Pos.X > Video.Width  + 50  || bala.Pos.X < -50 ||
                bala.Pos.Y > Video.Height + 50  || bala.Pos.Y < -50)
            {
                return true;
            }

            return false;
        });

        //Escreve a quantidade de gatos ajudando na tela
        string qtd = std::to_string(Contexto::ContarGatosAjudando());
        auto frase = CarregarFrase(qtd, Contexto::Video.Width - 50, 10, 0.5);
        RenderizarFrase(frase, 0.5);

        /**auto frase_link = CarregarFrase(
            "https://github.com/robertonazareth/cat-rescue",
            0, Contexto::Video.Height - 50
        );
        RenderizarFrase(frase_link);**/

        for (auto &ilha : Ilhas)
        {
            ilha.Atualizar();
        }
        
        Ave.Atualizar();

        //renderiza os gatos que não estão ajudando primeiro
        for (auto &gato : Gatos)
        {
            if (gato.Estado() != atores::GATO_AJUDANDO)
                gato.Atualizar();
        }

        for (auto &gato : Gatos)
        {
            if (gato.Estado() == atores::GATO_AJUDANDO)
                gato.Atualizar();
        }

        Bruxa.Atualizar();

        for (auto &bala : Balas)
        {
            bala.Atualizar();
        }

        for (auto &agua : Aguas)
        {
            agua.Atualizar();
        }

        Video.EncerrarFrame();
    }

    u8 Contexto::ContarGatosAjudando()
    {
        u8 quantidade = 0;
        for (auto gato : Gatos)
        {
            if (gato.Estado() == atores::GATO_AJUDANDO)
            {
                ++quantidade;
            }
        }

        return quantidade;
    }

    u8 Contexto::PosicaoGatosAjudando(atores::Gato *gatoProcurado)
    {
        u8 qtd = -1;

        for (auto &gato : Gatos)
        {
            if (gato.Estado() == atores::GATO_AJUDANDO)
                ++qtd;

            //para o loop se é o mesmo gato
            if (std::addressof(gato) == gatoProcurado)
            {
                return qtd;
            }
        }

        return -1;
    }

    template <typename T>
    void Contexto::RemoverItemSe(vector<T> &lista, function<bool(T)> remover)
    {
        lista.erase(
            std::remove_if(lista.begin(), lista.end(), remover),
            lista.end()
        );
    }
}
