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

#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "../Commons.h"

class CPhysicsManager
{
public:
    explicit CPhysicsManager();
    ~CPhysicsManager();

    void init();
    void destroy();
    void update();

    btDiscreteDynamicsWorld* getDynamicsWorld() const { return m_psWorld; }

private:
    btBroadphaseInterface *m_psBroadphase;
    btDefaultCollisionConfiguration *m_psCollisionConfiguration;
    btCollisionDispatcher *m_psDispatcher;
    btSequentialImpulseConstraintSolver *m_psSolver;
    btDiscreteDynamicsWorld *m_psWorld;
};

#endif /* end of include guard: PHYSICSMANAGER_H */
