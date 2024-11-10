//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CPOINT_H
#define OOP_4_CPOINT_H


class CPoint {
public:
    CPoint(float x, float y) : x(x), y(y) {}
    [[nodiscard]] float getX() const { return x; }
    [[nodiscard]] float getY() const { return y; }

private:
    float x, y;
};

#endif //OOP_4_CPOINT_H
