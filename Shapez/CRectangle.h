//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CRECTANGLE_H
#define OOP_4_CRECTANGLE_H

#include <utility>
#include "../Interfaces/ISolidShape.h"
#include "CPoint.h"

class CRectangle : public ISolidShape {
public:
    CRectangle(const CPoint& topLeft,
               float width,
               float height,
               Color strokeColor,
               Color fillColor):
               topLeft(topLeft),
               width(width),
               height(height),
               strokeColor(strokeColor),
               fillColor(fillColor) {}

    [[nodiscard]] float GetArea() const override { return width * height; }
    [[nodiscard]] float GetPerimeter() const override { return 2 * (width + height); }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Rectangle: (" << topLeft.getX() << ", " << topLeft.getY() << "), width=" << width << ", height=" << height;
        ss << ISolidShape::ToString();
        return ss.str();
    }

    [[nodiscard]] Color GetStrokeColor() const override { return strokeColor; }
    [[nodiscard]] Color GetFillColor() const override { return fillColor; }

    void Draw(ICanvas* canvas) const override
    {
        canvas->FillPolygon({topLeft,
                             {topLeft.getX(), topLeft.getY() + height},
                             {topLeft.getX() + width, topLeft.getY() + height},
                             {topLeft.getX() + width, topLeft.getY()}}, fillColor);

        canvas->DrawLine(topLeft, {topLeft.getX(), topLeft.getY() + height}, strokeColor);
        canvas->DrawLine({topLeft.getX(), topLeft.getY() + height}, {topLeft.getX() + width, topLeft.getY() + height}, strokeColor);
        canvas->DrawLine({topLeft.getX() + width, topLeft.getY() + height}, {topLeft.getX() + width, topLeft.getY()}, strokeColor);
        canvas->DrawLine({topLeft.getX() + width, topLeft.getY()}, topLeft, strokeColor);
    }

private:
    CPoint topLeft;
    float width, height;
    Color strokeColor, fillColor;
};

#endif //OOP_4_CRECTANGLE_H
