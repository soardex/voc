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
    : m_psRenderer(nullptr),
    m_psEventHandler(nullptr),
    m_psScriptManager(nullptr),
    m_psTextureManager(nullptr),
    m_psPhysicsManager(nullptr)
{
}

CEmperorSystem::~CEmperorSystem()
{
}

void CEmperorSystem::init()
{
    initializeRenderer();
    initializeEventHandler();
    initializeScriptManager();
    initializeTextureManager();
    initializePhysicsManager();
}

void CEmperorSystem::destroy()
{
    if (m_psPhysicsManager)
    {
        m_psPhysicsManager->destroy();
        
        delete m_psPhysicsManager;
        m_psPhysicsManager = nullptr;
    }

    if (m_psTextureManager)
    {
        delete m_psTextureManager;
        m_psTextureManager = nullptr;
    }

    if (m_psScriptManager)
    {
        m_psScriptManager->destroy();
        
        delete m_psScriptManager;
        m_psScriptManager = nullptr;
    }

    if (m_psEventHandler)
    {
        m_psEventHandler->destroy();
        
        delete m_psEventHandler;
        m_psEventHandler = nullptr;
    }

    if (m_psRenderer)
    {
        m_psRenderer->destroy();

        delete m_psRenderer;
        m_psRenderer = nullptr;
    }
}

void CEmperorSystem::update()
{
    if (m_psRenderer)
        m_psRenderer->update();

    if (m_psEventHandler)
        m_psEventHandler->update();

    if (m_psPhysicsManager)
        m_psPhysicsManager->update();
}


void CEmperorSystem::initializeRenderer()
{
    m_psRenderer = new CRenderer();
    if (!m_psRenderer)
        fprintf(stderr, "[ERR] System Error: Unable to initialize renderer.");

    m_psRenderer->init();
}

void CEmperorSystem::initializeEventHandler()
{
    m_psEventHandler = new CEventHandler();
    if (!m_psEventHandler)
        fprintf(stderr, "[ERR] System Error: Unable to initialize event handler.");

    m_psEventHandler->init();
}

void CEmperorSystem::initializeScriptManager()
{
    m_psScriptManager = new CScriptManager();
    if (!m_psScriptManager)
        fprintf(stderr, "[ERR] System Error: Unable to initialize script manager.");

    m_psScriptManager->init();
}

void CEmperorSystem::initializeTextureManager()
{
    m_psTextureManager = new CTextureManager();
    if (!m_psTextureManager)
        fprintf(stderr, "[ERR] System Error: Unable to initialize texture manager.");
}

void CEmperorSystem::initializePhysicsManager()
{
    m_psPhysicsManager = new CPhysicsManager();
    if (!m_psPhysicsManager)
        fprintf(stderr, "[ERR] System Error: Unable to initialize physics manager.");

    m_psPhysicsManager->init();
}

unsigned int CEmperorSystem::getRealTime() const
{
    timeval tv;
    gettimeofday(&tv, 0);

    return ((unsigned int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

