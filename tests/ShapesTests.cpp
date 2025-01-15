#include <gtest/gtest.h>
#include "../Shapez/CompositeShape.h"
#include "../Shapez/CRectangle.h"
#include "MockCanvas.h"

class MockStyle : public IStyle {
public:
    MockStyle(const Color& color, float lineWidth) : m_color(color), m_lineWidth(lineWidth) {}

    [[nodiscard]] std::optional<Color> GetColor() const override {
        return m_color;
    }

    void SetColor(const Color& color) override {
        m_color = color;
    }

    [[nodiscard]] std::optional<float> GetLineWidth() const override {
        return m_lineWidth;
    }

    void SetLineWidth(float width) override {
        m_lineWidth = width;
    }

private:
    std::optional<Color> m_color;
    std::optional<float> m_lineWidth;
};

TEST(CompositeShapeTest, AddShapeTest) {
    CompositeShape compositeShape;
    auto rect1 = std::make_shared<CRectangle>(CPoint(0, 0), 10, 20,
                                              std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));
    auto rect2 = std::make_shared<CRectangle>(CPoint(5, 5), 15, 25,
                                              std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));

    compositeShape.AddShape(rect1);
    compositeShape.AddShape(rect2);

}

TEST(CompositeShapeTest, GetPerimeterTest) {
    CompositeShape compositeShape;
    auto rect = std::make_shared<CRectangle>(CPoint(0, 0), 10, 20,
                                             std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                             std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));
    compositeShape.AddShape(rect);

    EXPECT_FLOAT_EQ(compositeShape.GetPerimeter(), rect->GetPerimeter());
}

TEST(CompositeShapeTest, GetAreaTest) {
    CompositeShape compositeShape;
    auto rect = std::make_shared<CRectangle>(CPoint(0, 0), 10, 20,
                                             std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                             std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));
    compositeShape.AddShape(rect);

    EXPECT_FLOAT_EQ(compositeShape.GetArea(), rect->GetArea());
}

TEST(CompositeShapeTest, UniformStrokeColorTest) {
    CompositeShape compositeShape;
    auto strokeStyle = std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f);
    auto fillStyle = std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f);

    auto rect1 = std::make_shared<CRectangle>(CPoint(0, 0), 10, 20, strokeStyle, fillStyle);
    auto rect2 = std::make_shared<CRectangle>(CPoint(5, 5), 15, 25, strokeStyle, fillStyle);

    compositeShape.AddShape(rect1);
    compositeShape.AddShape(rect2);

    auto result = compositeShape.GetStrokeStyle();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetColor()->ToString(), "ff0000ff");
    EXPECT_FLOAT_EQ(result->GetLineWidth().value_or(0), 2.0f);
}

TEST(CompositeShapeTest, DifferentStrokeColorTest) {
    CompositeShape compositeShape;
    auto rect1 = std::make_shared<CRectangle>(CPoint(0, 0), 10, 20,
                                              std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));
    auto rect2 = std::make_shared<CRectangle>(CPoint(5, 5), 15, 25,
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 3.0f),
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));

    compositeShape.AddShape(rect1);
    compositeShape.AddShape(rect2);

    EXPECT_EQ(compositeShape.GetStrokeStyle(), nullptr);
}

TEST(CompositeShapeTest, SetFillStyleTest) {
    CompositeShape compositeShape;
    auto rect1 = std::make_shared<CRectangle>(CPoint(0, 0), 10, 20,
                                              std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));
    auto rect2 = std::make_shared<CRectangle>(CPoint(5, 5), 15, 25,
                                              std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));

    compositeShape.AddShape(rect1);
    compositeShape.AddShape(rect2);

    auto fillStyle = std::make_shared<MockStyle>(Color("0000ffff"), 1.0f);
    compositeShape.SetFillStyle(fillStyle);

    EXPECT_EQ(compositeShape.GetFillStyle()->GetColor()->ToString(), "0000ffff");
    EXPECT_FLOAT_EQ(compositeShape.GetFillStyle()->GetLineWidth().value_or(0), 1.0f);
}

TEST(CompositeShapeTest, DrawTest) {
    CompositeShape compositeShape;
    auto rect1 = std::make_shared<CRectangle>(CPoint(0, 0), 10, 20,
                                              std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));
    auto rect2 = std::make_shared<CRectangle>(CPoint(5, 5), 15, 25,
                                              std::make_shared<MockStyle>(Color("ff0000ff"), 2.0f),
                                              std::make_shared<MockStyle>(Color("00ff00ff"), 1.5f));
    compositeShape.AddShape(rect1);
    compositeShape.AddShape(rect2);

    MockCanvas canvas;
    compositeShape.Draw(&canvas);

    EXPECT_EQ(canvas.GetDrawCallCount(), 10);
}

GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}