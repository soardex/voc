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
 * Copyright (C) Fitz Abucay, 2014
 */

#include "Renderer.h"

CRenderer::CRenderer()
    : m_psWindow(nullptr)
{
}

CRenderer::~CRenderer()
{
}

void CRenderer::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        exit(1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    m_psWindow = SDL_CreateWindow("VOC fizzafruit",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480, SDL_WINDOW_OPENGL);

    m_sContext = SDL_GL_CreateContext(m_psWindow);
    if (!m_sContext)
        exit(1);

    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        fprintf(stderr, "[ERR] Renderer Error: %s\n", glewGetErrorString(status));
        exit(1);
    }

    SDL_GL_SetSwapInterval(1);
}

void CRenderer::update()
{
    SDL_GL_SwapWindow(m_psWindow);
    SDL_Delay(10);
}

void CRenderer::destroy()
{
    if (m_sContext)
        SDL_GL_DeleteContext(m_sContext);

    SDL_DestroyWindow(m_psWindow);
    SDL_Quit();
}

