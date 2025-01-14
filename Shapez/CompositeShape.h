//
// Created by mrLogic on 11/11/2024.
//

#ifndef OOD_7_COMPOSITESHAPE_H
#define OOD_7_COMPOSITESHAPE_H


#include <vector>
#include <memory>
#include "../Interfaces/ISolidShape.h"
#include "../Interfaces/IStyle.h"
#include "CColor.h"

class CompositeShape : public ISolidShape {
public:

    void AddShape(const std::shared_ptr<IShape>& shape) override
    {
        m_shapes.push_back(shape);
        m_fillStyles.push_back(shape->GetFillColor());
        m_strokeStyles.push_back(shape->GetStrokeColor());
    }

    [[nodiscard]] float GetPerimeter() const override
    {
        float totalPerimeter = 0;
        for (const auto& shape : m_shapes)
        {
            totalPerimeter += shape->GetPerimeter();
        }
        return totalPerimeter;
    }

    [[nodiscard]] float GetArea() const override
    {
        float totalArea = 0;
        for (const auto& shape : m_shapes) {
            if (auto solidShape = std::dynamic_pointer_cast<ISolidShape>(shape))
            {
                totalArea += solidShape->GetArea();
            }
        }
        return totalArea;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeColor() const override
    {
        if (!m_strokeStyles.empty())
        {
            auto strokeColor = m_strokeStyles[0];
            for (const auto& style: m_strokeStyles)
            {
                if (!((style->GetColor().value_or(Color("0")).ToString() == strokeColor->GetColor().value_or(Color("0")).ToString())
                and (style->GetLineWidth() == strokeColor->GetLineWidth())))
                {
                    return nullptr;
                }
            }
            return strokeColor;
        }
        return nullptr;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillColor() const override
    {
        if (!m_strokeStyles.empty())
        {
            auto fillColor = m_fillStyles[0];
            for (const auto& style: m_fillStyles) // выделить отдельный компоновщик для стилей
            {
                if (!((style->GetColor().value_or(Color("0")).ToString() == fillColor->GetColor().value_or(Color("0")).ToString())
                      and (style->GetLineWidth() == fillColor->GetLineWidth())))
                {
                    return nullptr;
                }
            }
            return fillColor;
        }
        return nullptr;

    }

    void SetStrokeColor(LineStyle style) override
    {
        for (auto& s: m_strokeStyles)
        {
            s->SetColor(Color(style.GetColor()->ToString()));
        }
    }

    void SetFillColor(FillStyle style) override
    {
        for (auto& s: m_fillStyles)
        {
            s->SetColor(Color(style.GetColor()->ToString()));
        }
    }

    void SetLineWidth(float width) override
    {
        for (auto& s: m_shapes)
        {
            s->SetLineWidth(width);
        }
    }

    void Draw(ICanvas* canvas) const override {
        for (const auto& shape : m_shapes) {
            shape->Draw(canvas);
        }
    }

private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
    std::vector<std::shared_ptr<IStyle>> m_strokeStyles;
    std::vector<std::shared_ptr<IStyle>> m_fillStyles;
};


#endif //OOD_7_COMPOSITESHAPE_H
