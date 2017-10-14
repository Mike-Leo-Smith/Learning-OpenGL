#ifndef LEARNING_OPENGL_VECTOR_H
#define LEARNING_OPENGL_VECTOR_H

#include <immintrin.h>

template<int Dim>
struct alignas(16) Vector;

template<>
struct alignas(16) Vector<2>
{
    union
    {
        __m128 _entries;
        
        struct
        {
            float x;
            float y;
        };
    };
};

template<>
struct alignas(16) Vector<3>
{
    union
    {
        __m128 _entries;
        
        struct
        {
            float x;
            float y;
            float z;
        };
    };
};

template<>
struct alignas(16) Vector<4>
{
    union
    {
        __m128 _entries;
        
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
    };
};

using Vector2 = Vector<2>;
using Vector3 = Vector<3>;
using Vector4 = Vector<4>;

#endif // LEARNING_OPENGL_VECTOR_H
