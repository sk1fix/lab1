#pragma once
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>
using namespace std;
namespace picture {
    template <typename T>
    std::uniform_int_distribution<T> getDice(std::true_type)
    {
        return std::uniform_int_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }

    template <typename T>
    std::uniform_real_distribution<T> getDice(std::false_type)
    {
        return std::uniform_real_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }

    template <typename T>
    T random()
    {
        std::random_device randomDevice;
        std::mt19937_64 generator(randomDevice());
        auto dice = getDice<T>(std::integral_constant<bool, std::numeric_limits<T>::is_integer>());
        return dice(generator);
    }

    template <>
    inline char random<char>()
    {
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> distr('a', 'z');
        return (char)distr(gen);
    }

    template <>
    inline bool random<bool>()
    {
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> distr(0, 1);
        return distr(gen);
    }
    template <typename T>
    class Images
    {
    private:
        T** _image;
        int _x;
        int _y;

    public:
        Images(int x, int y, T* arr)
        {
            if (x <= 0 || y <= 0)
                throw runtime_error("Wrong size");
            _x = x;
            _y = y;
            _image = new T * [x];
            for (int i = 0; i < x; i++)
            {
                _image[i] = new T[y];
                for (int j = 0; j < y; j++)
                {
                    _image[i][j] = arr[i * x + j];
                }
            }
        }
        Images(int x, int y, bool rand)
        {
            if (x <= 0 || y <= 0)
                throw runtime_error("Wrong size");
            _x = x;
            _y = y;
            _image = new T * [x];
            for (int i = 0; i < x; i++)
            {
                _image[i] = new T[y];
                for (int j = 0; j < y; j++)
                {
                    if (rand == true)
                    {
                        _image[i][j] = random<T>();
                    }
                    else
                    {
                        _image[i][j] = 0;
                    }
                }
            }
        }
        int get_x()
        {
            return _x;
        }

        int get_y()
        {
            return _y;
        }
        T& operator () (int x, int y) const
        {
            return _image[x][y];
        }
        friend Images<T> operator* (const Images& first, const Images& second)
        {
            if (first._x != second._x || first._y != second._y)
                throw runtime_error("Different size");
            Images<T> m(first._x, first._y, false);
            for (int i = 0; i < first._x; i++)
            {
                for (int j = 0; j < first._y; j++)
                {
                    if (first._image[i][j] * second._image[i][j] > std::numeric_limits<T>::max())
                        m._image[i][j] = std::numeric_limits<T>::max();
                    else if (first._image[i][j] * second._image[i][j] < std::numeric_limits<T>::min())
                        m._image[i][j] = std::numeric_limits<T>::min();
                    else
                        m._image[i][j] = first._image[i][j] * second._image[i][j];
                }
            }
            return m;
        }
        friend Images<T> operator + (const Images& first, const Images& second)
        {
            if (first._x != second._x || first._y != second._y)
                throw runtime_error("Different size");
            Images<T> m(first._x, first._y, false);
            for (int i = 0; i < first._x; i++)
            {
                for (int j = 0; j < first._y; j++)
                {
                    if (first._image[i][j] + second._image[i][j] > std::numeric_limits<T>::max())
                        m._image[i][j] = std::numeric_limits<T>::max();
                    else if (first._image[i][j] + second._image[i][j] < std::numeric_limits<T>::min())
                        m._image[i][j] = std::numeric_limits<T>::min();
                    else
                        m._image[i][j] = first._image[i][j] + second._image[i][j];
                }
            }
            return m;
        }
        friend Images operator * (const Images& first, T constant)
        {
            Images<T> m(first._x, first._y, false);
            for (int i = 0; i < first._x; i++)
            {
                for (int j = 0; j < first._y; j++)
                {
                    if (first._image[i][j] * constant > std::numeric_limits<T>::max())
                        m._image[i][j] = std::numeric_limits<T>::max();
                    else if (first._image[i][j] * constant < std::numeric_limits<T>::min())
                        m._image[i][j] = std::numeric_limits<T>::min();
                    else
                        m._image[i][j] = first._image[i][j] * constant;
                }
            }
            return m;
        }
        friend Images<T> operator+(const Images& first, T constant)
        {
            Images<T> m(first._x, first._y, false);
            for (int i = 0; i < first._x; i++)
            {
                for (int j = 0; j < first._y; j++)
                {
                    if (first._image[i][j] + constant > std::numeric_limits<T>::max())
                        m._image[i][j] = std::numeric_limits<T>::max();
                    else if (first._image[i][j] + constant < std::numeric_limits<T>::min())
                        m._image[i][j] = std::numeric_limits<T>::min();
                    else
                        m._image[i][j] = first._image[i][j] + constant;
                }
            }
            return m;
        }
        float calculating_the_image_fill_factor()
        {
            float ctiff = 0;
            float max_value = _x * _y * std::numeric_limits<T>::max();
            for (int i = 0; i < _x; i++)
            {
                for (int j = 0; j < _y; j++)
                {
                    ctiff += _image[i][j] / max_value;
                }
            }
            return ctiff;
        }
        void printImage()
        {
            for (int i = 0; i < _x; i++)
            {
                for (int j = 0; j < _y; j++)
                {
                    cout << _image[i][j] << " ";
                }
                cout << endl;
            }
        }
        void drawing(int x1, int y1, int x2, int y2)
        {
            int pX = x1 - 1;
            int pY = y1 - 1;
            if (x2 > x1) {
                for (int i = x1 - 1; i < x2; i++)
                {
                    _image[i][pY] = 1;
                    if (y1 != y2)
                        pY += 1;
                }
            }
            else
            {
                for (int i = y1 - 1; i < y2; i++)
                {
                    _image[pX][i] = 1;
                }
            }
        }
    };
    template<typename T>
    Images<T> operator!(Images<T> first)
    {
        Images<T> m(first._x, first._y, false);
        for (int i = 0; i < first._x; i++)
        {
            for (int j = 0; j < first._y; j++)
            {
                m._image[i][j] = -first._image[i][j];
            }
        }
        return m;
    }
    template<>
    Images<bool> operator!(Images<bool> first)
    {
        Images<bool> m(first.get_x(), first.get_y(), false);
        for (int i = 0; i < first.get_x(); i++)
        {
            for (int j = 0; j < first.get_y(); j++)
            {
                if (first(i,j) == 1)
                    m(i, j) = 0;
                else
                    m(i, j) = 1;
            }
        }
        return m;
    }
    template<>
    Images<char> operator ! (Images<char> first)
    {
        Images<char> m(first.get_x(), first.get_y(), false);
        for (int i = 0; i < first.get_x(); i++)
        {
            for (int j = 0; j < first.get_y(); j++)
            {
                m(i, j) = 'a' + ('z' - first(i, j));
            }
        }
        return m;
    }
}