#ifndef GAMECORE_H
#define GAMECORE_H

#include <structs.h>

namespace MediumCore{
    class GameCore{
        private:
            static Location location;

        public:
            static void LoadLocation(int id);
            
    };
}

#endif