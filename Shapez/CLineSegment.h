//
// Created by Misha on 29.03.2024.
//
#pragma once

#ifndef OOP_4_CLINESEGMENT_H
#define OOP_4_CLINESEGMENT_H

#include <valarray>
#include <sstream>
#include <memory>
#include "CPoint.h"
#include "LineStyle.h"
#include "../Interfaces/IShape.h"


#include <memory>

class CLineSegment : public IShape {
public:
    CLineSegment(const CPoint& p1, const CPoint& p2, std::shared_ptr<IStyle> strokeStyle)
            : m_p1(p1), m_p2(p2), m_strokeStyle(std::move(strokeStyle)) {}

    void AddShape(const std::shared_ptr<IShape>& shape) override {};

    [[nodiscard]] float GetPerimeter() const override
    {
        return GetLineLength(m_p1, m_p2);
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeColor() const override
    {
        return m_strokeStyle;
    }
    [[nodiscard]] std::shared_ptr<IStyle> GetFillColor() const override
    {
        return nullptr;
    }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Line: (" << m_p1.getX() << ", " << m_p1.getY() << "), (" << m_p2.getX() << ", " << m_p2.getY() << ") " << std::endl;
        ss << IShape::ToString();
        return ss.str();
    }

    void Draw(ICanvas* canvas) const override
    {
        if (m_strokeStyle) {
            Color color = m_strokeStyle->GetColor().value_or(Color("0"));
            canvas->DrawLine(m_p1, m_p2, color,
                             m_strokeStyle->GetLineWidth().value_or(2));
        }
    }

    static float GetLineLength(CPoint p1, CPoint p2)
    {
        return std::sqrt(std::pow(p2.getX() - p1.getX(), 2) + std::pow(p2.getY() - p1.getY(), 2));
    }

private:
    CPoint m_p1, m_p2;
    std::shared_ptr<IStyle> m_strokeStyle;
};


#endif //OOP_4_CLINESEGMENT_H
