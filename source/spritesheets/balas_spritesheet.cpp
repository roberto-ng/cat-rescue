#include "spritesheets/balas_spritesheet.h"

namespace sprite
{
    std::vector<spritesheet> balas {
        {//bala oval azul
            "balas_png",
            {
                {
                    false, 1, "oval_azul",
                    {
                        { 19, 318, 10, 14 }
                    }
                }
            }
        },
        {//bala ondular amarela
            "balas_png",
            {
                {
                    false, 6, "ondular_amarela",
                    {
                        { 113, 591, 12, 42 },
                        { 124, 591, 12, 42 },
                        { 137, 591, 12, 42 },
                        { 151, 591, 12, 42 }
                    }
                }
            }
        },
        {//bala fogo amarelo rosa
            "balas_png",
            {
                {
                    true, 5, "fogo_amarelo_rosa",
                    {
                        { 106, 330, 14, 14 },
                        { 126, 330, 15, 14 },
                        { 145, 331, 15, 13 },
                        { 165, 329, 14, 15 }
                    }
                }
            }
        },
        {//bala foguete azul
            "balas_png",
            {
                {
                    true, 4, "foguete_azul",
                    {
                        { 154, 406, 12, 7 },
                        { 154, 463, 12, 7 }
                    }
                }
            }
        },
        {//bala foguete amarelo
            "balas_png",
            {
                {
                    true, 4, "foguete_amarelo",
                    {
                        { 221, 406, 12, 7 },
                        { 222, 463, 12, 7 }
                    }
                }
            }
        }
    };
}
