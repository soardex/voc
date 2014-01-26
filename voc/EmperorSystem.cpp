#include "EmperorSystem.h"
#include "Commons.h"

#include "system/AssetsHandler.h"
#include "system/InputHandler.h"
#include "system/PhysicsHandler.h"
#include "system/RenderHandler.h"
#include "system/SceneHandler.h"
#include "system/SoundHandler.h"
#include "system/TimeHandler.h"

class CEmperorSystem::CImpl
{
public:
    explicit CImpl()
        : m_psRender(0),
        m_psPhysics(0),
        m_psInput(0),
        m_psScene(0),
        m_psTimer(0)
    {
    }

    void init()
    {
        m_psRender = new CRenderHandler();
        m_psRender->init();

        m_psInput = new CInputHandler();

        m_psPhysics = new CPhysicsHandler();
        m_psPhysics->init();

        m_psScene = new CSceneHandler();
        m_psScene->init();
    }

    void update()
    {
        float previousTime = 0.0f, currentTime = float(SDL_GetTicks());
        float deltaTime = 0.0f;
        float angle = 0.0f, look = 0.0f;
        float cameraEyeX = 0.0f, cameraEyeZ = -1.0f, cameraEyeY = 0.0f;
        float cameraPosX = 0.0f, cameraPosZ = 5.0f, cameraPosY = 0.0f;
        while (true)
        {
            previousTime = currentTime;
            currentTime = float(SDL_GetTicks());
            deltaTime = (currentTime - previousTime) / 1000.0f;

            m_psInput->update();

            glm::mat4 view = glm::lookAt(glm::vec3(cameraPosX, cameraPosY, cameraPosZ),
                    glm::vec3((cameraPosX + cameraEyeX), (cameraPosY + cameraEyeY), (cameraPosZ + cameraEyeZ)),
                    glm::vec3(0.0f, 1.0f, 0.0f));

            if (m_psInput->getSpectatorKeyState(CInputHandler::SPECKEY::E_SK_UP))
            {
                cameraPosX += cameraEyeX * 3.1415f * deltaTime;
                cameraPosZ += cameraEyeZ * 3.1415f * deltaTime;
                cameraPosY += cameraEyeY * 3.1415f * deltaTime;
            }
            else if (m_psInput->getSpectatorKeyState(CInputHandler::SPECKEY::E_SK_DN))
            {
                cameraPosX -= cameraEyeX * 3.1415f * deltaTime;
                cameraPosZ -= cameraEyeZ * 3.1415f * deltaTime;
                cameraPosY -= cameraEyeY * 3.1415f * deltaTime;
            }
            else if (m_psInput->getSpectatorKeyState(CInputHandler::SPECKEY::E_SK_LT))
            {
                angle -= 3.1415f * deltaTime;
                cameraEyeX = sin(angle);
                cameraEyeZ = -cos(angle);
            }
            else if (m_psInput->getSpectatorKeyState(CInputHandler::SPECKEY::E_SK_RT))
            {
                angle += 3.1415f * deltaTime;
                cameraEyeX = sin(angle);
                cameraEyeZ = -cos(angle);
            }

            if (m_psInput->getSpectatorKeyState(CInputHandler::SPECKEY::E_SK_PGUP))
            {
                look += 3.1415f * deltaTime;
                cameraEyeY = sin(look);
            }
            else if (m_psInput->getSpectatorKeyState(CInputHandler::SPECKEY::E_SK_PGDN))
            {
                look -= 3.1415f * deltaTime;
                cameraEyeY = sin(look);
            }

            m_psPhysics->update(deltaTime);
            m_psScene->update(deltaTime, view);
            m_psRender->update();

            if (!m_psInput->isRunning())
                break;
        }
    }

    void destroy()
    {
        if (m_psScene)
        {
            m_psScene->destroy();
            delete m_psScene;
            m_psScene = NULL;
        }

        if (m_psPhysics)
        {
            m_psPhysics->destroy();
            delete m_psPhysics;
            m_psPhysics = NULL;
        }

        if (m_psInput)
        {
            delete m_psInput;
            m_psInput = NULL;
        }

        if (m_psRender)
        {
            m_psRender->destroy();
            delete m_psRender;
            m_psRender = NULL;
        }
    }

    CRenderHandler *m_psRender;
    CPhysicsHandler *m_psPhysics;
    CInputHandler *m_psInput;
    CSceneHandler *m_psScene;
    CTimeHandler *m_psTimer;
};

CEmperorSystem::CEmperorSystem()
    : m_pImpl(new CImpl)
{
    m_pImpl->init();
}

CEmperorSystem::~CEmperorSystem()
{
    m_pImpl->destroy();
}

void CEmperorSystem::run()
{
    m_pImpl->update();
}

