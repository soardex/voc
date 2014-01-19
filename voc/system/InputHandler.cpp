#include "InputHandler.h"

CInputHandler::CInputHandler()
    : m_nClose(0)
{
}

CInputHandler::~CInputHandler()
{
}

void CInputHandler::update()
{
    m_nClose = 0;
    while (SDL_PollEvent(&m_sEvent))
    {
        switch (m_sEvent.type)
        {
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                if (m_sEvent.key.keysym.sym == SDLK_ESCAPE)
                    m_nClose = 1;
                break;
            case SDL_QUIT:
                    m_nClose = 1;
                break;
        }
    }
}

