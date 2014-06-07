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

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "../Commons.h"
#include "../utils/Helpers.h"

#include "TextureManager.h"

class CSpriteManager
{
public:
    explicit CSpriteManager();
    ~CSpriteManager();

    void init();
    void destroy();

    void addToSpriteBank(char const *file);

    void renderSprite(char const *name, glm::vec2 pos);
    void renderSprite(char const *name, unsigned int index, glm::vec2 pos);

private:
    struct SSpriteFrame
    {
        unsigned int id;

        glm::vec2 UL;
        glm::vec2 LR;

        glm::vec2 dimension;
        void populateDimension() { dimension = glm::vec2(LR - UL); }
    };

    struct SSprite
    {
        std::string name;
        std::vector<SSpriteFrame> frames;
    };

    struct SSpriteBank
    {
        std::string name;
        std::string path;

        unsigned int priority;
        unsigned int type;

        std::vector<SSprite> sprites;
    };
    
    std::vector<SSpriteBank> m_vSpriteBank;
    std::map<std::string, unsigned int> m_mSpriteMapToBank;

    unsigned int m_nSpriteCount;
    unsigned int m_nSpriteBankCount;

    enum
    {
        VERTEX,
        ELEMENT,

        MAX
    };

    std::vector<GLuint> m_vBuffer;
    std::vector<size_t> m_vSize;

    CTextureManager *m_psTexture;
};

#endif /* end of include guard: SPRITEMANAGER_H */
