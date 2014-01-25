#include "PhysicsHandler.h"

CPhysicsHandler::CPhysicsHandler()
{
}

void CPhysicsHandler::init()
{
    m_psBroadphase = new btDbvtBroadphase();
    m_psCollisionConfiguration = new btDefaultCollisionConfiguration();
    m_psDispatcher = new btCollisionDispatcher(m_psCollisionConfiguration);
    m_psSolver = new btSequentialImpulseConstraintSolver();
    m_psWorld = new btDiscreteDynamicsWorld(m_psDispatcher, m_psBroadphase, m_psSolver, m_psCollisionConfiguration);
    m_psWorld->setGravity(btVector3(0.0f, -9.8f, 0.0f));
}

void CPhysicsHandler::update(float tse)
{
    m_psWorld->stepSimulation(tse, 10);
}

void CPhysicsHandler::destroy()
{
    delete m_psWorld;
    delete m_psSolver;
    delete m_psDispatcher;
    delete m_psCollisionConfiguration;
    delete m_psBroadphase;
}

