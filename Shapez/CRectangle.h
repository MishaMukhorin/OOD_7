//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CRECTANGLE_H
#define OOP_4_CRECTANGLE_H

#include <utility>
#include "../Interfaces/ISolidShape.h"
#include "../Interfaces/IStyle.h"
#include "CPoint.h"
#include "FillStyle.h"
#include "LineStyle.h"

class CRectangle : public ISolidShape {
public:
    CRectangle(const CPoint& topLeft, float width, float height,
               std::shared_ptr<IStyle> strokeStyle,
               std::shared_ptr<IStyle> fillStyle)
            : topLeft(topLeft), width(width), height(height),
              strokeStyle(std::move(strokeStyle)), fillStyle(std::move(fillStyle)) {}

    [[nodiscard]] float GetArea() const override { return width * height; }
    [[nodiscard]] float GetPerimeter() const override { return 2 * (width + height); }

    void AddShape(const std::shared_ptr<IShape>& shape) override {};

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeColor() const override {
        return strokeStyle;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillColor() const override {
        return fillStyle;
    }

    void Draw(ICanvas* canvas) const override {
        canvas->FillPolygon({topLeft,
                             {topLeft.getX(), topLeft.getY() + height},
                             {topLeft.getX() + width, topLeft.getY() + height},
                             {topLeft.getX() + width, topLeft.getY()}},
                            fillStyle->GetColor().value_or(Color("0")));

        canvas->DrawLine(topLeft, {topLeft.getX(), topLeft.getY() + height},
                         strokeStyle->GetColor().value_or(Color("0")),
                         strokeStyle->GetLineWidth().value_or(2));
        canvas->DrawLine({topLeft.getX(), topLeft.getY() + height}, {topLeft.getX() + width, topLeft.getY() + height},
                         strokeStyle->GetColor().value_or(Color("0")),
                         strokeStyle->GetLineWidth().value_or(2));
        canvas->DrawLine({topLeft.getX() + width, topLeft.getY() + height}, {topLeft.getX() + width, topLeft.getY()},
                         strokeStyle->GetColor().value_or(Color("0")),
                         strokeStyle->GetLineWidth().value_or(2));
        canvas->DrawLine({topLeft.getX() + width, topLeft.getY()}, topLeft,
                         strokeStyle->GetColor().value_or(Color("0")),
                         strokeStyle->GetLineWidth().value_or(2));
    }

private:
    CPoint topLeft;
    float width, height;
    std::shared_ptr<IStyle> strokeStyle;
    std::shared_ptr<IStyle> fillStyle;
};

#endif //OOP_4_CRECTANGLE_H
