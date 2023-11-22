#pragma once
#include<random>
namespace halftone_image{
    template <typename T>
    class Images{
        private:
            T** _matrix;
        public:
            Images(int x, int y, bool random);
            T* operator(int i, int j);
            Images operator *(const Images& other);
            Images operator !();
    }
}
