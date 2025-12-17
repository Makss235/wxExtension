#pragma once

struct CornerRadius {
    double topLeft = 0.0;
    double topRight = 0.0;
    double bottomLeft = 0.0;
    double bottomRight = 0.0;

    CornerRadius() = default;
    CornerRadius(double all) : topLeft(all), topRight(all),
        bottomLeft(all), bottomRight(all) {}
    CornerRadius(double tl, double tr, double bl, double br)
        : topLeft(tl), topRight(tr), bottomLeft(bl), bottomRight(br) {}
};

struct Thickness {
    double left = 0.0;
    double top = 0.0;
    double right = 0.0;
    double bottom = 0.0;

    Thickness() = default;
    Thickness(double all) : left(all), top(all), right(all), bottom(all) {}
    Thickness(double l, double t, double r, double b)
        : left(l), top(t), right(r), bottom(b) {}
};
