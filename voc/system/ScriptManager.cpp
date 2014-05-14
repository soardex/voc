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

#include "ScriptManager.h"

CScriptManager::CScriptManager()
    : m_psScriptState(nullptr)
{
}

CScriptManager::~CScriptManager()
{
    m_psScriptState = nullptr;
}

void CScriptManager::init()
{
    m_psScriptState = lua_open();
    luaopen_base(m_psScriptState);
    luaopen_table(m_psScriptState);
    luaopen_string(m_psScriptState);
    luaopen_math(m_psScriptState);
    luaL_openlibs(m_psScriptState);
}

void CScriptManager::destroy()
{
    lua_close(m_psScriptState);
}

