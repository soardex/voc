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

#ifndef RENDERER_H
#define RENDERER_H

#include "../Commons.h"

class CRenderer
{
public:
    explicit CRenderer();
    ~CRenderer();

    void init();
    void update();
    void destroy();

    SDL_Window* getWindowContext() const { return m_psWindow; }
    SDL_GLContext getOpenGLContext() const { return m_sContext; }

private:
    SDL_Window *m_psWindow;
    SDL_GLContext m_sContext;
};

#endif /* end of include guard: RENDERER_H */

