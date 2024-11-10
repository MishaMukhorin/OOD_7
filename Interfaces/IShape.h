//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_ISHAPE_H
#define OOP_4_ISHAPE_H

#include "../Shapez/CColor.h"
#include "ICanvasDrowable.h"


class IShape: public ICanvasDrowable {
public:
    ~IShape() override = default;

    [[nodiscard]] virtual float GetPerimeter() const = 0;
    [[nodiscard]] virtual std::string ToString() const
    {
        std::stringstream ss;
        ss << "Perimeter: " << GetPerimeter() << std::endl;
        ss << "Stroke color: " << GetStrokeColor().ToString() << std::endl;
        return ss.str();
    }

    [[nodiscard]] virtual Color GetStrokeColor() const = 0;

protected:
    IShape() = default;
};


#endif