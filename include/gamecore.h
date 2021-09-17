#ifndef GAMECORE_H
#define GAMECORE_H

#include <structs.h>
#include <renderer.h>
#include <aparams.h>
#include <timeparams.h>

namespace MediumCore{
    class GameCore{
        private:
            static Location location;
            static aFPoint playerPosition;
            static aFPoint playerCollider;
            static aFPoint cameraPosition;
            static float maxSpeed;
            static float boostSpeed;
            static float brakeSpeed;
            static aFPoint direction;
            static aFPoint acceleration;

            static bool leftPressed;
            static bool rightPressed;
            static bool upPressed;
            static bool downPressed;

        public:
            static void ProcessKey(SDL_KeyboardEvent event);
            static void Paint(Renderer &renderer);
            static void LoadLocation(int id);
            
    };
}

#endif