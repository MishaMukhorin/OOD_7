//
// Created by Misha on 11.04.2024.
//

#ifndef OOP_4_ICANVASDROWABLE_H
#define OOP_4_ICANVASDROWABLE_H

#include "ICanvas.h"

class ICanvasDrowable
{
public:
    virtual ~ICanvasDrowable() = default;

    virtual void Draw(ICanvas* canvas) const = 0;

protected:
    ICanvasDrowable() = default;

};


#endif //OOP_4_ICANVASDROWABLE_H
