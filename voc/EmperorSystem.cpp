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

#include "EmperorSystem.h"

CEmperorSystem::CEmperorSystem()
    : m_psRenderer(nullptr)
{
}

CEmperorSystem::~CEmperorSystem()
{
}

void CEmperorSystem::init()
{

}

void CEmperorSystem::destroy()
{
    if (m_psRenderer)
    {
        m_psRenderer->destroy();

        delete m_psRenderer;
        m_psRenderer = nullptr;
    }
}

void CEmperorSystem::initialiazeRenderer()
{
    m_psRenderer = new CRenderer();
    if (!m_psRenderer)
        fprintf(stderr, "[ERR] System Error: Unable to initialize renderer.");

    m_psRenderer->init();
}

unsigned int CEmperorSystem::getRealTime() const
{
    timeval tv;
    gettimeofday(&tv, 0);

    return ((unsigned int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

