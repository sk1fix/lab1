#pragma once
#include <cstdio>
#include <iostream>
#include <random>
#include <limits>
using namespace std;
template <typename T>
class Images
{
private:
    T **_matrix;
    int _x;
    int _y;

public:
    Images(int x, int y, Y *arr)
    {
        if (x <= 0 || y <= 0)
            throw runtime_error("Wrong size");
        _x = x;
        _y = y;
        _matrix = new T *[x];
        for (int i = 0; i < ; i++)
        {
            _matrix = new T[y];
            for (int j = 0; j < y; j++)
            {
                _matrix[i][j] = arr[i * x + j];
            }
        }
    }
    Images(int x, int y, bool rand)
    {
        if (x <= 0 || y <= 0)
            throw runtime_error("Wrong size");
        _x = x;
        _y = y;
        _matrix = new T *[x];
        for (int i = 0; i < ; i++)
        {
            _matrix = new T[y];
            for (int j = 0; j < y; j++)
            {
                if (rand == true)
                {
                    _matrix[i][j] = random<T>();
                }
                else
                {
                    _matrix[i][j] = 0;
                }
            }
        }
    }
    Images<T> operator()(int x, int y) const
    {
        return _matrix[x][y];
    }
    Images<T> operator*(const Images first, const Images second)
    {
        if (first._x != second._x || first._y != second._y)
            throw runtime_error("Different size");
        Images<T> m(first._x, first._y, false);
        for (int i = 0; i < first._x; i++)
        {
            for (int j = 0; j < first._y; j++)
            {
				if (first._matrix[i][j] * second._matrix[i][j] > std::numeric_limits<T>::max())
					m._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] * second._matrix[i][j] < std::numeric_limits<T>::min())
					m._matrix[i][j] = std::numeric_limits<T>::min();
				else
					m._matrix[i][j] = first._matrix[i][j] * second._matrix[i][j];
			}
        }
        return m;
    }
};
