/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) IOIO, 2014
 */

#include "EventHandler.h"

CEventHandler::CEventHandler()
    : m_bRunningState(true)
{
}

CEventHandler::~CEventHandler()
{
}

void CEventHandler::init()
{
    assert((sizeof(m_bSpectatorKey) / sizeof(m_bSpectatorKey[0])) == E_SK_MAX);
    for (size_t i = 0; i < (sizeof(m_bSpectatorKey) / sizeof(m_bSpectatorKey[0])); i++)
        m_bSpectatorKey[i] = false;

    m_bRunningState = true;
}

void CEventHandler::destroy()
{
}

void CEventHandler::update()
{
    m_bRunningState = true;

    while (SDL_PollEvent(&m_sEvent))
    {
        switch (m_sEvent.type)
        {
            case SDL_KEYDOWN:
                if (m_sEvent.key.keysym.sym == SDLK_UP)
                    m_bSpectatorKey[E_SK_UP] = true;

                if (m_sEvent.key.keysym.sym == SDLK_DOWN)
                    m_bSpectatorKey[E_SK_DN] = true;

                if (m_sEvent.key.keysym.sym == SDLK_LEFT)
                    m_bSpectatorKey[E_SK_LT] = true;

                if (m_sEvent.key.keysym.sym == SDLK_RIGHT)
                    m_bSpectatorKey[E_SK_RT] = true;

                if (m_sEvent.key.keysym.sym == SDLK_w)
                    m_bSpectatorKey[E_SK_W] = true;

                if (m_sEvent.key.keysym.sym == SDLK_a)
                    m_bSpectatorKey[E_SK_A] = true;

                if (m_sEvent.key.keysym.sym == SDLK_s)
                    m_bSpectatorKey[E_SK_S] = true;

                if (m_sEvent.key.keysym.sym == SDLK_d)
                    m_bSpectatorKey[E_SK_D] = true;

                if (m_sEvent.key.keysym.sym == SDLK_PAGEUP)
                    m_bSpectatorKey[E_SK_PGUP] = true;

                if (m_sEvent.key.keysym.sym == SDLK_PAGEDOWN)
                    m_bSpectatorKey[E_SK_PGDN] = true;
                break;
            case SDL_KEYUP:
                for (size_t i = 0; i < (sizeof(m_bSpectatorKey) / sizeof(m_bSpectatorKey[0])); i++)
                    m_bSpectatorKey[i] = false;

                if (m_sEvent.key.keysym.sym == SDLK_ESCAPE)
                    m_bRunningState = false;

                break;
            case SDL_QUIT:
                m_bRunningState = false;
                break;
        }
    }
}

