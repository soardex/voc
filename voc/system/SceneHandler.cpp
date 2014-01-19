#include "SceneHandler.h"
#include "../utils/GeometryUtils.h"

CSceneHandler::CSceneHandler()
{
}

CSceneHandler::~CSceneHandler()
{
}

void CSceneHandler::init()
{
}

void CSceneHandler::update()
{
    glViewport(0, 0, 640, 480);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, float(640.0f / 480.0f), 1.0f, 750.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        float extent = 30.0f, step = 1.0f, h = -0.4f;
        glBegin(GL_LINES);
            for (int line = -extent; line <= extent; line += step)
            {
                glVertex3f(line, h, extent);
                glVertex3f(line, h, -extent);

                glVertex3f(extent, h, line);
                glVertex3f(-extent, h, line);
            }
        glEnd();

        glPushMatrix();
            glTranslatef(0.0f, 0.0f, -300.0f);
            glRotatef(90.0, 1.0, 0.0, 0.0);
            glRotatef(0.0, 0.0, 1.0, 0.0);

            float x, y, z = -50.0f;
            glBegin(GL_POINTS);
                for (float angle = 0.0; angle <= (2.0 * 3.1415) * 4.0; angle += 0.1)
                {
                    x = 50.0 * sin(angle);
                    y = 50.0 * cos(angle);

                    glVertex3f(x, y, z);
                    z += 0.5;
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void CSceneHandler::destroy()
{
}

