//
// Created by mrLogic on 11/11/2024.
//

#ifndef OOD_7_MOCKCANVAS_H
#define OOD_7_MOCKCANVAS_H

#include "../Interfaces/ICanvas.h"
#include <gmock/gmock.h>
#include <vector>

class MockCanvas : public ICanvas {
public:
    MockCanvas() = default;

    struct DrawCall {
        std::string type;
        std::vector<CPoint> points;
        Color color;
        float lineWidth;
    };

    void FillPolygon(std::vector<CPoint> points, Color fillColor) override {
        drawCalls.push_back({"FillPolygon", points, fillColor, 0});
    }

    void DrawLine(CPoint from, CPoint to, Color lineColor, float lineWidth) override {
        drawCalls.push_back({"DrawLine", {from, to}, lineColor, lineWidth});
    }

    [[nodiscard]] size_t GetDrawCallCount() const {
        return drawCalls.size();
    }

    [[nodiscard]] const DrawCall& GetDrawCall(size_t index) const {
        return drawCalls.at(index);
    }

    void DrawEllipse(CPoint center, float radiusX, float radiusY, Color lineColor, float lineWidth) override {};
    void FillEllipse(CPoint center, float radiusX, float radiusY, Color fillColor) override {};


private:
    std::vector<DrawCall> drawCalls;
};
#endif //OOD_7_MOCKCANVAS_H
