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


#include "GeometryUtils.h"

CGeometryUtils::CGeometryUtils()
{
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

//GLsizei const elementCount = 6;
//GLsizeiptr const elementSize = elementCount * sizeof(glm::uint32);
//glm::uint32 const elementData[elementCount] =
//{
//    0, 1, 2,
//    0, 2, 3
//};
//
//GLsizei const vertexCount = 4;
//GLsizeiptr const vertexSize = vertexCount * sizeof(glm::vec2);
//glm::vec2 const vertexData[vertexCount] = 
//{
//    glm::vec2(-1.0f, -1.0f),
//    glm::vec2( 1.0f, -1.0f),
//    glm::vec2( 1.0f,  1.0f),
//    glm::vec2(-1.0f,  1.0f)
//};
}

CGeometryUtils::~CGeometryUtils()
{
}

