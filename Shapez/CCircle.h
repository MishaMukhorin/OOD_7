//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CCIRCLE_H
#define OOP_4_CCIRCLE_H

#include <cmath>
#include <utility>
#include "../Interfaces/ISolidShape.h"
#include "CPoint.h"

class CCircle : public ISolidShape {
public:

    CCircle(const CPoint& center,
            float radius,
            Color strokeColor,
            Color fillColor):
            m_center({center.getX() - radius, center.getY() - radius}),
            m_radius(radius),
            m_strokeColor(strokeColor),
            m_fillColor(fillColor) {}

    [[nodiscard]] float GetArea() const override { return M_PI * m_radius * m_radius; }
    [[nodiscard]] float GetPerimeter() const override { return 2.0 * M_PI * m_radius; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Circle: (" << m_center.getX() << ", " << m_center.getY() << "), radius=" << m_radius << std::endl;
        ss << ISolidShape::ToString();
        return ss.str();
    }

    [[nodiscard]] Color GetStrokeColor() const override { return m_strokeColor; }
    [[nodiscard]] Color GetFillColor() const override { return m_fillColor; }

    void Draw(ICanvas* canvas) const override
    {
        canvas->DrawCircle(m_center, m_radius, m_strokeColor);
        canvas->FillCircle(m_center, m_radius, m_fillColor);
    }

private:
    CPoint m_center;
    float m_radius;
    Color m_strokeColor, m_fillColor;
};

#endif //OOP_4_CCIRCLE_H
