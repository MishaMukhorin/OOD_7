//
// Created by mrLogic on 11/11/2024.
//

#ifndef OOD_7_FILLSTYLE_H
#define OOD_7_FILLSTYLE_H
#include "../Interfaces/IStyle.h"

class FillStyle : public IStyle {
public:
    explicit FillStyle(const Color& c) : m_color(c) {}

    [[nodiscard]] std::optional<Color> GetColor() const override { return m_color; }
    void SetColor(const Color& c) override { this->m_color = c; }

    [[nodiscard]] std::optional<float> GetLineWidth() const override { return {}; }
    void SetLineWidth(float) override {}

private:
    Color m_color;
};

#endif //OOD_7_FILLSTYLE_H
