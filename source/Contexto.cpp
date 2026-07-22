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
    bool Contexto::Confirmar = false;
    EstadoJogo Contexto::Estado = JOGO_TITULO;

    void Contexto::Reiniciar()
    {
        Aguas.clear();
        Ilhas.clear();
        Gatos.clear();
        Balas.clear();
        Bruxa.Reiniciar();
        Ave = atores::Ave();
        atores::Agua::Inicializar();
        Video.frames = 0;
        Estado = JOGO_JOGANDO;
    }

    void Contexto::Atualizar()
    {
        Video.IniciarFrame();
        Video.frames++;
        Video.ChecarEntrada();

        if (Estado == JOGO_TITULO)
        {
            auto titulo = CarregarFrase("CAT RESCUE", 0, 65, 0.5);
            auto instrucao = CarregarFrase(
#ifdef _3DS
                "PRESS A TO START",
#else
                "PRESS ENTER TO START",
#endif
                0, 150, 0.25
            );
            CentralizarFrase(titulo, 0.5, Video.Width);
            CentralizarFrase(instrucao, 0.25, Video.Width);
            RenderizarFrase(titulo, 0.5);
            RenderizarFrase(instrucao, 0.25);
            if (Confirmar)
            {
                Confirmar = false;
                Reiniciar();
            }
            Video.EncerrarFrame();
            return;
        }

        if (Estado == JOGO_VITORIA || Estado == JOGO_FIM)
        {
            const char *mensagem = Estado == JOGO_VITORIA ? "YOU WIN" : "GAME OVER";
            auto fim = CarregarFrase(mensagem, 0, 75, 0.5);
            auto instrucao = CarregarFrase(
#ifdef _3DS
                "PRESS A TO RESTART",
#else
                "PRESS ENTER TO RESTART",
#endif
                0, 150, 0.25
            );
            CentralizarFrase(fim, 0.5, Video.Width);
            CentralizarFrase(instrucao, 0.25, Video.Width);
            RenderizarFrase(fim, 0.5);
            RenderizarFrase(instrucao, 0.25);
            if (Confirmar)
            {
                Confirmar = false;
                Reiniciar();
            }
            Video.EncerrarFrame();
            return;
        }

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
        string qtd = "CATS " + std::to_string(Contexto::ContarGatosAjudando()) + "/3";
        auto frase = CarregarFrase(qtd, 120, 8, 0.2);
        RenderizarFrase(frase, 0.2);

        string lives = "LIVES " + std::to_string(Contexto::Bruxa.HP);
        auto frase_lives = CarregarFrase(lives, 270, 8, 0.2);
        RenderizarFrase(frase_lives, 0.2);

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

        if (Ave.HP() == 0)
            Estado = JOGO_VITORIA;
        else if (Bruxa.HP == 0)
            Estado = JOGO_FIM;

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
