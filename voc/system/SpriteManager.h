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

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "../Commons.h"
#include "../utils/Helpers.h"

class CSpriteManager
{
public:
    explicit CSpriteManager();
    ~CSpriteManager();

    void init();
    void destroy();

    void addToSpriteBank(char const *file);
    void removeFromSpriteBank(char const *name);

    void renderSprite(char const *name);

private:
    struct SSpriteBank
    {
        std::string name;
        std::string path;

        unsigned int priority;

        struct SSprite
        {
            std::string name;

            struct SSpriteFrame
            {
                unsigned int id;

                glm::vec2 UL;
                glm::vec2 LR;

                glm::vec2 dimension;
            };

            std::vector<SSpriteFrame> frames;
        };

        std::vector<SSprite> sprites;
    };
    
    std::vector<SSpriteBank> m_vSpriteBank;
};

#endif /* end of include guard: SPRITEMANAGER_H */

