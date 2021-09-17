#include <gamecore.h>

namespace MediumCore{

    aFPoint GameCore::playerPosition = {1, 1};
    aFPoint GameCore::playerCollider = {30, 30};
    aFPoint GameCore::cameraPosition = {0, 0};
    float GameCore::maxSpeed = 10;
    float GameCore::boostSpeed = 500;
    float GameCore::brakeSpeed = 300;
    aFPoint GameCore::direction = {0, 0};
    aFPoint GameCore::acceleration = {0, 0};

    bool GameCore::leftPressed = false;
    bool GameCore::rightPressed = false;
    bool GameCore::upPressed = false;
    bool GameCore::downPressed = false;

    void GameCore::ProcessKey(SDL_KeyboardEvent event){
        //TODO: test input
        switch(event.keysym.sym){
            case SDLK_a:
                if(event.state == SDL_PRESSED)
                    leftPressed = true;
                else
                    leftPressed = false;
            break;
            case SDLK_d:
                if(event.state == SDL_PRESSED)
                    rightPressed = true;
                else
                    rightPressed = false;
            break;
            case SDLK_w:
                if(event.state == SDL_PRESSED)
                    upPressed = true;
                else
                    upPressed = false;
            break;
            case SDLK_s:
                if(event.state == SDL_PRESSED)
                    downPressed = true;
                else
                    downPressed = false;
            break;
        }
    }

    void GameCore::Paint(Renderer &renderer){
        direction = {0, 0};

        if(leftPressed)
            direction.x = -1;
        if(rightPressed)
            direction.x = 1;
        if(upPressed)
            direction.y = -1;
        if(downPressed)
            direction.y = 1;

        float res_x = screen_width / 2;
        float res_y = screen_height / 2;

        cameraPosition = {res_x - playerPosition.x, res_y - playerPosition.y};

        float x_odd = abs(acceleration.x - direction.x);
        float y_odd = abs(acceleration.y - direction.y);

        if(x_odd > 1)
            x_odd = 1;
        if(y_odd > 1)
            y_odd = 1;

        if(boostSpeed < Time::deltaTime)
            boostSpeed = Time::deltaTime;
        if(brakeSpeed < Time::deltaTime)
            brakeSpeed = Time::deltaTime;

        if(direction.x == 0){
            //braking
            if(acceleration.x > direction.x){
                acceleration.x -= x_odd * Time::deltaTime / brakeSpeed;
            }
            if(acceleration.x < direction.x){
                acceleration.x += x_odd * Time::deltaTime / brakeSpeed;
            }
        }
        if(direction.x > 0){
            if(acceleration.x < 0){
                //braking
                acceleration.x += abs(acceleration.x) * Time::deltaTime / brakeSpeed;
            }
            //TODO: check collider here
            if(acceleration.x < direction.x){
                acceleration.x += x_odd * Time::deltaTime / boostSpeed;
            }
        }
        if(direction.x < 0){
            if(acceleration.x > 0){
                //braking
                acceleration.x -= abs(acceleration.x) * Time::deltaTime / brakeSpeed;
            }
            //TODO: check collider here
            if(acceleration.x > direction.x){
                acceleration.x -= x_odd * Time::deltaTime / boostSpeed;
            }
        }

        if(direction.y == 0){
            //braking
            if(acceleration.y > direction.y){
                acceleration.y -= y_odd * Time::deltaTime / brakeSpeed;
            }
            if(acceleration.y < direction.y){
                acceleration.y += y_odd * Time::deltaTime / brakeSpeed;
            }
        }
        if(direction.y > 0){
            if(acceleration.y < 0){
                //braking
                acceleration.y += abs(acceleration.y) * Time::deltaTime / brakeSpeed;
            }
            //TODO: check collider here
            if(acceleration.y < direction.y){
                acceleration.y += y_odd * Time::deltaTime / boostSpeed;
            }
        }
        if(direction.y < 0){
            if(acceleration.y > 0){
                //braking
                acceleration.y -= abs(acceleration.y) * Time::deltaTime / brakeSpeed;
            }
            //TODO: check collider here
            if(acceleration.y > direction.y){
                acceleration.y -= y_odd * Time::deltaTime / boostSpeed;
            }
        }

        acceleration.x = truncf(acceleration.x * 1000000) / 1000000;
        acceleration.y = truncf(acceleration.y * 1000000) / 1000000;

        printf("%f : %f, %f : %f\n", direction.x, direction.y, acceleration.x, acceleration.y);

        //TODO: test colliders

        if(acceleration.x < 0 && playerPosition.x > 0 || acceleration.x > 0 && playerPosition.x + playerCollider.x < 30 * 10)
            playerPosition.x += acceleration.x * maxSpeed;
        if(acceleration.y < 0 && playerPosition.y > 0 || acceleration.y > 0 && playerPosition.y + playerCollider.y < 30 * 10)
            playerPosition.y += acceleration.y * maxSpeed;

        //TODO: test location render
        renderer.SelectAtlas("test_atlas");
        for(int x = 0; x < 10; x++){
            for(int y = 0; y < 10; y++){
                renderer.DrawSprite(SDL_Rect({x * 30 + cameraPosition.x, y * 30 + cameraPosition.y, 30, 30}), "floor");
            }
        }
        renderer.DrawSprite(SDL_Rect({(int)round(playerPosition.x) + cameraPosition.x, (int)round(playerPosition.y) + cameraPosition.y, 30, 30}), "tree");
    }

    void GameCore::LoadLocation(int id){

    }
}