#include "EmperorSystem.h"
#include "Commons.h"

#include "system/AssetsHandler.h"
#include "system/InputHandler.h"
#include "system/RenderHandler.h"
#include "system/SceneHandler.h"
#include "system/SoundHandler.h"

class CEmperorSystem::CImpl
{
public:
    explicit CImpl()
        : m_psRender(0),
        m_psInput(0),
        m_psScene(0)
    {
    }

    void init()
    {
        m_psRender = new CRenderHandler();
        m_psRender->init();

        m_psInput = new CInputHandler();

        m_psScene = new CSceneHandler();
        m_psScene->init();
    }

    void update()
    {
        while (true)
        {
            m_psInput->update();
            m_psScene->update();

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
    CInputHandler *m_psInput;
    CSceneHandler *m_psScene;
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

