#include "spritesheets/tubarao_spritesheet.h"

namespace sprite
{
    spritesheet tubarao {
        "tubarao_png",
        {
            {
                false, 1, "derrotado",
                {
                    { 0, 0, 14, 12 }
                }
            },
            {
                true, 5, "grande",
                {
                    { 0, 12,  14, 24 },
                    { 0, 60,  14, 24 },
                    { 0, 108, 14, 24 },
                    { 0, 156, 14, 24 }
                }
            },
            {
                true, 5, "grande_inverso",
                {
                    { 0, 36,  14, 24 },
                    { 0, 84,  14, 24 },
                    { 0, 132, 14, 23 },
                    { 0, 180, 14, 24 }
                }
            },
            {
                true, 5, "pequeno",
                {
                    { 0, 204, 14, 12 },
                    { 0, 228, 14, 12 },
                    { 0, 252, 14, 12 },
                    { 0, 276, 14, 12 }
                }
            },
            {
                true, 5, "pequeno_inverso",
                {
                    { 0, 216, 14, 12 },
                    { 0, 240, 14, 12 },
                    { 0, 264, 14, 12 },
                    { 0, 288, 14, 12 }
                }
            }
        }
    }; 
}