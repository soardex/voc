#include "SceneHandler.h"
#include "../utils/GeometryUtils.h"


CSceneHandler::CSceneHandler()
    : m_psModel(0)
{
}

CSceneHandler::~CSceneHandler()
{
}

void CSceneHandler::init()
{
    m_psModel = new CModelLoader();
    m_psModel->init();
    m_psModel->load("./build/assets/models/collada/chevy.dae");

    glViewport(0, 0, 640, 480);

    m_sProjection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 750.0f);
    m_sModel = glm::mat4(1.0f);
    m_sView = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, -5.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mvp = m_sProjection * m_sView * m_sModel;
    glLoadMatrixf(glm::value_ptr(mvp));
}

void CSceneHandler::update(float tse, glm::mat4 view)
{
    glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);

    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glEnable(GL_LIGHT1);

    glm::mat4 mvp = m_sProjection * view * m_sModel;
    glLoadMatrixf(glm::value_ptr(mvp));

    glPushMatrix();
        float extent = 30.0f, step = 1.0f, h = -0.6f;
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
            for (int line = -extent; line <= extent; line += step)
            {
                glVertex3f(line, h, extent);
                glVertex3f(line, h, -extent);

                glVertex3f(extent, h, line);
                glVertex3f(-extent, h, line);
            }
        glEnd();

        //glPushMatrix();
        //    glColor3f(0.75, 0.75, 0.75);
        //    glBegin(GL_TRIANGLES);
        //        glVertex3f(-0.5, 0.0, 5.0);
        //        glVertex3f(0.0, 0.5, 5.0);
        //        glVertex3f(0.0, 0.0, -5.0);
        //    glEnd();
        //glPopMatrix();

        glColor3f(1.0, 1.0, 1.0);
        if (m_psModel)
            m_psModel->render();

        //glPushMatrix();
        //    glTranslatef(0.0f, 0.0f, -300.0f);
        //    glRotatef(90.0, 1.0, 0.0, 0.0);

        //    float x, y, z = -50.0f;
        //    glBegin(GL_POINTS);
        //        for (float angle = 0.0; angle <= (2.0 * 3.1415) * 4.0; angle += 0.1)
        //        {
        //            x = 50.0 * sin(angle);
        //            y = 50.0 * cos(angle);

        //            glVertex3f(x, y, z);
        //            z += 0.5;
        //        }
        //    glEnd();
        //glPopMatrix();
    glPopMatrix();
}

void CSceneHandler::destroy()
{
    if (m_psModel)
    {
        delete m_psModel;
        m_psModel = NULL;
    }
}

