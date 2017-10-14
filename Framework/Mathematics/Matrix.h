//
// Created by Mike Smith on 14/10/2017.
//

#ifndef LEARNING_OPENGL_MATRIX_H
#define LEARNING_OPENGL_MATRIX_H

#include <immintrin.h>

template<int Rows, int Cols>
struct alignas(16) Matrix
{
    __m128 rows[Rows];
};

using Matrix2 = Matrix<2, 2>;
using Matrix3 = Matrix<3, 3>;
using Matrix4 = Matrix<4, 4>;

#endif  // LEARNING_OPENGL_MATRIX_H
