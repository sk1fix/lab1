#pragma once
#include<picture.h>
using namespace picture;
int main()
{
    Images<int> img(5, 4, true);
    img.drawing(1, 1, 3, 3);
    img.printImage();
}