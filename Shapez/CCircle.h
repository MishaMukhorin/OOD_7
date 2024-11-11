//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CCIRCLE_H
#define OOP_4_CCIRCLE_H

#include <cmath>
#include <utility>
#include "../Interfaces/ISolidShape.h"
#include "CPoint.h"
#include "../Interfaces/IStyle.h"
#include <memory>

class CEllipse : public ISolidShape {
public:
    CEllipse(const CPoint& center,
             float radiusX,
             float radiusY,
             std::shared_ptr<IStyle> strokeStyle,
             std::shared_ptr<IStyle> fillStyle)
            : m_center(center),
              m_radiusX(radiusX),
              m_radiusY(radiusY),
              m_strokeStyle(std::move(strokeStyle)),
              m_fillStyle(std::move(fillStyle)) {}

    [[nodiscard]] float GetArea() const override {
        return M_PI * m_radiusX * m_radiusY;
    }

    void AddShape(const std::shared_ptr<IShape>& shape) override {};

    [[nodiscard]] float GetPerimeter() const override {
        // Approximation using Ramanujan's first formula for ellipse perimeter
        return M_PI * (3 * (m_radiusX + m_radiusY) - std::sqrt((3 * m_radiusX + m_radiusY) * (m_radiusX + 3 * m_radiusY)));
    }

    [[nodiscard]] std::string ToString() const override {
        std::stringstream ss;
        ss << "Ellipse: Center=(" << m_center.getX() << ", " << m_center.getY()
           << "), radiusX=" << m_radiusX << ", radiusY=" << m_radiusY << std::endl;
        ss << ISolidShape::ToString();
        return ss.str();
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeColor() const override {
        return m_strokeStyle;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillColor() const override {
        return m_fillStyle;
    }

    void Draw(ICanvas* canvas) const override {
        canvas->DrawEllipse(m_center, m_radiusX, m_radiusY,
                            m_strokeStyle->GetColor().value_or(Color("0")),
                            m_strokeStyle->GetLineWidth().value_or(2));

        canvas->FillEllipse(m_center, m_radiusX, m_radiusY, m_fillStyle->GetColor().value_or(Color("0")));
    }

private:
    CPoint m_center;
    float m_radiusX, m_radiusY;
    std::shared_ptr<IStyle> m_strokeStyle;
    std::shared_ptr<IStyle> m_fillStyle;
};

#endif //OOP_4_CCIRCLE_H
