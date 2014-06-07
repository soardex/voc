/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Fitz Abucay, 2014
 */

#include "SpriteManager.h"

CSpriteManager::CSpriteManager()
    : m_nSpriteCount(0),
    m_nSpriteBankCount(0),
    m_vBuffer(MAX),
    m_vSize(MAX),
    m_psTexture(nullptr)
{
}

CSpriteManager::~CSpriteManager()
{
}

void CSpriteManager::init()
{
    m_psTexture = new CTextureManager();

    glGenBuffers(MAX, &m_vBuffer[0]);
}

void CSpriteManager::destroy()
{
    glDeleteBuffers(MAX, &m_vBuffer[0]);

    if (m_psTexture)
    {
        delete m_psTexture;
        m_psTexture = nullptr;
    }
}

void CSpriteManager::addToSpriteBank(char const *file)
{
    if (file != NULL)
    {
        pugi::xml_document doc;
        if (!doc.load_file(file))
            fprintf(stderr, "[ERR] Sprite Manager Error: Unable to load the file.");

        pugi::xml_node root = doc.child("texture");
        
        SSpriteBank bank;
        pugi::xml_attribute_iterator attr = root.attributes_begin();
        for (; attr != root.attributes_end(); ++attr)
        {
            if (std::string("name").compare(attr->name()) == 0)
            {
                bank.name = attr->value();
            }

            if (std::string("path").compare(attr->name()) == 0)
            {
                bank.path = attr->value();
            }

            if (std::string("type").compare(attr->name()) == 0)
            {
                bank.type = attr->as_int();
            }
        }

        pugi::xml_node_iterator child = root.begin();
        for (; child != root.end(); ++child)
        {
            if (std::string("sprite").compare(child->name()) == 0)
            {
                SSprite sprite;
                pugi::xml_attribute_iterator attr = child->attributes_begin();
                for (; attr != child->attributes_end(); ++attr)
                {
                    if (std::string("name").compare(attr->name()) == 0)
                    {
                        sprite.name = attr->value();
                    }
                }

                pugi::xml_node_iterator it = child->begin();
                for (; it != child->end(); ++it)
                {
                    if (std::string("frame").compare(it->name()) == 0)
                    {
                        SSpriteFrame frame;
                        pugi::xml_attribute_iterator at = it->attributes_begin();
                        for (; at != it->attributes_end(); ++at)
                        {
                            if (std::string("id").compare(at->name()) == 0)
                            {
                                frame.id = at->as_int();
                            }

                            if (std::string("x1").compare(at->name()) == 0)
                            {
                                frame.UL.x = at->as_float();
                            }

                            if (std::string("y1").compare(at->name()) == 0)
                            {
                                frame.UL.y = at->as_float();
                            }

                            if (std::string("x2").compare(at->name()) == 0)
                            {
                                frame.LR.x = at->as_float();
                            }

                            if (std::string("y2").compare(at->name()) == 0)
                            {
                                frame.LR.y = at->as_float();
                            }
                        }

                        frame.populateDimension();
                        sprite.frames.push_back(frame);
                    }
                }

                m_mSpriteMapToBank[sprite.name] = m_nSpriteBankCount;
                bank.sprites.push_back(sprite);
                m_nSpriteCount++;
            }
        }

        GLenum type = GL_RGB;
        if (bank.type == 2)
        {
            type = GL_RGBA;
        }

        m_psTexture->load(bank.path.c_str(), m_nSpriteBankCount, type);
        m_vSpriteBank.push_back(bank);
        m_nSpriteBankCount++;
    }
}

void CSpriteManager::renderSprite(char const *name, glm::vec2 pos)
{
    if (name != NULL)
    {
        if (m_mSpriteMapToBank.find(name) != m_mSpriteMapToBank.end())
        {
            unsigned int id = m_mSpriteMapToBank[name];
            SSpriteBank const &bank = m_vSpriteBank[id];

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBlendColor(1.0, 1.0, 1.0, 1.0);
            
            m_psTexture->bindTexture(id);

            SSpriteFrame const *frame = &bank.sprites[0].frames[0];
            float w = frame->dimension.x;
            float h = frame->dimension.y;

            float s = m_psTexture->getImageProperties(id).width;
            float t = m_psTexture->getImageProperties(id).height;

            glm::vec2 UL(frame->UL.x / s, (t - frame->UL.y) / t);
            glm::vec2 LR(frame->LR.x / s, (t - frame->LR.y) / t);

            helpers::SVertv2v2 vertexData[4] = 
            {
                helpers::SVertv2v2(glm::vec2(pos.x, pos.y), glm::vec2(UL.x, UL.y)),
                helpers::SVertv2v2(glm::vec2(pos.x, pos.y + h), glm::vec2(UL.x, LR.y)),
                helpers::SVertv2v2(glm::vec2(pos.x + w, pos.y + h), glm::vec2(LR.x, LR.y)),
                helpers::SVertv2v2(glm::vec2(pos.x + w, pos.y), glm::vec2(LR.x, UL.y))
            };

            GLsizei const vertexCount = 4;
            GLsizeiptr const vertexSize = vertexCount * sizeof(helpers::SVertv2v2);

            GLsizei const elementCount = 4;
            GLsizeiptr const elementSize = elementCount * sizeof(glm::uint32);
            glm::uint32 elementData[] = { 0, 1, 2, 3 };

            glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer[VERTEX]);
            if (vertexSize != m_vSize[VERTEX])
            {
                glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexData, GL_DYNAMIC_DRAW);
                m_vSize[VERTEX] = vertexSize;
            }
            else
                glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize, vertexData);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vBuffer[ELEMENT]);
            if (elementSize != m_vSize[ELEMENT])
            {
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, elementData, GL_DYNAMIC_DRAW);
                m_vSize[ELEMENT] = elementSize;
            }
            else
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementSize, elementData);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer[VERTEX]);
            glVertexAttribPointer(helpers::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(helpers::SVertv2v2), BUFFER_OFFSET(0));
            glVertexAttribPointer(helpers::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(helpers::SVertv2v2), BUFFER_OFFSET(sizeof(glm::vec2)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vBuffer[ELEMENT]);
            glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
            glEnableVertexAttribArray(helpers::semantic::attr::TEXCOORD);
                glDrawElements(GL_TRIANGLE_FAN, elementCount, GL_UNSIGNED_INT, 0);
            glDisableVertexAttribArray(helpers::semantic::attr::POSITION);
            glDisableVertexAttribArray(helpers::semantic::attr::TEXCOORD);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
            glDisable(GL_BLEND);
        }
    }
}

void CSpriteManager::renderSprite(char const *name, unsigned int index, glm::vec2 pos)
{
    if (name != NULL)
    {
        if (m_mSpriteMapToBank.find(name) != m_mSpriteMapToBank.end())
        {
            unsigned int id = m_mSpriteMapToBank[name];
            SSpriteBank const &bank = m_vSpriteBank[id];

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBlendColor(1.0, 1.0, 1.0, 1.0);
            
            m_psTexture->bindTexture(id);

            SSpriteFrame const *frame = &bank.sprites[0].frames[index];
            float w = frame->dimension.x;
            float h = frame->dimension.y;

            float s = m_psTexture->getImageProperties(id).width;
            float t = m_psTexture->getImageProperties(id).height;

            glm::vec2 UL(frame->UL.x / s, (t - frame->UL.y) / t);
            glm::vec2 LR(frame->LR.x / s, (t - frame->LR.y) / t);

            helpers::SVertv2v2 vertexData[4] = 
            {
                helpers::SVertv2v2(glm::vec2(pos.x, pos.y), glm::vec2(UL.x, UL.y)),
                helpers::SVertv2v2(glm::vec2(pos.x, pos.y + h), glm::vec2(UL.x, LR.y)),
                helpers::SVertv2v2(glm::vec2(pos.x + w, pos.y + h), glm::vec2(LR.x, LR.y)),
                helpers::SVertv2v2(glm::vec2(pos.x + w, pos.y), glm::vec2(LR.x, UL.y))
            };

            GLsizei const vertexCount = 4;
            GLsizeiptr const vertexSize = vertexCount * sizeof(helpers::SVertv2v2);

            GLsizei const elementCount = 4;
            GLsizeiptr const elementSize = elementCount * sizeof(glm::uint32);
            glm::uint32 elementData[] = { 0, 1, 2, 3 };

            glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer[VERTEX]);
            if (vertexSize != m_vSize[VERTEX])
            {
                glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexData, GL_DYNAMIC_DRAW);
                m_vSize[VERTEX] = vertexSize;
            }
            else
                glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize, vertexData);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vBuffer[ELEMENT]);
            if (elementSize != m_vSize[ELEMENT])
            {
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, elementData, GL_DYNAMIC_DRAW);
                m_vSize[ELEMENT] = elementSize;
            }
            else
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementSize, elementData);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer[VERTEX]);
            glVertexAttribPointer(helpers::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(helpers::SVertv2v2), BUFFER_OFFSET(0));
            glVertexAttribPointer(helpers::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(helpers::SVertv2v2), BUFFER_OFFSET(sizeof(glm::vec2)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vBuffer[ELEMENT]);
            glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
            glEnableVertexAttribArray(helpers::semantic::attr::TEXCOORD);
                glDrawElements(GL_TRIANGLE_FAN, elementCount, GL_UNSIGNED_INT, 0);
            glDisableVertexAttribArray(helpers::semantic::attr::POSITION);
            glDisableVertexAttribArray(helpers::semantic::attr::TEXCOORD);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
            glDisable(GL_BLEND);
        }
    }
}
