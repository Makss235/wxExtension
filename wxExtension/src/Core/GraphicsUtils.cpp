#include "GraphicsUtils.h"

void GraphicsUtils::drawRoundedRect(wxGraphicsContext* gc, double x, double y, double w, double h, 
	const CornerRadius& cr, const Thickness& bt, const wxColour& backgroundColor, 
	const wxColour& borderColor, const wxColour& parentBg) {
    if (!gc) return;

    w -= 1;
    h -= 1;

    if (parentBg.IsOk()) {
        gc->SetBrush(wxBrush(parentBg));
        gc->SetPen(*wxTRANSPARENT_PEN);
        gc->DrawRectangle(x - 1, y, w + 2, h + 1);
    }

    wxGraphicsPath mainPath = createRoundedRectPath(gc, x, y, w, h, cr);

    gc->SetBrush(wxBrush(backgroundColor));
    gc->SetPen(*wxTRANSPARENT_PEN);
    gc->DrawPath(mainPath);

    bool hasBorder = (bt.left > 0 || bt.top > 0 || bt.right > 0 || bt.bottom > 0);

    if (hasBorder && borderColor.IsOk()) {
        double maxBorder = std::max({ bt.left, bt.top, bt.right, bt.bottom });

        if (bt.left == bt.top && bt.top == bt.right && bt.right == bt.bottom) {
            gc->SetPen(wxPen(borderColor, static_cast<int>(bt.left)));
            gc->SetBrush(*wxTRANSPARENT_BRUSH);

            double offset = bt.left / 2.0;
            wxGraphicsPath borderPath = createRoundedRectPath(
                gc, x + offset, y + offset, w - bt.left, h - bt.top, cr);
            gc->StrokePath(borderPath);
        }
        else {
            gc->SetPen(*wxTRANSPARENT_PEN);
            gc->SetBrush(wxBrush(borderColor));

            if (bt.top > 0) {
                gc->DrawRectangle(x + cr.topLeft, y,
                    w - cr.topLeft - cr.topRight, bt.top);
            }

            if (bt.right > 0) {
                gc->DrawRectangle(x + w - bt.right, y + cr.topRight,
                    bt.right, h - cr.topRight - cr.bottomRight);
            }

            if (bt.bottom > 0) {
                gc->DrawRectangle(x + cr.bottomLeft, y + h - bt.bottom,
                    w - cr.bottomLeft - cr.bottomRight, bt.bottom);
            }

            if (bt.left > 0) {
                gc->DrawRectangle(x, y + cr.topLeft,
                    bt.left, h - cr.topLeft - cr.bottomLeft);
            }
        }
    }
}

wxGraphicsPath GraphicsUtils::createRoundedRectPath(wxGraphicsContext* gc, 
    double x, double y, double w, double h, const CornerRadius& cr) {
    wxGraphicsPath path = gc->CreatePath();

    path.MoveToPoint(x + cr.topLeft, y);
    path.AddLineToPoint(x + w - cr.topRight, y);
    if (cr.topRight > 0) {
        path.AddArc(x + w - cr.topRight, y + cr.topRight,
            cr.topRight, -M_PI / 2, 0, true);
    }

    path.AddLineToPoint(x + w, y + h - cr.bottomRight);
    if (cr.bottomRight > 0) {
        path.AddArc(x + w - cr.bottomRight, y + h - cr.bottomRight,
            cr.bottomRight, 0, M_PI / 2, true);
    }

    path.AddLineToPoint(x + cr.bottomLeft, y + h);
    if (cr.bottomLeft > 0) {
        path.AddArc(x + cr.bottomLeft, y + h - cr.bottomLeft,
            cr.bottomLeft, M_PI / 2, M_PI, true);
    }

    path.AddLineToPoint(x, y + cr.topLeft);
    if (cr.topLeft > 0) {
        path.AddArc(x + cr.topLeft, y + cr.topLeft,
            cr.topLeft, M_PI, 3 * M_PI / 2, true);
    }

    path.CloseSubpath();
    return path;
}
