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
#include "FillStyle.h"


#include <memory>

class CLineSegment : public IShape {
public:

    CLineSegment(const CPoint& p1, const CPoint& p2, const LineStyle& strokeStyle)
            :   m_p1(p1), m_p2(p2), m_strokeStyle(std::make_shared<LineStyle>(strokeStyle)) {}

    void AddShape(const std::shared_ptr<IShape>& shape) override {};


    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeStyle() const override
    {
        return m_strokeStyle;
    }
    [[nodiscard]] std::shared_ptr<IStyle> GetFillStyle() const override
    {
        return nullptr;
    }

    [[nodiscard]] std::string GetType() const override
    {
        return "Line";
    }

    [[nodiscard]] std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<CLineSegment>(*this);
    }

    void Move(float x, float y) override
    {
        m_p1.SetX(m_p1.GetX() + x);
        m_p1.SetY(m_p1.GetY() + y);
        m_p2.SetX(m_p2.GetX() + x);
        m_p2.SetY(m_p2.GetY() + y);
    }

    std::pair<CPoint, CPoint> GetRect() override
    {
        CPoint topLeft(0, 0), lowRight(0, 0);

        topLeft.SetX(std::min(m_p1.GetX(), m_p2.GetX()));
        topLeft.SetY(std::min(m_p1.GetY(), m_p2.GetY()));
        lowRight.SetX(std::max(m_p1.GetX(), m_p2.GetX()));
        lowRight.SetY(std::max(m_p1.GetY(), m_p2.GetY()));

        return {topLeft, lowRight};
    }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Line: (" << m_p1.GetX() << ", " << m_p1.GetY() << "), (" << m_p2.GetX() << ", " << m_p2.GetY() << ") " << std::endl;
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

    void SetStrokeColor(LineStyle style) override
    {
        m_strokeStyle->SetColor(Color(style.GetColor()->ToString()));
    }

    void SetFillColor(FillStyle style) override
    {

    }

    void SetLineWidth(float width) override
    {
        m_strokeStyle->SetLineWidth(width);
    }

    static float GetLineLength(CPoint p1, CPoint p2)
    {
        return std::sqrt(std::pow(p2.GetX() - p1.GetX(), 2) + std::pow(p2.GetY() - p1.GetY(), 2));
    }

private:
    CPoint m_p1, m_p2;
    std::shared_ptr<IStyle> m_strokeStyle;
};


#endif //OOP_4_CLINESEGMENT_H
