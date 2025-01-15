//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CRECTANGLE_H
#define OOP_4_CRECTANGLE_H

#include <utility>
#include "../Interfaces/IStyle.h"
#include "CPoint.h"
#include "FillStyle.h"
#include "LineStyle.h"

class CRectangle : public IShape {
public:
    CRectangle(const CPoint& topLeft, float width, float height,
               const LineStyle& strokeStyle,
               const FillStyle& fillStyle)
            : m_topLeft(topLeft), m_width(width), m_height(height),
              m_strokeStyle(std::make_shared<LineStyle>(strokeStyle)),
              m_fillStyle(std::make_shared<FillStyle>(fillStyle)) {}

    void AddShape(const std::shared_ptr<IShape>& shape) override {};

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeStyle() const override {
        return m_strokeStyle;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillStyle() const override {
        return m_fillStyle;
    }

    [[nodiscard]] std::string GetType() const override
    {
        return "Rectangle";
    }

    void Move(float x, float y) override
    {
        m_topLeft.SetX(m_topLeft.GetX() + x);
        m_topLeft.SetY(m_topLeft.GetY() + y);
    }

    [[nodiscard]] std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<CRectangle>(*this);
    }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Rectangle: (" << m_topLeft.GetX() << ", " << m_topLeft.GetY() << "), ("
            << m_width << ", " << m_height << ") " << std::endl;
        ss << IShape::ToString();
        return ss.str();
    }

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


    void Draw(ICanvas* canvas) const override {
        canvas->FillPolygon({m_topLeft,
                             {m_topLeft.GetX(), m_topLeft.GetY() + m_height},
                             {m_topLeft.GetX() + m_width, m_topLeft.GetY() + m_height},
                             {m_topLeft.GetX() + m_width, m_topLeft.GetY()}},
                            m_fillStyle->GetColor().value_or(Color("0")));

        canvas->DrawLine(m_topLeft, {m_topLeft.GetX(), m_topLeft.GetY() + m_height},
                         m_strokeStyle->GetColor().value_or(Color("0")),
                         m_strokeStyle->GetLineWidth().value_or(2));
        canvas->DrawLine({m_topLeft.GetX(), m_topLeft.GetY() + m_height}, {m_topLeft.GetX() + m_width,
                                                                           m_topLeft.GetY() + m_height},
                         m_strokeStyle->GetColor().value_or(Color("0")),
                         m_strokeStyle->GetLineWidth().value_or(2));
        canvas->DrawLine({m_topLeft.GetX() + m_width, m_topLeft.GetY() + m_height}, {m_topLeft.GetX() + m_width,
                                                                                     m_topLeft.GetY()},
                         m_strokeStyle->GetColor().value_or(Color("0")),
                         m_strokeStyle->GetLineWidth().value_or(2));
        canvas->DrawLine({m_topLeft.GetX() + m_width, m_topLeft.GetY()}, m_topLeft,
                         m_strokeStyle->GetColor().value_or(Color("0")),
                         m_strokeStyle->GetLineWidth().value_or(2));
    }

private:
    CPoint m_topLeft;
    float m_width, m_height;
    std::shared_ptr<IStyle> m_strokeStyle;
    std::shared_ptr<IStyle> m_fillStyle;
};

#endif //OOP_4_CRECTANGLE_H
