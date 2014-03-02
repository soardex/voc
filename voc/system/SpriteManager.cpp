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

#include "SpriteManager.h"

CSpriteManager::CSpriteManager()
{
}

CSpriteManager::~CSpriteManager()
{
}

void CSpriteManager::init()
{
}

void CSpriteManager::destroy()
{
}

void CSpriteManager::addToSpriteBank(char const *file)
{
    if (file != NULL)
    {
        pugi::xml_document doc;
        if (!doc.load_file(file))
            fprintf(stderr, "[ERR] Sprite Manager Error: Unable to load the file.");

        pugi::xml_node root = doc.child("texture");
        
        pugi::xml_attribute_iterator attr = root.attributes_begin();
        for (; attr != root.attributes_end(); ++attr)
        {
            if (std::string("name").compare(attr->name()))
            {
            }

            if (std::string("path").compare(attr->name()))
            {
            }
        }

        pugi::xml_node_iterator child = root.begin();
        for (; child != root.end(); ++child)
        {
            if (std::string("sprite").compare(child->name()))
            {
                pugi::xml_attribute_iterator attr = child->attributes_begin();
                for (; attr != child->attributes_end(); ++attr)
                {
                    if (std::string("name").compare(attr->name()))
                    {
                    }
                }

                pugi::xml_node_iterator it = child->begin();
                for (; it != child->end(); ++it)
                {
                    if (std::string("frame").compare(it->name()))
                    {
                        pugi::xml_attribute_iterator at = it->attributes_begin();
                        for (; at != it->attributes_end(); ++at)
                        {
                            if (std::string("id").compare(at->name()))
                            {
                            }

                            if (std::string("x1").compare(at->name()))
                            {
                            }

                            if (std::string("y1").compare(at->name()))
                            {
                            }

                            if (std::string("x2").compare(at->name()))
                            {
                            }

                            if (std::string("y2").compare(at->name()))
                            {
                            }
                        }
                    }
                }
            }
        }
    }
}

void CSpriteManager::removeFromSpriteBank(char const *name)
{
    if (name != NULL)
    {
    }
}

void CSpriteManager::renderSprite(char const *name)
{
    if (name != NULL)
    {
        //GLuint texture;
        //glActiveTexture(GL_TEXTURE0);
        //glGenTextures(1, &texture);

        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendColor(1.0, 1.0, 1.0, 1.0);

        //glBindTexture(GL_TEXTURE_2D, texture);
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //FT_GlyphSlot glyph = m_sFont.face->glyph;

        //char const *p;
        //for (p = text; *p; p++)
        //{
        //    if (FT_Load_Char(m_sFont.face, *p, FT_LOAD_RENDER | FT_LOAD_NO_HINTING))
        //        continue;

        //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, glyph->bitmap.width,
        //            glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
        //            glyph->bitmap.buffer);

        //    int w = glyph->bitmap.width;
        //    int h = glyph->bitmap.rows;

        //    glm::vec2 lpos;
        //    lpos.x = pos.x + glyph->bitmap_left;
        //    lpos.y = (pos.y * -1.0) + glyph->bitmap_top;

        //    helpers::SVertv2v2 vertexData[4] = 
        //    {
        //        helpers::SVertv2v2(glm::vec2(lpos.x, lpos.y), glm::vec2(0, 0)),
        //        helpers::SVertv2v2(glm::vec2(lpos.x, lpos.y - h), glm::vec2(0, 1)),
        //        helpers::SVertv2v2(glm::vec2(lpos.x + w, lpos.y - h), glm::vec2(1, 1)),
        //        helpers::SVertv2v2(glm::vec2(lpos.x + w, lpos.y), glm::vec2(1, 0))
        //    };

        //    GLsizei const vertexCount = 4;
        //    GLsizeiptr const vertexSize = vertexCount * sizeof(helpers::SVertv2v2);

        //    GLsizei const elementCount = 4;
        //    GLsizeiptr const elementSize = elementCount * sizeof(glm::uint32);
        //    glm::uint32 elementData[] = { 0, 1, 2, 3 };

        //    glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer[VERTEX]);
        //    if (vertexSize != m_vSize[VERTEX])
        //    {
        //        glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexData, GL_DYNAMIC_DRAW);
        //        m_vSize[VERTEX] = vertexSize;
        //    }
        //    else
        //        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize, vertexData);

        //    glBindBuffer(GL_ARRAY_BUFFER, 0);

        //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vBuffer[ELEMENT]);
        //    if (elementSize != m_vSize[ELEMENT])
        //    {
        //        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, elementData, GL_DYNAMIC_DRAW);
        //        m_vSize[ELEMENT] = elementSize;
        //    }
        //    else
        //        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementSize, elementData);

        //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        //    glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer[VERTEX]);
        //    glVertexAttribPointer(helpers::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(helpers::SVertv2v2), BUFFER_OFFSET(0));
        //    glVertexAttribPointer(helpers::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(helpers::SVertv2v2), BUFFER_OFFSET(sizeof(glm::vec2)));
        //    glBindBuffer(GL_ARRAY_BUFFER, 0);

        //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vBuffer[ELEMENT]);
        //    glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
        //    glEnableVertexAttribArray(helpers::semantic::attr::TEXCOORD);
        //        glDrawElements(GL_TRIANGLE_FAN, elementCount, GL_UNSIGNED_INT, 0);
        //    glDisableVertexAttribArray(helpers::semantic::attr::POSITION);
        //    glDisableVertexAttribArray(helpers::semantic::attr::TEXCOORD);
        //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        //    pos.x += (glyph->advance.x >> 6);
        //    pos.y += (glyph->advance.y >> 6);
        //}

        //glDisable(GL_BLEND);
        //glDeleteTextures(1, &texture);
    }
}

