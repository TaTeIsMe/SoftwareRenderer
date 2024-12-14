#include "EventHandler.h"
#include"SDL.h"

void EventHandler::handleEvents()
{
        SDL_Event event;
        SDL_GetRelativeMouseState(&mousedX, &mousedY);
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        WSAD.x = keystate[SDL_SCANCODE_D] - keystate[SDL_SCANCODE_A];
        WSAD.z = keystate[SDL_SCANCODE_W] - keystate[SDL_SCANCODE_S];
        verticalMove = keystate[SDL_SCANCODE_SPACE] - keystate[SDL_SCANCODE_LSHIFT];

        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            }
        }

}

bool EventHandler::getIsRunning()const {
    return isRunning;
}

int EventHandler::getMousedX() const
{
    return mousedX;
}

int EventHandler::getMousedY() const
{
    return mousedY;
}

int EventHandler::getVerticalMove() const
{
    return verticalMove;
}

Vector3 EventHandler::getWSAD()
{
    return WSAD;
}
