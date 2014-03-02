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

#ifndef EMPERORSYSTEM_H
#define EMPERORSYSTEM_H

#include "Commons.h"

#include "system/Renderer.h"
#include "system/EventHandler.h"
#include "system/ScriptManager.h"
#include "system/TextureManager.h"
#include "system/PhysicsManager.h"
#include "system/FontManager.h"
#include "system/SpriteManager.h"

class CEmperorSystem
{
public:
    explicit CEmperorSystem();
    ~CEmperorSystem();

    void init();
    void destroy();
    void update();

    CRenderer* getRenderer() const { return m_psRenderer; }
    CEventHandler* getEventHandler() const { return m_psEventHandler; }
    CScriptManager* getScriptManager() const { return m_psScriptManager; }
    CTextureManager* getTextureManager() const { return m_psTextureManager; }
    CPhysicsManager* getPhysicsManager() const { return m_psPhysicsManager; }
    CFontManager* getFontManager() const { return m_psFontManager; }
    CSpriteManager* getSpriteManager() const { return m_psSpriteManager; }

protected:
    void initializeRenderer();
    void initializeEventHandler();
    void initializeScriptManager();
    void initializeTextureManager();
    void initializePhysicsManager();
    void initializeFontManager();
    void initializeSpriteManager();

    unsigned int getRealTime() const;

private:
    CRenderer *m_psRenderer;
    CEventHandler *m_psEventHandler;
    CScriptManager *m_psScriptManager;
    CTextureManager *m_psTextureManager;
    CPhysicsManager *m_psPhysicsManager;
    CFontManager *m_psFontManager;
    CSpriteManager *m_psSpriteManager;
};

#endif /* end of include guard: EMPERORSYSTEM_H */

