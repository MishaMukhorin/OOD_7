//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_ISOLIDSHAPE_H
#define OOP_4_ISOLIDSHAPE_H

#include "IShape.h"

class ISolidShape : public IShape {
public:
    ~ISolidShape() override = default;

    [[nodiscard]] virtual Color GetFillColor() const = 0;
    [[nodiscard]] virtual float GetArea() const = 0;
    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << IShape::ToString();
        ss << "Area: " << GetArea() << std::endl;
        ss << "Fill color: " << GetFillColor().ToString() << std::endl;
        return ss.str();
    }

protected:
    ISolidShape() = default;
};

#endif //OOP_4_ISOLIDSHAPE_H
