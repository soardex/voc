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

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "../Commons.h"

class CTextureManager
{
public:
    explicit CTextureManager();
    virtual ~CTextureManager();

    bool load(const char *filename, const unsigned int textureId,
            GLenum imageFormat = GL_RGB,
            GLint internalFormat = GL_RGB,
            GLint level = 0,
            GLint border = 0);

    bool unloadTexture(const unsigned int textureId);
    bool bindTexture(const unsigned int textureId);
    void unloadAllTextures();

protected:
    CTextureManager(const CTextureManager& tm);
    CTextureManager& operator=(const CTextureManager& tm);

    std::map<unsigned int, GLuint> m_mTextureId;
};

#endif /* end of include guard: TEXTUREMANAGER_H */

