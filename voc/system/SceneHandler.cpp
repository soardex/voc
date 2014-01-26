#include "SceneHandler.h"
#include "../utils/GeometryUtils.h"


CSceneHandler::CSceneHandler()
    : m_fAngle(0)
{
}

CSceneHandler::~CSceneHandler()
{
}

void CSceneHandler::init()
{
    glViewport(0, 0, 640, 480);

    m_sProjection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 750.0f);
    m_sModel = glm::mat4(1.0f);
    m_sView = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, -5.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mvp = m_sProjection * m_sView * m_sModel;
    glLoadMatrixf(glm::value_ptr(mvp));

    m_fAngle = 0.0f;
}

void CSceneHandler::update(float tse, glm::mat4 view)
{
    glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glEnable(GL_LIGHT0);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    GLfloat lightPosition01[] = { 10.0f, 10.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition01);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

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

        glm::vec3 cubeVertices[12] = 
        {
            glm::vec3(0, 0, 0),
            glm::vec3(1, 0, 0),
            glm::vec3(1, 1, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 1, 1),
            glm::vec3(0, 1, 1),
            glm::vec3(0, 0, 1),
            glm::vec3(0, 1, 1),
            glm::vec3(0, 1, 0),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0)
        };
 
        glm::vec3 cubeNormals[12] = 
        {
            glm::vec3(-1, -1, -1),
            glm::vec3( 1, -1, -1),
            glm::vec3( 1,  1, -1),
            glm::vec3(-1,  1, -1),
            glm::vec3( 1, -1,  1),
            glm::vec3( 1,  1,  1),
            glm::vec3(-1,  1,  1),
            glm::vec3(-1, -1,  1),
            glm::vec3(-1,  1,  1),
            glm::vec3(-1,  1, -1),
            glm::vec3( 1, -1,  1),
            glm::vec3( 1, -1, -1)
        };

        glm::vec2 cubeTexCoords[12] =
        {
            glm::vec2(0, 1),
            glm::vec2(1, 1),
            glm::vec2(1, 0),
            glm::vec2(0, 0),
            glm::vec2(0, 1),
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(1, 1),
            glm::vec2(0, 1),
            glm::vec2(1, 1),
            glm::vec2(1, 0),
            glm::vec2(0, 0)
        };

        int cubeIndices[36] =
        {
            0, 2, 1,
            0, 3, 2,
            1, 5, 4,
            1, 2, 5,
            4, 6, 7,
            4, 5, 6,
            7, 3, 0,
            7, 6, 3,
            9, 5, 2,
            9, 8, 5,
            0, 11, 10,
            0, 10, 7
        };

        glPushMatrix();
            m_fAngle += 45 * tse;

            glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), m_fAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 translate = glm::translate(rotate, glm::vec3(0.0f, 0.0f, 0.0f));

            glMultMatrixf(glm::value_ptr(translate));
            glBegin(GL_TRIANGLES);
                for (int i = 0; i < int(sizeof(cubeIndices) / sizeof(cubeIndices[0])); i++)
                {
                    glColor4ub(255, 255, 255, 255);
                    glNormal3fv(glm::value_ptr(cubeNormals[cubeIndices[i]]));
                    glTexCoord2fv(glm::value_ptr(cubeTexCoords[cubeIndices[i]]));

                    glm::vec3 v = cubeVertices[cubeIndices[i]] - glm::vec3(0.5f);
                    v *= glm::vec3(1.0f);
                    glVertex3fv(glm::value_ptr(v));
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void CSceneHandler::destroy()
{
}

