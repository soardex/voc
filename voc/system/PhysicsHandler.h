#ifndef _PHYSICS_HANDLER_H_
#define _PHYSICS_HANDLER_H_

#include "../Commons.h"

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

class CPhysicsHandler
{
public:
    CPhysicsHandler();

    void init();
    void update(float tse);
    void destroy();

private:
    btBroadphaseInterface *m_psBroadphase;
    btDefaultCollisionConfiguration *m_psCollisionConfiguration;
    btCollisionDispatcher *m_psDispatcher;
    btSequentialImpulseConstraintSolver *m_psSolver;
    btDiscreteDynamicsWorld *m_psWorld;
};

#endif /* end of include guard: _PHYSICS_HANDLER_H_ */
