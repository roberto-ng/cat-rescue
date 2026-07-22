#include "spritesheets/witch_spritesheet.h"

namespace sprite
{
    spritesheet bruxa {
        "witch_png",
        {
            {
                true, 5, "voar",
                {
                    { 0,   0, 32, 32 },
                    { 32,  0, 32, 32 },
                    { 64,  0, 32, 32 },
                    { 96,  0, 32, 32 },
                    { 128, 0, 32, 32 },
                    { 160, 0, 32, 32 },
                    { 192, 0, 32, 32 },
                    { 224, 0, 32, 32 }
                }
            },
            {
                false, 1, "voar_baixo",
                {
                    { 256, 0, 32, 32 }
                }
            },
            {
                false, 1, "voar_cima",
                {
                    { 288, 0, 32, 32 }
                }
            }
        }
    };
    
}