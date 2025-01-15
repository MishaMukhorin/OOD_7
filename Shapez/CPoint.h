//
// Created by Misha on 29.03.2024.
//

#ifndef OOP_4_CPOINT_H
#define OOP_4_CPOINT_H


class CPoint {
public:
    CPoint(float x, float y) : x(x), y(y) {}
    [[nodiscard]] float GetX() const { return x; }
    [[nodiscard]] float GetY() const { return y; }
    void SetX(float newX) { x = newX; }
    void SetY(float newY) { y = newY; }

private:
    float x, y;
};

#endif //OOP_4_CPOINT_H
