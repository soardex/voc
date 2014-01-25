#include "InputHandler.h"

CInputHandler::CInputHandler()
    : m_nClose(0),
    m_nStickyKeys(0)
{

    assert((sizeof(m_bSpectatorKeys) / sizeof(m_bSpectatorKeys[0])) == E_SK_MAX);
    for (int i = 0; i < int(sizeof(m_bSpectatorKeys) / sizeof(m_bSpectatorKeys[0])); i++)
        m_bSpectatorKeys[i] = false;
}

CInputHandler::~CInputHandler()
{
}

void CInputHandler::update()
{
    m_nClose = 0;
    m_nStickyKeys = 0;

    while (SDL_PollEvent(&m_sEvent))
    {
        if (m_sEvent.type == SDL_KEYUP)
        {
            if (!m_nStickyKeys)
            {
                for (int i = 0; i < int(sizeof(m_bSpectatorKeys) / sizeof(m_bSpectatorKeys[0])); i++)
                    m_bSpectatorKeys[i] = false;
            }
        }

        switch (m_sEvent.type)
        {
            case SDL_KEYDOWN:
                if (m_sEvent.key.keysym.sym == SDLK_UP)
                    m_bSpectatorKeys[E_SK_UP] = true;

                if (m_sEvent.key.keysym.sym == SDLK_DOWN)
                    m_bSpectatorKeys[E_SK_DN] = true;

                if (m_sEvent.key.keysym.sym == SDLK_LEFT)
                    m_bSpectatorKeys[E_SK_LT] = true;

                if (m_sEvent.key.keysym.sym == SDLK_RIGHT)
                    m_bSpectatorKeys[E_SK_RT] = true;

                if (m_sEvent.key.keysym.sym == SDLK_w)
                    m_bSpectatorKeys[E_SK_W] = true;

                if (m_sEvent.key.keysym.sym == SDLK_a)
                    m_bSpectatorKeys[E_SK_A] = true;

                if (m_sEvent.key.keysym.sym == SDLK_s)
                    m_bSpectatorKeys[E_SK_S] = true;

                if (m_sEvent.key.keysym.sym == SDLK_d)
                    m_bSpectatorKeys[E_SK_D] = true;

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

