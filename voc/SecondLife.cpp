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

#include "SecondLife.h"

CSecondLife::CSecondLife(CEmperorSystem *ces)
    : m_psSystem(ces),
    m_sCurrentMatrix(1.0)
{
    m_sCreationParams.width = 640;
    m_sCreationParams.height = 480;
}

CSecondLife::~CSecondLife()
{
}

void CSecondLife::init()
{
    m_sTimer.current = m_sTimer.getUpdatedTime(); 
    m_sTimer.previous = 0.0;

    bool validated = true;
    if (validated)
    {
        std::string vertShaderSource = "./build/assets/shaders/image-2d.vs";
        std::string fragShaderSource = "./build/assets/shaders/image-2d.fs";

        GLuint vertShader = helpers::createShader(GL_VERTEX_SHADER, vertShaderSource);
        GLuint fragShader = helpers::createShader(GL_FRAGMENT_SHADER, fragShaderSource);

        validated = validated && helpers::checkShader(vertShader, vertShaderSource);
        validated = validated && helpers::checkShader(fragShader, fragShaderSource);

        m_sShader.program = glCreateProgram();
        glAttachShader(m_sShader.program, vertShader);
        glAttachShader(m_sShader.program, fragShader);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        glLinkProgram(m_sShader.program);
        validated = helpers::checkProgram(m_sShader.program);
    }

    if (validated)
    {
        m_sShader.uniforms.mvp.modelview = m_sShader.getUniformLocation("modelview");
        m_sShader.uniforms.mvp.projection = m_sShader.getUniformLocation("projection");
    }

    glViewport(0, 0, m_sCreationParams.width, m_sCreationParams.height);

    m_sMvp.projection = glm::perspective(45.0, double(m_sCreationParams.width /
            m_sCreationParams.height), 0.1, 750.0);
    m_sMvp.model = glm::mat4(1.0);
    m_sMvp.view = glm::lookAt( glm::vec3(0.0, 0.0, 3.0),
            glm::vec3(0.0, 0.0, -5.0),
            glm::vec3(0.0, 1.0, 0.0));

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glFrontFace(GL_CCW);
}

void CSecondLife::destroy()
{
}

void CSecondLife::update()
{
    m_sTimer.previous = m_sTimer.current;
    m_sTimer.current = m_sTimer.getUpdatedTime();
    m_sTimer.delta = m_sTimer.getDeltaTime();

    glm::mat4 view = glm::lookAt(m_sCamera.pos, (m_sCamera.pos + m_sCamera.eye), m_sCamera.up);

    if (m_psSystem->getEventHandler()->getSpectatorKey(CEventHandler::ESpecKey::E_SK_UP))
    {
        m_sCamera.pos.x += m_sCamera.eye.x * 3.1415 * m_sTimer.delta;
        m_sCamera.pos.z += m_sCamera.eye.z * 3.1415 * m_sTimer.delta;
        m_sCamera.pos.y += m_sCamera.eye.y * 3.1415 * m_sTimer.delta;
    }
    else if (m_psSystem->getEventHandler()->getSpectatorKey(CEventHandler::ESpecKey::E_SK_DN))
    {
        m_sCamera.pos.x -= m_sCamera.eye.x * 3.1415 * m_sTimer.delta;
        m_sCamera.pos.z -= m_sCamera.eye.z * 3.1415 * m_sTimer.delta;
        m_sCamera.pos.y -= m_sCamera.eye.y * 3.1415 * m_sTimer.delta;
    }
    else if (m_psSystem->getEventHandler()->getSpectatorKey(CEventHandler::ESpecKey::E_SK_LT))
    {
        m_sCamera.angle -= 3.1415 * m_sTimer.delta;
        m_sCamera.eye.x = sin(m_sCamera.angle);
        m_sCamera.eye.z = -cos(m_sCamera.angle);
    }
    else if (m_psSystem->getEventHandler()->getSpectatorKey(CEventHandler::ESpecKey::E_SK_RT))
    {
        m_sCamera.angle += 3.1415 * m_sTimer.delta;
        m_sCamera.eye.x = sin(m_sCamera.angle);
        m_sCamera.eye.z = -cos(m_sCamera.angle);
    }

    if (m_psSystem->getEventHandler()->getSpectatorKey(CEventHandler::ESpecKey::E_SK_PGUP))
    {
        m_sCamera.look += 3.1415 * m_sTimer.delta;
        m_sCamera.eye.y = sin(m_sCamera.look);
    }
    else if (m_psSystem->getEventHandler()->getSpectatorKey(CEventHandler::ESpecKey::E_SK_PGDN))
    {
        m_sCamera.look -= 3.1415 * m_sTimer.delta;
        m_sCamera.eye.y = sin(m_sCamera.look);
    }

    m_sCurrentMatrix = m_sMvp.getModelView(view);

    glClearColor(0.0, 0.7, 0.7, 1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_sShader.program);
    push();

    pop();
    glUseProgram(0);
}

void CSecondLife::push()
{
    m_vStack.push(m_sCurrentMatrix);
}

void CSecondLife::pop()
{
    m_sCurrentMatrix = m_vStack.top();
    m_vStack.pop();
}

