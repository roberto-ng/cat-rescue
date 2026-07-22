#ifndef GATO_SPRITESHEET_H
#define GATO_SPRITESHEET_H

#include <vector>
#include "animacao.h"

namespace sprite
{
    enum gato_tipos {
        GATO_TIPO_CINZA,
        GATO_TIPO_ROSA
    };

    extern std::vector<spritesheet> gatos; 
}

#endif
