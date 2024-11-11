//
// Created by mrLogic on 11/11/2024.
//

#ifndef OOD_7_ISTYLE_H
#define OOD_7_ISTYLE_H

#include "../Shapez/CColor.h"
#include <optional>

class IStyle {
public:
    virtual ~IStyle() = default;

    [[nodiscard]] virtual std::optional<Color> GetColor() const = 0;
    virtual void SetColor(const Color& color) = 0;

    [[nodiscard]] virtual std::optional<float> GetLineWidth() const = 0;
    virtual void SetLineWidth(float width) = 0;
};

#endif //OOD_7_ISTYLE_H
