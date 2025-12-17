#pragma once

#include <cmath>
#include <wx/graphics.h>
#include <wx/colour.h>
#include <wx/brush.h>
#include <wx/pen.h>

#include <Structs.h>

class GraphicsUtils {
public:
    // Рисование прямоугольника с разными радиусами углов и границами
    static void drawRoundedRect(
        wxGraphicsContext* gc,
        double x, double y, double w, double h,
        const CornerRadius& cornerRadius,
        const Thickness& borderThickness,
        const wxColour& backgroundColor,
        const wxColour& borderColor,
        const wxColour& parentBg = wxColour(255, 255, 255)
    );

    // Создание пути со скруглёнными углами
    static wxGraphicsPath createRoundedRectPath(
        wxGraphicsContext* gc,
        double x, double y, double w, double h,
        const CornerRadius& cornerRadius
    );
};

