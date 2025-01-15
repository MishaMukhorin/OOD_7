//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CCIRCLE_H
#define OOP_4_CCIRCLE_H

#include <cmath>
#include <utility>
#include "CPoint.h"
#include "../Interfaces/IStyle.h"
#include <memory>

class CEllipse : public IShape {
public:
    CEllipse(const CPoint& center,
             float radiusX,
             float radiusY,
             const LineStyle& strokeStyle,
             const FillStyle& fillStyle)
            : m_center(center),
              m_radiusX(radiusX),
              m_radiusY(radiusY),
              m_strokeStyle(std::make_shared<LineStyle>(strokeStyle)),
              m_fillStyle(std::make_shared<FillStyle>(fillStyle))
              {}

    void AddShape(const std::shared_ptr<IShape>& shape) override {};

    [[nodiscard]] std::string GetType() const override
    {
        return "Ellipse";
    }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Ellipse: Center=(" << m_center.GetX() << ", " << m_center.GetY()
           << "), radiusX=" << m_radiusX << ", radiusY=" << m_radiusY << std::endl;
        ss << IShape::ToString();
        return ss.str();
    }

    std::pair<CPoint, CPoint> GetRect() override
    {
        CPoint topLeft(0, 0), lowRight(0, 0);
        topLeft.SetX(m_center.GetX() - m_radiusX);
        topLeft.SetY(m_center.GetY() - m_radiusY);
        lowRight.SetX(m_center.GetX() + m_radiusX);
        lowRight.SetY(m_center.GetY() + m_radiusY);

        return {topLeft, lowRight};
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeStyle() const override
    {
        return m_strokeStyle;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillStyle() const override
    {
        return m_fillStyle;
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

    void Move(float x, float y) override
    {
        m_center.SetX(m_center.GetX() + x);
        m_center.SetY(m_center.GetY() + y);
    }

    void Draw(ICanvas* canvas) const override
    {
        canvas->DrawEllipse(m_center, m_radiusX, m_radiusY,
                            m_strokeStyle->GetColor().value_or(Color("0")),
                            m_strokeStyle->GetLineWidth().value_or(2));

        canvas->FillEllipse(m_center, m_radiusX, m_radiusY, m_fillStyle->GetColor().value_or(Color("0")));
    }

    [[nodiscard]] std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<CEllipse>(*this);
    }

private:
    CPoint m_center;
    float m_radiusX, m_radiusY;
    std::shared_ptr<IStyle> m_strokeStyle;
    std::shared_ptr<IStyle> m_fillStyle;
};

#endif //OOP_4_CCIRCLE_H
