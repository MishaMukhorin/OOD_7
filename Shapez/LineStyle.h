//
// Created by mrLogic on 11/11/2024.
//

#ifndef OOD_7_LINESTYLE_H
#define OOD_7_LINESTYLE_H


#include "../Interfaces/IStyle.h"

class LineStyle : public IStyle {
public:
    LineStyle(const Color& color, float width) : m_color(color), lineWidth(width) {}

    [[nodiscard]] std::optional<Color> GetColor() const override { return m_color; }
    void SetColor(const Color& c) override { this->m_color = c; }

    [[nodiscard]] std::optional<float> GetLineWidth() const override { return lineWidth; }
    void SetLineWidth(float width) override { lineWidth = width; }

private:
    Color m_color;
    float lineWidth;
};


#endif //OOD_7_LINESTYLE_H
