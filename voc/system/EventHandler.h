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

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../Commons.h"

class CEventHandler
{
public:
    enum E_SPECKEY
    {
        E_SK_UP = 0,
        E_SK_DN,
        E_SK_LT,
        E_SK_RT,

        E_SK_W,
        E_SK_S,
        E_SK_A,
        E_SK_D,

        E_SK_PGUP,
        E_SK_PGDN,

        E_SK_MAX
    };

    explicit CEventHandler();
    ~CEventHandler();

    void init();
    void destroy();
    void update();

    bool getSpectatorKey(E_SPECKEY key) const { return m_bSpectatorKey[key]; }

private:
    SDL_Event m_sEvent;

    bool m_bSpectatorKey[E_SK_MAX];
};

#endif /* end of include guard: EVENTHANDLER_H */

