//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CTRIANGLE_H
#define OOP_4_CTRIANGLE_H

#include <ostream>
#include <utility>
#include "CPoint.h"
#include "CLineSegment.h"
#include "../Interfaces/ISolidShape.h"
#include <memory>

class CTriangle : public ISolidShape
{
public:
    CTriangle(const CPoint& p1,
              const CPoint& p2,
              const CPoint& p3,
              std::shared_ptr<IStyle> strokeStyle,
              std::shared_ptr<IStyle> fillStyle)
            : p1(p1),
              p2(p2),
              p3(p3),
              m_strokeStyle(std::move(strokeStyle)),
              m_fillStyle(std::move(fillStyle)) {}

    [[nodiscard]] float GetArea() const override
    {
        float a = CLineSegment::GetLineLength(p1, p2);
        float b = CLineSegment::GetLineLength(p2, p3);
        float c = CLineSegment::GetLineLength(p3, p1);
        float p = (a + b + c) / 2;
        return float(std::sqrt(p * (p - a) * (p - b) * (p - c)));
    }

    [[nodiscard]] float GetPerimeter() const override
    {
        return CLineSegment::GetLineLength(p1, p2) +
               CLineSegment::GetLineLength(p2, p3) +
               CLineSegment::GetLineLength(p3, p1);
    }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Triangle: (" << p1.getX() << ", " << p1.getY() << "), (" << p2.getX() << ", " << p2.getY() << "), (" << p3.getX() << ", " << p3.getY() << ")";
        ss << ISolidShape::ToString();
        return ss.str();
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeColor() const override
    {
        return m_strokeStyle ;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillColor() const override
    {
        return m_fillStyle ;
    }

    void Draw(ICanvas* canvas) const override
    {
        // Fill the triangle with the fill color if enabled
        if (m_fillStyle)
        {
            Color fillColor = m_fillStyle->GetColor().value_or(Color("0"));
            canvas->FillPolygon({p1, p2, p3}, fillColor);
        }

        // Draw each line of the triangle with the stroke color if enabled
        if (m_strokeStyle)
        {
            Color strokeColor = m_strokeStyle->GetColor().value_or(Color("0"));
            float strokeWidth = m_strokeStyle->GetLineWidth().value_or(2);
            canvas->DrawLine(p1, p2, strokeColor, strokeWidth);
            canvas->DrawLine(p2, p3, strokeColor, strokeWidth);
            canvas->DrawLine(p3, p1, strokeColor, strokeWidth);
        }
    }

    void AddShape(const std::shared_ptr<IShape>& shape) override {};

private:
    CPoint p1, p2, p3;
    std::shared_ptr<IStyle> m_strokeStyle; // Using shared pointer to IStyle for stroke style
    std::shared_ptr<IStyle> m_fillStyle;   // Using shared pointer to IStyle for fill style
};


#endif //OOP_4_CTRIANGLE_H
