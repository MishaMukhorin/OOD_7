//
// Created by Misha on 29.03.2024.
//
#pragma once

#ifndef OOP_4_CLINESEGMENT_H
#define OOP_4_CLINESEGMENT_H

#include <valarray>
#include <sstream>
#include "CPoint.h"
#include "../Interfaces/IShape.h"



class CLineSegment: public IShape {
public:
    CLineSegment(const CPoint& p1, const CPoint& p2, Color strokeColor) : m_p1(p1), m_p2(p2), m_strokeColor(strokeColor) {}

    [[nodiscard]] float GetPerimeter() const override
    {
        return float(std::sqrt(std::pow(m_p2.getX() - m_p1.getX(), 2) + std::pow(m_p2.getY() - m_p1.getY(), 2)));
    }

    [[nodiscard]] Color GetStrokeColor() const override { return m_strokeColor; }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Line: (" << m_p1.getX() << ", " << m_p1.getY() << "), (" << m_p1.getX() << ", " << m_p1.getY() << ") " << std::endl;
        ss << IShape::ToString();
        return ss.str();
    }

    void Draw(ICanvas* canvas) const override
    {
        canvas->DrawLine(m_p1, m_p2, m_strokeColor);
    }

    static float GetLineLength(CPoint p1, CPoint p2)
    {
        return float(std::sqrt(std::pow(p2.getX() - p1.getX(), 2) + std::pow(p2.getY() - p1.getY(), 2)));
    }

private:
    CPoint m_p1, m_p2;
    Color m_strokeColor;

};

#endif //OOP_4_CLINESEGMENT_H
