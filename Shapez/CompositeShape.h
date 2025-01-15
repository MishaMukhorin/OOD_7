//
// Created by mrLogic on 11/11/2024.
//

#ifndef OOD_7_COMPOSITESHAPE_H
#define OOD_7_COMPOSITESHAPE_H


#include <vector>
#include <memory>
#include "../Interfaces/IStyle.h"
#include "CColor.h"
#include "../Interfaces/IShape.h"

class CompositeShape : public IShape {
public:

    void AddUnresolvedId(const std::string& id)
    {
        m_unresolvedIds.emplace_back(id);
    }

    /// promise to resolve ids
    std::vector<std::string> getIdsToResolve()
    {
        std::vector<std::string> idsToBeResolved = std::move(m_unresolvedIds);
        for (const auto& id: idsToBeResolved)
        {
            m_resolvedIds.emplace_back(id);
        }
        return idsToBeResolved;
    }

    void AddShape(const std::shared_ptr<IShape>& shape) override
    {
        m_shapes.push_back(shape);
        m_fillStyles.push_back(shape->GetFillStyle());
        m_strokeStyles.push_back(shape->GetStrokeStyle());
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeStyle() const override
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

    [[nodiscard]] std::shared_ptr<IStyle> GetFillStyle() const override
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

    [[nodiscard]] std::string GetType() const override
    {
        return "Composite";
    }

    [[nodiscard]] std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<CompositeShape>(*this);
    }

    void Move(float x, float y) override
    {
        for (const auto& shape: m_shapes)
        {
            shape->Move(x, y);
        }
    }

    [[nodiscard]] std::string ToString() const override
    {
        std::ostringstream ss;
        ss << "Ids in this group: " << std::endl;
        for (const auto& id: m_resolvedIds)
        {
            ss << " - " << id << std::endl;
        }
        ss << IShape::ToString();
        return ss.str();
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

    //todo выделить компоновщик для стилей
    std::vector<std::shared_ptr<IStyle>> m_strokeStyles;
    std::vector<std::shared_ptr<IStyle>> m_fillStyles;

    std::vector<std::string> m_unresolvedIds;
    std::vector<std::string> m_resolvedIds;

};


#endif //OOD_7_COMPOSITESHAPE_H
