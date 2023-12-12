#pragma once
#include<picture.h>
using namespace picture;
int main()
{
    Images<bool> img(4, 4, true);
    img.drawing(1, 2, 3, 4);
    img.printImage();
}