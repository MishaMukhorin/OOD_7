//
// Created by Misha on 11.04.2024.
//

#ifndef OOP_4_CCOLOR_H
#define OOP_4_CCOLOR_H

#include <string>
#include <sstream>
#include <iomanip>

class Color
{
public:
    explicit Color(const std::string& hexString)
    {
        if (hexString.empty())
        {
            m_rgba = 0;
            return;
        }
        std::stringstream ss;
        ss << std::hex << hexString;
        ss >> m_rgba;
    }

    explicit Color(unsigned int color): m_rgba(color) {}

    [[nodiscard]] std::string ToString() const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(8) << std::setfill('0') << m_rgba;
        return ss.str();
    }

    [[nodiscard]] unsigned int GetInt() const
    {
        return m_rgba;
    }

private:
    unsigned int m_rgba;
};


#endif //OOP_4_CCOLOR_H
