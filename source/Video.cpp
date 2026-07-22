#include "Video.h"

#define _USE_MATH_DEFINES

#include <cstdio>
#include <cstdlib>
#include <cmath>

#ifdef _3DS
#include <witch_png.h>
#include <tiles_png.h>
#include <ave_png.h>
#include <tubarao_png.h>
#include <gatos_png.h>
#include <balas_png.h>
#include <barra_de_vida_png.h>
#include <boxy_bold_font_png.h>
#endif

#include "Contexto.h"

using jogo::Contexto;

namespace graficos
{
    Video::Video()
    {
#ifdef _3DS
        ST_Init();
        ST_DebugSetOn();
        consoleInit(GFX_BOTTOM, NULL);
        ST_RenderSetBackground(0xCC, 0xFF, 0x66);

        CliqueAtual = Vetor2(-30, -30);
        CliqueAnterior = Vetor2(-30, -30);
#else
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("Erro ao iniciar SDL: %s\n", SDL_GetError());
            exit(1);
        }

        _janela = SDL_CreateWindow(
            "Cat Rescue",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Width * 2,
            Height * 2,
            SDL_WINDOW_SHOWN
        );

        if (_janela == nullptr)
        {
            printf("Erro ao criar janela: %s\n", SDL_GetError());
            SDL_Quit();
            exit(1);
        }

        _ren = SDL_CreateRenderer(_janela, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (_ren == nullptr)
        {
            printf("Erro ao criar renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(_janela);
            SDL_Quit();
            exit(1);
        }

        SDL_RenderSetLogicalSize(_ren, Width, Height);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");

        CliqueAtual = Vetor2(-30, -30);
        CliqueAnterior = Vetor2(-30, -30);
#endif
    }

    Video::~Video()
    {
#ifdef _3DS
        for (auto &textura : Texturas)
        {
            ST_SpritesheetFreeSpritesheet(textura);
        }

        ST_Fini();
#else
        for (auto &textura : Texturas)
        {
            SDL_DestroyTexture(textura);
        }

        SDL_DestroyRenderer(_ren);
        SDL_DestroyWindow(_janela);
        IMG_Quit();
        SDL_Quit();
#endif
    }

    void Video::ChecarEntrada()
    {
#ifdef _3DS
        //checa as entradas
        ST_InputScan();

        //checa a touchscreen
        touchPosition toque;
        hidTouchRead(&toque);

        if (toque.px == 0 && toque.py == 0)
        {
            CliqueAtual = Vetor2(-30, -30);
            CliqueAnterior = Vetor2(-30, -30);
        }
        else
        {
            CliqueAnterior = CliqueAtual;
            CliqueAtual = Vetor2(toque.px, toque.py);
        }

        //checa o circle pad
        circlePosition pos; //posição do circle pad
        hidCircleRead(&pos);

        //printf("\x1b[1;1H%04d; %04d", pos.dx, pos.dy);

        if (ST_InputButtonDown(KEY_DUP) || pos.dy >= 70)
            Contexto::Cima = true;
        else
            Contexto::Cima = false;
        
        if (ST_InputButtonDown(KEY_DDOWN) || pos.dy <= -70)
            Contexto::Baixo = true;
        else 
            Contexto::Baixo = false;
        
        if (ST_InputButtonDown(KEY_DLEFT) || pos.dx <= -70)
            Contexto::Esquerda = true;
        else
            Contexto::Esquerda = false;
        
        if (ST_InputButtonDown(KEY_DRIGHT) || pos.dx >= 70)
            Contexto::Direita = true;
        else
            Contexto::Direita = false;
            
        if (ST_InputButtonPressed(KEY_START)) 
            sair = true;
#else   
        //Se o botão estiver sendo pressionado
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            s32 x, y;
            SDL_GetMouseState(&x, &y);
            CliqueAnterior = CliqueAtual;
            CliqueAtual = Vetor2(x, y);
        }

        while (SDL_PollEvent(&_evento))
        {
            if (_evento.type == SDL_QUIT)
                sair = true;

            //ao clicar
            if (_evento.type == SDL_MOUSEBUTTONDOWN)
            {
                s32 x, y;
                SDL_GetMouseState(&x, &y);
                CliqueAtual = Vetor2(x, y);
                CliqueAnterior = Vetor2(x, y);
            }

            if (_evento.type == SDL_MOUSEBUTTONUP)
            {
                CliqueAtual = Vetor2(-30, -30);
                CliqueAnterior = Vetor2(-30, -30);
            }

            if (_evento.type == SDL_FINGERDOWN)
            {
                const f32 x = _evento.tfinger.x;
                const f32 y = _evento.tfinger.y;
                CliqueAtual = Vetor2(x, y);
                CliqueAnterior = Vetor2(x, y);
            }

            if (_evento.type == SDL_FINGERMOTION)
            {
                const f32 x = _evento.tfinger.x;
                const f32 y = _evento.tfinger.y;
                CliqueAnterior = CliqueAtual;
                CliqueAtual = Vetor2(x, y);
            }

            if (_evento.type == SDL_FINGERUP)
            {
                CliqueAtual = Vetor2(-30, -30);
                CliqueAnterior = Vetor2(-30, -30);
            }

            if (_evento.type == SDL_KEYUP)
            {
                switch (_evento.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        Contexto::Esquerda = false;
                        break;
                    case SDLK_RIGHT:
                        Contexto::Direita = false;
                        break;
                    case SDLK_UP:
                        Contexto::Cima = false;
                        break;
                    case SDLK_DOWN:
                        Contexto::Baixo = false;
                        break;
                }
            }

            if (_evento.type == SDL_KEYDOWN)
            {
                switch (_evento.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        Contexto::Esquerda = true;
                        break;
                    case SDLK_RIGHT:
                        Contexto::Direita = true;
                        break;
                    case SDLK_UP:
                        Contexto::Cima = true;
                        break;
                    case SDLK_DOWN:
                        Contexto::Baixo = true;
                        break;
                    case SDLK_ESCAPE:
                        sair = true;
                        break;
                }
            }
        }
#endif
    }

    void Video::CarregarTextura(const std::string nome)
    {
#ifdef _3DS
        textura *tex;
        if (nome == "witch.png")
            tex = ST_SpritesheetCreateSpritesheetPNG(witch_png);
        else if (nome == "tiles.png")
            tex = ST_SpritesheetCreateSpritesheetPNG(tiles_png);
        else if (nome == "ave.png")
            tex = ST_SpritesheetCreateSpritesheetPNG(ave_png);
        else if (nome == "tubarao.png")
            tex = ST_SpritesheetCreateSpritesheetPNG(tubarao_png);
        else if (nome == "gatos.png")
            tex = ST_SpritesheetCreateSpritesheetPNG(gatos_png);
        else if (nome == "balas.png")
            tex = ST_SpritesheetCreateSpritesheetPNG(balas_png);
        else if (nome == "barra_de_vida.png")
            tex = ST_SpritesheetCreateSpritesheetPNG(barra_de_vida_png);
        else if (nome == "boxy_bold_font.png")
            tex = ST_SpritesheetCreateSpritesheetPNG(boxy_bold_font_png);

        if (tex != nullptr)
        {
            Texturas.push_back(tex);
        }
        else puts("Erro ao carregar textura");
#else
        const std::string path = "data/" + nome;
        textura *tex = IMG_LoadTexture(Renderer(), path.c_str());

        if (tex == nullptr)
        {
            printf("Erro ao carregar textura: %s", SDL_GetError());
            return;
        }

        Texturas.push_back(tex); 
#endif
    }

    void Video::RenderizarTextura(textura *tex, s16 x, s16 y,
        u16 corte_x, u16 corte_y, u16 corte_w, u16 corte_h,
        f32 angulo,  f32 escala)
    {
#ifdef _3DS
        s32 rad = M_PI * angulo / 180.0; //angulo em radianos

        if (angulo > 1.0 || escala != 1.0)
        {
            ST_RenderSpritePositionScaleRotate(tex, corte_x, corte_y,
                corte_w, corte_h, x+8, y+8, escala, rad);
        }
        else
        {
            ST_RenderSpritePosition(tex, corte_x, corte_y,
                corte_w, corte_h, x, y);
        }
#else
        const SDL_Rect corte { corte_x, corte_y, corte_w, corte_h };
        SDL_Rect destino { x, y, corte_w, corte_h };

        destino.w *= escala;
        destino.h *= escala;

        SDL_RenderCopyEx(Renderer(), tex, &corte, &destino,
                         angulo, NULL, SDL_FLIP_NONE);
#endif
    }

    void Video::LimparTela()
    {
#ifdef _3DS
        ST_RenderStartFrame(GFX_TOP);
#else
        SDL_RenderClear(Renderer());
#endif
    }

    void Video::IniciarFrame()
    {
#ifdef _3DS
        ST_RenderStartFrame(GFX_TOP);
#else
        SDL_Rect ret{ 0, 0, Width, Height };

        LimparTela();
        //SDL_RenderFillRect(Renderer(), &ret);
#endif
    }

    void Video::EncerrarFrame()
    {
#ifdef _3DS
        ST_RenderEndRender();
#else
        SDL_RenderPresent(Renderer());
#endif
    }

    Vetor2 Video::CliqueAtualEscalado()
    {
#ifndef _3DS
        s32 janela_largura, janela_altura;
        SDL_GetWindowSize(Janela(), &janela_largura, &janela_altura);

        s32 escala_largura = CliqueAtual.X / (janela_largura /(s32)Width);
        s32 escala_altura =  CliqueAtual.Y / (janela_altura / (s32)Height);

        return Vetor2(escala_largura, escala_altura);
#else
        return CliqueAtual;
#endif
    }

    Vetor2 Video::CliqueAnteriorEscalado()
    {
#ifndef _3DS
        s32 janela_largura, janela_altura;
        SDL_GetWindowSize(Janela(), &janela_largura, &janela_altura);

        s32 escala_largura = CliqueAnterior.X / (janela_largura /(s32)Width);
        s32 escala_altura =  CliqueAnterior.Y / (janela_altura / (s32)Height);

        return Vetor2(escala_largura, escala_altura);
#else
        return CliqueAnterior;
#endif
    }
} 

