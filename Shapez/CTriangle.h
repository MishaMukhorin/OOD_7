//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CTRIANGLE_H
#define OOP_4_CTRIANGLE_H

#include <ostream>
#include <utility>
#include "CPoint.h"
#include "CLineSegment.h"
#include <memory>

class CTriangle : public IShape
{
public:
    CTriangle(const CPoint& p1,
              const CPoint& p2,
              const CPoint& p3,
              const LineStyle& strokeStyle,
              const FillStyle& fillStyle)
            : m_p1(p1),
              m_p2(p2),
              m_p3(p3),
              m_strokeStyle(std::make_shared<LineStyle>(strokeStyle)),
              m_fillStyle(std::make_shared<FillStyle>(fillStyle)) {}



    void SetStrokeColor(LineStyle style) override
    {
        m_strokeStyle->SetColor(Color(style.GetColor()->ToString()));
    }

    void SetFillColor(FillStyle style) override
    {
        m_fillStyle->SetColor(Color(style.GetColor()->ToString()));
    }

    void SetLineWidth(float width) override {
        if (width > 0)
        {
            m_fillStyle->SetLineWidth(width);
        }
    }

    [[nodiscard]] std::string GetType() const override
    {
        return "Triangle";
    }

    void Move(float x, float y) override
    {
        m_p1.SetX(m_p1.GetX() + x);
        m_p1.SetY(m_p1.GetY() + y);
        m_p2.SetX(m_p2.GetX() + x);
        m_p2.SetY(m_p2.GetY() + y);
        m_p3.SetX(m_p3.GetX() + x);
        m_p3.SetY(m_p3.GetY() + y);
    }

    [[nodiscard]] std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<CTriangle>(*this);
    }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Triangle: (" << m_p1.GetX() << ", " << m_p1.GetY() << "), (" << m_p2.GetX() << ", " << m_p2.GetY() << "), (" << m_p3.GetX() << ", " << m_p3.GetY() << ")";
        ss << IShape::ToString();
        return ss.str();
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeStyle() const override
    {
        return m_strokeStyle ;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillStyle() const override
    {
        return m_fillStyle ;
    }

    void Draw(ICanvas* canvas) const override
    {
        // Fill the triangle with the fill color if enabled
        if (m_fillStyle)
        {
            Color fillColor = m_fillStyle->GetColor().value_or(Color("0"));
            canvas->FillPolygon({m_p1, m_p2, m_p3}, fillColor);
        }

        // Draw each line of the triangle with the stroke color if enabled
        if (m_strokeStyle)
        {
            Color strokeColor = m_strokeStyle->GetColor().value_or(Color("0"));
            float strokeWidth = m_strokeStyle->GetLineWidth().value_or(2);
            canvas->DrawLine(m_p1, m_p2, strokeColor, strokeWidth);
            canvas->DrawLine(m_p2, m_p3, strokeColor, strokeWidth);
            canvas->DrawLine(m_p3, m_p1, strokeColor, strokeWidth);
        }
    }

    void AddShape(const std::shared_ptr<IShape>& shape) override {};

private:
    CPoint m_p1, m_p2, m_p3;
    std::shared_ptr<IStyle> m_strokeStyle;
    std::shared_ptr<IStyle> m_fillStyle;
};


#endif //OOP_4_CTRIANGLE_H
