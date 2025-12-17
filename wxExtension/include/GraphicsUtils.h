#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <wx/graphics.h>
#include <wx/colour.h>
#include <wx/brush.h>
#include <wx/pen.h>

#include <Structs.h>

class GraphicsUtils {
public:
    static void drawRoundedRect(
        wxGraphicsContext* gc,
        double x, double y, double w, double h,
        const CornerRadius& cornerRadius,
        const Thickness& borderThickness,
        const wxColour& backgroundColor,
        const wxColour& borderColor,
        const wxColour& parentBg = wxColour(255, 255, 255));
};

