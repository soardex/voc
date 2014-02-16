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

#include "imported/tinyobjloader/tiny_obj_loader.h"

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

        glBindAttribLocation(m_sShader.program, helpers::semantic::attr::POSITION, "position");
        glBindAttribLocation(m_sShader.program, helpers::semantic::attr::TEXCOORD, "texcoord");

        glLinkProgram(m_sShader.program);
        validated = helpers::checkProgram(m_sShader.program);
    }

    if (validated)
    {
        m_sShader.uniforms = helpers::getActiveUniforms(m_sShader.program);
    }

    //! populate grid object
    {
        SMeshNode meshNode;
        SMesh mesh;
        std::vector<SMesh> holder;

        GLsizei elementCount;
        GLsizeiptr elementSize;
        std::vector<glm::uint32> elementData;

        GLsizei vertexCount;
        GLsizeiptr vertexSize;
        std::vector<glm::vec3> vertexData;

        float extent = 30.0, step = 1.0, h = -0.6;
        for (int line = -extent; line <= extent; line += step)
        {
            vertexData.push_back(glm::vec3(line, h, extent));
            vertexData.push_back(glm::vec3(line, h, -extent));

            vertexData.push_back(glm::vec3(extent, h, line));
            vertexData.push_back(glm::vec3(-extent, h, line));
        }

        vertexCount = vertexData.size();
        vertexSize = vertexCount * sizeof(glm::vec3);

        elementCount = vertexCount;
        elementSize = elementCount * sizeof(glm::uint32);
        for (int i = 0; i < elementCount; i++)
            elementData.push_back(i);

        mesh.count = elementCount;

        glGenVertexArrays(1, &mesh.vao);

        glGenBuffers(SMesh::MAX, &mesh.buffers[0]);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.buffers[SMesh::VERTEX]);
        glBufferData(GL_ARRAY_BUFFER, vertexSize, &vertexData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.buffers[SMesh::ELEMENT]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, &elementData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(mesh.vao);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.buffers[SMesh::VERTEX]);
            glVertexAttribPointer(helpers::semantic::attr::POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.buffers[SMesh::ELEMENT]);
            glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
        glBindVertexArray(0);

        mesh.type = GL_LINES;
        holder.push_back(mesh);

        meshNode.name = "grid";
        meshNode.mesh = holder;
        meshNode.visible = true;
        m_vMesh.push_back(meshNode);
    }

    //loadWaveObjFile("./build/assets/models/cube.obj", "./build/assets/models/", true);

    glViewport(0, 0, m_sCreationParams.width, m_sCreationParams.height);

    m_sMvp.constant.perspective = glm::perspective(45.0,
            double(m_sCreationParams.width / m_sCreationParams.height),
            0.1, 750.0);
    m_sMvp.constant.orthographic = glm::ortho(0, m_sCreationParams.width,
            m_sCreationParams.height, 0);

    m_sMvp.setProjection(SModelViewProjection::PERSPECTIVE);
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

    glUseProgram(m_sShader.program);
    glUniformMatrix4fv(m_sShader.uniforms["modelview"], 1, GL_FALSE, &m_sMvp.getModelView()[0][0]);
    glUniformMatrix4fv(m_sShader.uniforms["projection"], 1, GL_FALSE, &m_sMvp.projection[0][0]);
    glUseProgram(0);
}

void CSecondLife::destroy()
{
    std::vector<SMeshNode>::iterator it = m_vMesh.begin();
    for (; it != m_vMesh.end(); it++)
    {
        std::vector<SMesh>::iterator n = it->mesh.begin();
        for (; n != it->mesh.end(); n++)
        {
            glDeleteBuffers(SMesh::MAX, &n->buffers[0]);
            glDeleteVertexArrays(1, &n->vao);
        }

        it->mesh.clear();
    }

    m_vMesh.clear();
    glDeleteProgram(m_sShader.program);
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

    glUseProgram(m_sShader.program);
    glUniformMatrix4fv(m_sShader.uniforms["modelview"], 1, GL_FALSE, &m_sMvp.getModelView(view)[0][0]);
    glUniformMatrix4fv(m_sShader.uniforms["projection"], 1, GL_FALSE, &m_sMvp.projection[0][0]);
    glUseProgram(0);

    m_sCurrentMatrix = m_sMvp.getModelView(view);

    glClearColor(0.0, 0.7, 0.7, 1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_sShader.program);
    push();
        //! recursive rendering
        std::vector<SMeshNode>::iterator it = m_vMesh.begin();
        for (; it != m_vMesh.end(); it++)
        {
            if (it->visible)
            {
                std::vector<SMesh>::iterator n = it->mesh.begin();
                for (; n != it->mesh.end(); n++)
                {
                    glBindVertexArray(n->vao);
                        glDrawElements(n->type, n->count, GL_UNSIGNED_INT, 0);
                    glBindVertexArray(0);
                }
            }
        }
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

void CSecondLife::loadWaveObjFile(char const *file, char const *path, bool visible)
{
    std::vector<tinyobj::shape_t> shapes;
    std::string err = tinyobj::LoadObj(shapes, file, path);

    if (!err.empty())
        fprintf(stderr, "[ERR] Scene Error: Unable to load obj file.");

    SMeshNode meshNode;
    std::vector<SMesh> holder;
    for (int i = 0; i < shapes.size(); i++)
    {
        SMesh mesh;

        GLsizei elementCount;
        GLsizeiptr elementSize;
        std::vector<glm::uint32> elementData;

        GLsizei vertexCount;
        GLsizeiptr vertexSize;
        std::vector<glm::vec3> vertexData;

        assert((shapes[i].mesh.positions.size() % 3) == 0);
        for (int v = 0; v < shapes[i].mesh.positions.size() / 3; v++)
        {
            vertexData.push_back(glm::vec3(
                shapes[i].mesh.positions[3 * v + 0],
                shapes[i].mesh.positions[3 * v + 1],
                shapes[i].mesh.positions[3 * v + 2]));
        }

        vertexCount = vertexData.size();
        vertexSize = vertexCount * sizeof(glm::vec3);

        for (int f = 0; f < shapes[i].mesh.indices.size(); f++)
            elementData.push_back(shapes[i].mesh.indices[f]);

        elementCount = elementData.size();
        elementSize = elementCount * sizeof(glm::uint32);
        mesh.count = elementCount;

        glGenVertexArrays(1, &mesh.vao);

        glGenBuffers(SMesh::MAX, &mesh.buffers[0]);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.buffers[SMesh::VERTEX]);
        glBufferData(GL_ARRAY_BUFFER, vertexSize, &vertexData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.buffers[SMesh::ELEMENT]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, &elementData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(mesh.vao);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.buffers[SMesh::VERTEX]);
            glVertexAttribPointer(helpers::semantic::attr::POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.buffers[SMesh::ELEMENT]);
            glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
        glBindVertexArray(0);

        mesh.type = GL_TRIANGLES;
        holder.push_back(mesh);
    }

    meshNode.name = file;
    meshNode.mesh = holder;
    meshNode.visible = visible;
    m_vMesh.push_back(meshNode);
}

