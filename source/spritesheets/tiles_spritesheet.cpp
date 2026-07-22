#include "spritesheets/tiles_spritesheet.h"

namespace sprite
{
    spritesheet tiles {
        "tiles_png",
        { 
            {
                false, 0, "agua",
                {
                    { 0, 0, 16, 16 }
                }
            }, 
            {
                false, 0, "chao_1",
                {
                    { 16, 0, 16, 16 }
                }
            },
            {
                false, 0, "chao_2",
                {
                    { 32, 0, 16, 16 }
                }
            }, 
            {
                false, 0, "chao_3",
                {
                    { 32, 0, 16, 16 }
                }
            },
            {
                false, 0, "grama_1",
                {
                    { 63, 0, 16, 16 }
                }
            }, 
            {
                false, 0, "grama_2",
                {
                    { 79, 0, 16, 16 }
                }
            }, 
            {
                false, 0, "grama_3",
                {
                    { 96, 0, 16, 16 }
                }
            },
            {
                false, 0, "grama_borda",
                {
                    { 111, 0, 16, 16 }
                }
            } 
        }
    };
}