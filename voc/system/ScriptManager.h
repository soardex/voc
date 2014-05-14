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

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "../Commons.h"

class CScriptManager
{
public:
    explicit CScriptManager();
    ~CScriptManager();

    void init();
    void destroy();

private:
    lua_State *m_psScriptState;
};

#endif /* end of include guard: SCRIPTMANAGER_H */

