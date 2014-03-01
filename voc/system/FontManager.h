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

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "../Commons.h"
#include "../utils/Helpers.h"

class CFontManager
{
public:
    explicit CFontManager();
    ~CFontManager();

    void init();
    void destroy();

    void load(char const *name, char const *file);
    void write(char const *text, glm::vec2 pos);

    void setPixelSize(int size);
    void setFontType(char const *name);

    int getPixelSize() const { return m_sFont.size; }

private:
    enum
    {
        VERTEX,
        ELEMENT,

        MAX
    };

    std::vector<GLuint> m_vBuffer;
    std::vector<size_t> m_vSize;

    struct 
    {
        FT_Library library;
        FT_Face face;

        int size;
        std::map<std::string, FT_Face> mface;
    } m_sFont;
};

#endif /* end of include guard: FONTMANAGER_H */
