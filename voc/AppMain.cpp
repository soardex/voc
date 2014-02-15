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

#include "AppMain.h"

CAppMain::CAppMain()
{
    m_psSystem = new CEmperorSystem();
    if (!m_psSystem)
    {
        fprintf(stderr, "[ERR] Application Error: Unable to initialize Emperor System.");
        exit(1);
    }
}

CAppMain::~CAppMain()
{
    if (m_psSystem)
    {
        m_psSystem->destroy();

        delete m_psSystem;
        m_psSystem = nullptr;
    }
}

void CAppMain::run()
{
}

int main()
{
    CAppMain *voc = new CAppMain();
    if (voc)
    {
        voc->run();

        delete voc;
        voc = nullptr;
    }

    return 0;
}

