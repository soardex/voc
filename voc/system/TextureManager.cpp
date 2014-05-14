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
 * Copyright (C) Fitz Abucay, 2014
 */

#include "TextureManager.h"

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
    unloadAllTextures();
}

bool CTextureManager::load(const char *filename, const unsigned int textureId,
        GLenum imageFormat,
        GLint internalFormat,
        GLint level,
        GLint border)
{
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP *dib = 0;
    BYTE *bits = 0;

    unsigned int width = 0, height = 0;
    unsigned int glTextureId;

    fif = FreeImage_GetFileType(filename, 0);
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);

    if (fif == FIF_UNKNOWN)
        return false;

    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);

    if (!dib)
        return false;

    bits = FreeImage_GetBits(dib);
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);

    if ((bits == 0) || (width == 0) || (height == 0))
        return false;

    if (m_mTextureId.find(textureId) != m_mTextureId.end())
        glDeleteTextures(1, &(m_mTextureId[textureId]));

    glGenTextures(1, &glTextureId);
    m_mTextureId[textureId] = glTextureId;
    glBindTexture(GL_TEXTURE_2D, glTextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, level, internalFormat,
            width, height, border, imageFormat,
            GL_UNSIGNED_BYTE, bits);
    FreeImage_Unload(dib);
    return true;
}

bool CTextureManager::unloadTexture(const unsigned int textureId)
{
    bool result = true;

    if (m_mTextureId.find(textureId) != m_mTextureId.end())
    {
        glDeleteTextures(1, &(m_mTextureId[textureId]));
        m_mTextureId.erase(textureId);
    }
    else
        result = false;

    return result;
}

bool CTextureManager::bindTexture(const unsigned int textureId)
{
    bool result = true;

    if (m_mTextureId.find(textureId) != m_mTextureId.end())
        glBindTexture(GL_TEXTURE_2D, m_mTextureId[textureId]);
    else
        result = false;

    return result;
}

void CTextureManager::unloadAllTextures()
{
    std::map<unsigned int, GLuint>::iterator i = m_mTextureId.begin();

    for (; i != m_mTextureId.end(); i++)
        unloadTexture(i->first);

    m_mTextureId.clear();
}

