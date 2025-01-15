//
// Created by mrLogic on 1/15/2025.
//

#ifndef OOD_7_SHAPEUNIT_H
#define OOD_7_SHAPEUNIT_H

#include <string>
#include <memory>
#include <memory>
#include "IShape.h"


class ShapeUnit {
public:

    ShapeUnit(std::string id, std::unique_ptr<IShape> GeometryType):
            m_id(std::move(id)), m_shape(std::move(GeometryType)), m_lowRight(0, 0), m_topLeft(0, 0)
    {
        m_topLeft =
    }

    void Draw(ICanvas* canvas) const
    {
        m_shape->Draw(canvas);
    }

    void Move(float dx, float dy)
    {
        m_shape->Move(dx, dy);
    }

    [[nodiscard]] std::unique_ptr<ShapeUnit> Clone(const std::string& newId) const
    {
        return make_unique<ShapeUnit>(newId, m_shape->Clone());
    }

    [[nodiscard]] std::string GetId() const
    {
        return m_id;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillStyle() const
    {
        return m_shape->GetFillStyle();
    }

    [[nodiscard]] std::string ToString() const
    {
        std::stringstream ss;
        ss << m_id << " " << m_shape->ToString();
        return ss.str();
    }
    [[nodiscard]] std::shared_ptr<IStyle> GetStrokeStyle() const
    {
        return m_shape->GetStrokeStyle();
    }

    [[nodiscard]] std::string GetType() const
    {
        return m_shape->GetType();
    }

    [[nodiscard]] std::string GetShapeParamsString() const
    {
        return m_shape->ToString();
    }

    ~ShapeUnit() = default;

private:
    std::string m_id;
    CPoint m_topLeft, m_lowRight;
    std::unique_ptr<IShape> m_shape;
};


#endif //OOD_7_SHAPEUNIT_H
