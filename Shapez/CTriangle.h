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

class CTriangle : public ISolidShape
{
public:
    CTriangle(const CPoint& p1,
              const CPoint& p2,
              const CPoint& p3,
              Color strokeColor,
              Color fillColor) :
              p1(p1),
              p2(p2),
              p3(p3),
              strokeColor(strokeColor),
              fillColor(fillColor) {}
// done с большой
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
        return CLineSegment::GetLineLength(p1, p2) + CLineSegment::GetLineLength(p2, p3) + CLineSegment::GetLineLength(p3, p1);
    }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Triangle: (" << p1.getX() << ", " << p1.getY() << "), (" << p2.getX() << ", " << p2.getY() << "), (" << p3.getX() << ", " << p3.getY() << ")";
        ss << ISolidShape::ToString();
        return ss.str();
    }

    [[nodiscard]] Color GetStrokeColor() const override { return strokeColor; }
    [[nodiscard]] Color GetFillColor() const override { return fillColor; }

    void Draw(ICanvas* canvas) const override
    {
        canvas->FillPolygon({p1, p2, p3}, fillColor);

        canvas->DrawLine(p1, p2, strokeColor);
        canvas->DrawLine(p2, p3, strokeColor);
        canvas->DrawLine(p3, p1, strokeColor);

    }

private:
    CPoint p1, p2, p3;
    Color strokeColor, fillColor;

};

#endif //OOP_4_CTRIANGLE_H
