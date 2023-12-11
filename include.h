#pragma once
#include <cstdio>
#include <iostream>
#include <random>
using namespace std;
template <typename T>
class Images{
private:
    T** _matrix;
    int _x;
    int _y;
public:
    Images(int x, int y, Y* arr){
        if (x <= 0 || y <= 0)
            throw runtime_error('wrong size');
        _x = x;
        _y = y;
        _matrix = new T * [x];
        for (int i = 0; i < ; i++){
            _matrix = new T[y];
            for (int j = 0; j < y; j++){
                _matrix[i][j] = arr[i * x + j];
            }
        }
    }
    Images(int x, int y,bool rand){
        if (x <= 0 || y <= 0)
            throw runtime_error('wrong size');
        _x = x;
        _y = y;
        _matrix = new T * [x];
        for (int i = 0; i < ; i++){
            _matrix = new T[y];
            for (int j = 0; j < y; j++){
                if (rand==true){
                    _matrix[i][j]=random<T>();
                }
                else{
                    _matrix[i][j]=0;
                }
            }
        }
    }
    
};
