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


#ifndef _HELPERS_H_
#define _HELPERS_H_

#include "../Commons.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace helpers
{
    namespace semantic
    {
        namespace buffer
        {
            enum type
            {
                STATIC = 0,
                DYNAMIC = 1
            };
        }

        namespace uniform
        {
            enum type
            {
                MATERIAL = 0,
                TRANSFORM0 = 1,
                TRANSFORM1 = 2,
                INDIRECTION = 3
            };
        }

        namespace sampler
        {
            enum type
            {
                DIFFUSE = 0,
                POSITION = 4,
                TEXCOORD = 5,
                COLOR = 6
            };
        }

        namespace image
        {
            enum type
            {
                DIFFUSE = 0,
                PICKING = 1
            };
        }

        namespace attr
        {
            enum type
            {
                POSITION = 0,
                COLOR = 3,
                TEXCOORD = 4,
                DRAW_ID = 5
            };
        }

        namespace vert
        {
            enum type
            {
                POSITION = 0,
                COLOR = 3,
                TEXCOORD = 4,
                INSTANCE = 7
            };
        }

        namespace frag
        {
            enum type
            {
                COLOR = 0,
                RED = 0,
                GREEN = 1,
                BLUE = 2,
                ALPHA = 0
            };
        }

        namespace renderbuffer
        {
            enum type
            {
                DEPTH,
                COLOR0
            };
        }
    }

    std::string loadFile(std::string const &file);
    GLuint createShader(GLenum type, std::string const &source);
    bool checkShader(GLuint shader, std::string const &file);
    bool checkProgram(GLuint program);
    bool checkExtension(char const *ext);
    bool checkGLVersion();
    bool validateProgram(GLuint program);

    std::map<std::string, GLint> getActiveAttributes(GLuint program);
    std::map<std::string, GLint> getActiveUniforms(GLuint program);
}

#endif /* end of include guard: _HELPERS_H_ */


