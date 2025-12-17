#include "GraphicsUtils.h"

void GraphicsUtils::drawRoundedRect(wxGraphicsContext* gc, double x, double y, double w, double h, 
	const CornerRadius& cr, const Thickness& bt, const wxColour& bgc, const wxColour& bc, const wxColour& pbg) {

    w--;
    h--;

    wxPoint2DDouble ul(x + cr.topLeft, y + cr.topLeft);
    wxPoint2DDouble ur(x + w - cr.topRight, y + cr.topRight);
    wxPoint2DDouble lr(x + w - cr.bottomRight, y + h - cr.bottomRight);
    wxPoint2DDouble ll(x + cr.bottomLeft, y + h - cr.bottomLeft);

    gc->SetBrush(pbg);
    gc->SetPen(wxPen(pbg, 1));
    gc->DrawRectangle(-1, 0, w + 2, h);

    gc->SetBrush(bgc);
    gc->SetPen(wxPen(bgc, 1));
    wxGraphicsPath commonPath = gc->CreatePath();

    commonPath.AddArc(ul, cr.topLeft, -M_PI, -M_PI / 2, true);
    commonPath.AddLineToPoint(x + w - cr.topRight, y);
    commonPath.AddArc(ur, cr.topRight, -M_PI / 2, 0, true);
    commonPath.AddLineToPoint(x + w, y + h - cr.bottomRight);
    commonPath.AddArc(lr, cr.bottomRight, 0, M_PI / 2, true);
    commonPath.AddLineToPoint(x + cr.bottomLeft, y + h);
    commonPath.AddArc(ll, cr.bottomLeft, M_PI / 2, M_PI, true);
    commonPath.AddLineToPoint(x, y + cr.topLeft);

    gc->DrawPath(commonPath);

    if (bt.left != 0 || bt.top != 0 ||
        bt.right != 0 || bt.bottom != 0)
    {
        if (bt.left != 0 || bt.top != 0)
        {
            int pointCount = std::round(cr.topLeft / 4);
            const double step = M_PI / (2 * pointCount);

            gc->SetBrush(bc);
            gc->SetPen(wxPen(bc, 1));

            wxGraphicsPath path = gc->CreatePath();
            path.AddArc(x + cr.topLeft, y + cr.topLeft,
                cr.topLeft, M_PI, -M_PI / 2, true);
            path.AddLineToPoint(x + cr.topLeft, y + bt.top - 1);

            const double rx1 = cr.topLeft - bt.left;
            const double ry1 = cr.topLeft - bt.top;
            for (double angle = M_PI / 2; angle <= M_PI; angle += step)
            {
                const double dx = rx1 * cos(angle);
                const double dy = ry1 * sin(angle);
                wxPoint2DDouble p(x + cr.topLeft + dx - 1, y + cr.topLeft - dy - 1);
                path.AddLineToPoint(p);
            }

            path.AddLineToPoint(x + bt.left - 1, y + cr.topLeft);
            path.AddLineToPoint(x, y + cr.topLeft);
            gc->DrawPath(path);

            if (bt.top != 0)
            {
                gc->SetPen(wxPen(bc, bt.top));
                gc->StrokeLine(x + cr.topLeft, std::floor(bt.top / 2),
                    w - cr.topRight, std::floor(bt.top / 2));
            }
        }


        if (bt.top != 0 || bt.right != 0)
        {
            int pointCount = std::round(cr.topRight / 4);
            const double step = M_PI / (2 * pointCount);

            gc->SetBrush(bc);
            gc->SetPen(wxPen(bc, 1));

            wxGraphicsPath path = gc->CreatePath();
            path.AddArc(x + w - cr.topRight, y + cr.topRight,
                cr.topRight, -M_PI / 2, 0, true);
            path.AddLineToPoint(x + w - bt.right + 1, y + cr.topRight);

            const double rx2 = cr.topRight - bt.right;
            const double ry2 = cr.topRight - bt.top;
            for (double angle = 0; angle <= M_PI / 2; angle += step)
            {
                const double dx = rx2 * cos(angle);
                const double dy = ry2 * sin(angle);
                wxPoint2DDouble p(x + w - cr.topRight + dx + 1, y + cr.topRight - dy - 1);
                path.AddLineToPoint(p);
            }

            path.AddLineToPoint(x + w - cr.topRight, y + bt.top - 1);
            path.AddLineToPoint(x + w - cr.topRight, y);
            gc->DrawPath(path);

            if (bt.right != 0)
            {
                gc->SetPen(wxPen(bc, bt.right));
                gc->StrokeLine(w - std::ceil(bt.right / 2) + 1, cr.topRight,
                    w - std::ceil(bt.right / 2) + 1, h - cr.bottomRight);
            }
        }


        if (bt.right != 0 || bt.bottom != 0)
        {
            int pointCount = std::round(cr.bottomRight / 4);
            const double step = M_PI / (2 * pointCount);

            gc->SetBrush(bc);
            gc->SetPen(wxPen(bc, 1));

            wxGraphicsPath path = gc->CreatePath();
            path.AddArc(x + w - cr.bottomRight, y + h - cr.bottomRight,
                cr.bottomRight, 0, M_PI / 2, true);
            path.AddLineToPoint(x + w - cr.bottomRight, y + h - bt.bottom + 1);

            const double rx3 = cr.bottomRight - bt.right;
            const double ry3 = cr.bottomRight - bt.bottom;
            for (double angle = -M_PI / 2; angle <= 0; angle += step)
            {
                const double dx = rx3 * cos(angle);
                const double dy = ry3 * sin(angle);
                wxPoint2DDouble p(x + w - cr.bottomRight + dx + 1, y + h - cr.bottomRight - dy + 1);
                path.AddLineToPoint(p);
            }

            path.AddLineToPoint(x + w - bt.right + 1, y + h - cr.bottomRight);
            path.AddLineToPoint(x + w, y + h - cr.bottomRight);
            gc->DrawPath(path);

            if (bt.bottom != 0)
            {
                gc->SetPen(wxPen(bc, bt.bottom));
                gc->StrokeLine(w - cr.bottomRight, h - std::ceil(bt.bottom / 2) + 1,
                    cr.bottomLeft, h - std::ceil(bt.bottom / 2) + 1);
            }
        }


        if (bt.bottom != 0 || bt.left != 0)
        {
            int pointCount = std::round(cr.bottomLeft / 4);
            const double step = M_PI / (2 * pointCount);

            gc->SetBrush(bc);
            gc->SetPen(wxPen(bc, 1));

            wxGraphicsPath path = gc->CreatePath();
            path.AddArc(x + cr.bottomLeft, y + h - cr.bottomLeft,
                cr.bottomLeft, M_PI / 2, M_PI, true);
            path.AddLineToPoint(x + bt.left - 1, y + h - cr.bottomLeft);

            const double rx4 = cr.bottomLeft - bt.left;
            const double ry4 = cr.bottomLeft - bt.bottom;
            for (double angle = M_PI; angle <= 3 * M_PI / 2; angle += step)
            {
                const double dx = rx4 * cos(angle);
                const double dy = ry4 * sin(angle);
                wxPoint2DDouble p(x + cr.bottomLeft + dx - 1, y + h - cr.bottomLeft - dy + 1);
                path.AddLineToPoint(p);
            }

            path.AddLineToPoint(x + cr.bottomLeft - 1, y + h - bt.bottom + 1);
            path.AddLineToPoint(x + cr.bottomLeft, y + h);
            gc->DrawPath(path);

            if (bt.left != 0)
            {
                gc->SetPen(wxPen(bc, bt.left));
                gc->StrokeLine(std::floor(bt.left / 2), h - cr.bottomLeft,
                    std::floor(bt.left / 2), cr.topLeft);
            }
        }
    }
}
