//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_ISHAPE_H
#define OOP_4_ISHAPE_H

#include "../Shapez/CColor.h"
#include "ICanvasDrowable.h"
#include "IStyle.h"


class IShape: public ICanvasDrowable {
public:
    ~IShape() override = default;

    virtual void AddShape(const std::shared_ptr<IShape>& shape) = 0;

    [[nodiscard]] virtual float GetPerimeter() const = 0;
    [[nodiscard]] virtual std::string ToString() const
    {
        std::stringstream ss;
        ss << "Perimeter: " << GetPerimeter() << std::endl;
        ss << "Stroke m_color: " << GetStrokeColor()->GetColor()->ToString() << std::endl;
        return ss.str();
    }

    [[nodiscard]] virtual std::shared_ptr<IStyle> GetStrokeColor() const = 0;
    [[nodiscard]] virtual std::shared_ptr<IStyle> GetFillColor() const = 0;

protected:
    IShape() = default;
};


#endif