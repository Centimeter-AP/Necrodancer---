#pragma once
#include "pch.h"

class CDraw
{
public:
    static void RenderTransparentImage(HDC hdc, const WCHAR* imagePath, int left, int top, int fCX, int fCY, BYTE alpha)
    {
        Graphics graphics(hdc);
        Image image(imagePath);

        // Create an ImageAttributes object and set the alpha value
        ImageAttributes imgAttr;
        ColorMatrix colorMatrix = {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, alpha / 255.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        imgAttr.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

        // Draw the image with the specified alpha value
        graphics.DrawImage(&image, Rect(left, top, fCX, fCY), 0, 0, image.GetWidth(), image.GetHeight(), UnitPixel, &imgAttr);
    }
};
