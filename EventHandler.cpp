#include "EventHandler.h"
#include"SDL.h"

void EventHandler::handleEvents()
{
        SDL_Event event;
        SDL_GetRelativeMouseState(&mousedX, &mousedY);
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_D])WSAD.x = 1;
        if (keystate[SDL_SCANCODE_A])WSAD.x = -1;
        if (keystate[SDL_SCANCODE_SPACE])verticalMove = 1;
        if (keystate[SDL_SCANCODE_LSHIFT])verticalMove = -1;
        if (keystate[SDL_SCANCODE_W])WSAD.z = 1;
        if (keystate[SDL_SCANCODE_S])WSAD.z = -1;
        if (!keystate[SDL_SCANCODE_SPACE] && !keystate[SDL_SCANCODE_LSHIFT])verticalMove = 0;
        if (!keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D])WSAD.x = 0;
        if (!keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S])WSAD.z = 0;

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
