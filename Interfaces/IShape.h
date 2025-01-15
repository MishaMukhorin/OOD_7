//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_ISHAPE_H
#define OOP_4_ISHAPE_H

#include "../Shapez/CColor.h"
#include "ICanvasDrowable.h"
#include "IStyle.h"
#include "../Shapez/FillStyle.h"
#include "../Shapez/LineStyle.h"


class IShape: public ICanvasDrowable {
public:
    ~IShape() override = default;

    virtual void AddShape(const std::shared_ptr<IShape>& shape) = 0;

    [[nodiscard]] virtual std::string GetType() const = 0;
    [[nodiscard]] virtual std::string ToString() const
    {

        std::stringstream ss;
        ss << "Stroke color: " << GetStrokeStyle()->GetColor()->ToString() << std::endl;
        if (GetFillStyle() != nullptr)
        {
            ss << "Fill color: " << GetFillStyle()->GetColor()->ToString() << std::endl;
        }
        ss << "Line Width: " << GetStrokeStyle()->GetLineWidth().value_or(0) << std::endl;
        return ss.str();
    }

    virtual void Move(float x, float y) = 0;

    virtual std::pair<CPoint, CPoint> GetRect() = 0;

    [[nodiscard]] virtual std::shared_ptr<IStyle> GetStrokeStyle() const = 0;
    [[nodiscard]] virtual std::shared_ptr<IStyle> GetFillStyle() const = 0;

    virtual void SetStrokeColor(LineStyle style) = 0;
    virtual void SetLineWidth(float width) = 0;
    virtual void SetFillColor(FillStyle style) = 0;

    [[nodiscard]] virtual std::unique_ptr<IShape> Clone() const = 0;


protected:
    IShape() = default;
};


#endif