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

#include "PhysicsManager.h"

CPhysicsManager::CPhysicsManager()
    : m_psBroadphase(nullptr),
    m_psCollisionConfiguration(nullptr),
    m_psDispatcher(nullptr),
    m_psSolver(nullptr),
    m_psWorld(nullptr)
{
}

CPhysicsManager::~CPhysicsManager()
{
}

void CPhysicsManager::init()
{
    m_psBroadphase = new btDbvtBroadphase();
    m_psCollisionConfiguration = new btDefaultCollisionConfiguration();
    m_psDispatcher = new btCollisionDispatcher(m_psCollisionConfiguration);
    m_psSolver = new btSequentialImpulseConstraintSolver();
    m_psWorld = new btDiscreteDynamicsWorld(m_psDispatcher, m_psBroadphase, m_psSolver, m_psCollisionConfiguration);
    m_psWorld->setGravity(btVector3(0.0, -9.8, 0.0));
}

void CPhysicsManager::destroy()
{
    delete m_psWorld;
    delete m_psSolver;
    delete m_psDispatcher;
    delete m_psCollisionConfiguration;
    delete m_psBroadphase;
}

void CPhysicsManager::update()
{
    m_psWorld->stepSimulation(0, 10);
}

