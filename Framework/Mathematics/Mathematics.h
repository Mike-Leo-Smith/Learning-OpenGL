#ifndef LEARNING_OPENGL_MATHEMATICS_H
#define LEARNING_OPENGL_MATHEMATICS_H

#include "immintrin.h"
#include "Vector.h"

#define FUNC_ATTRS __attribute__((always_inline, nodebug))

namespace math
{
    inline Vector2D FUNC_ATTRS makeVector2D(float x = 0, float y = 0)
    {
        return Vector2D { ._entries = _mm_setr_ps(x, y, 0, 0) };
    }
    
    inline Vector2D FUNC_ATTRS makeVector2D(const Vector2D &vector2d)
    {
        return vector2d;
    }
    
    inline Vector2D FUNC_ATTRS makeVector2D(const Vector3D &vector3d)
    {
        return Vector2D { ._entries = vector3d._entries };
    }
    
    inline Vector2D FUNC_ATTRS makeVector2D(const Vector4D &vector4d)
    {
        return Vector2D { ._entries = vector4d._entries };
    }
    
    inline Vector3D FUNC_ATTRS makeVector3D(float x = 0, float y = 0, float z = 0)
    {
        return Vector3D { ._entries = _mm_setr_ps(x, y, z, 0) };
    }
    
    inline Vector3D FUNC_ATTRS makeVector3D(const Vector2D &vector2d, float z = 0)
    {
        return Vector3D { ._entries = _mm_setr_ps(vector2d.x, vector2d.y, z, 0) };
    }
    
    inline Vector3D FUNC_ATTRS makeVector3D(const Vector3D &vector3d)
    {
        return vector3d;
    }
    
    inline Vector3D FUNC_ATTRS makeVector3D(const Vector4D &vector4d)
    {
        return Vector3D { ._entries = vector4d._entries };
    }
    
    inline Vector4D FUNC_ATTRS makeVector4D(float x = 0, float y = 0, float z = 0, float w = 0)
    {
        return Vector4D { ._entries = _mm_setr_ps(x, y, z, w) };
    }
    
    inline Vector4D FUNC_ATTRS makeVector4D(const Vector2D &vector2d, float z = 0, float w = 0)
    {
        return Vector4D { ._entries = _mm_setr_ps(vector2d.x, vector2d.y, z, w) };
    }
    
    inline Vector4D FUNC_ATTRS makeVector4D(const Vector3D &vector3d, float w = 0)
    {
        return Vector4D { ._entries = _mm_setr_ps(vector3d.x, vector3d.y, vector3d.z, w) };
    }
    
    inline Vector4D FUNC_ATTRS makeVector4D(const Vector4D &vector4d)
    {
        return vector4d;
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS unary_plus(const Vector<Dim> &v)
    {
        return v;
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS unary_minus(Vector<Dim> v)
    {
        return Vector<Dim> { ._entries = _mm_mul_ps(_mm_set_ps1(-1.0f), v._entries) };
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS add(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
    {
        return Vector<Dim> { ._entries = _mm_add_ps(lhs._entries, rhs._entries) };
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS subtract(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
    {
        return Vector<Dim> { ._entries = _mm_sub_ps(lhs._entries, rhs._entries) };
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS multiply(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
    {
        return Vector<Dim> { ._entries = _mm_mul_ps(lhs._entries, rhs._entries) };
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS multiply(const Vector<Dim> &lhs, float &rhs)
    {
        return Vector<Dim> { ._entries = _mm_mul_ps(lhs._entries, _mm_set_ps1(rhs)) };
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS multiply(float lhs, const Vector<Dim> &rhs)
    {
        return Vector<Dim> { ._entries = _mm_mul_ps(_mm_set_ps1(lhs), rhs._entries) };
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS divide(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
    {
        return Vector<Dim> { ._entries = _mm_div_ps(lhs._entries, rhs._entries) };
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS divide(const Vector<Dim> &lhs, float rhs)
    {
        return Vector<Dim> { ._entries = _mm_div_ps(lhs._entries, _mm_set_ps1(rhs)) };
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS divide(float lhs, const Vector<Dim> &rhs)
    {
        return Vector<Dim> { ._entries = _mm_div_ps(_mm_set_ps1(lhs), rhs._entries) };
    }
    
    template<int Dim>
    inline float FUNC_ATTRS norm(const Vector<Dim> &v)
    {
        constexpr int mask = ((Dim == 4) << 7) | ((Dim >= 3) << 6) | ((Dim >= 2) << 5) | 0b00010001;
        return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v._entries, v._entries, mask)));
    }
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS normalized_approx(const Vector<Dim> v)
    {
        constexpr int mask = ((Dim == 4) << 7) | ((Dim >= 3) << 6) | ((Dim >= 2) << 5) | 0b00011111;
        return Vector<Dim> { ._entries = _mm_mul_ps(
            v._entries, _mm_rsqrt_ps(_mm_dp_ps(v._entries, v._entries, mask))) };
    };
    
    template<int Dim>
    inline Vector<Dim> FUNC_ATTRS normalized(const Vector<Dim> v)
    {
        constexpr int mask = ((Dim == 4) << 7) | ((Dim >= 3) << 6) | ((Dim >= 2) << 5) | 0b00011111;
        return Vector<Dim> {
            ._entries = _mm_div_ps(v._entries, _mm_sqrt_ps(_mm_dp_ps(v._entries, v._entries, mask))) };
    };
    
    template<int Dim>
    inline float FUNC_ATTRS dot(const Vector<Dim> &lhs, const Vector<Dim> &rhs)
    {
        constexpr int mask = ((Dim == 4) << 7) | ((Dim >= 3) << 6) | ((Dim >= 2) << 5) | 0b00010001;
        return _mm_cvtss_f32(_mm_dp_ps(lhs._entries, rhs._entries, mask));
    }
    
    inline Vector3D FUNC_ATTRS cross(const Vector3D &lhs, const Vector3D &rhs)
    {
        return Vector3D { ._entries = _mm_sub_ps(
            _mm_mul_ps(_mm_shuffle_ps(lhs._entries, lhs._entries, _MM_SHUFFLE(3, 0, 2, 1)),
                       _mm_shuffle_ps(rhs._entries, rhs._entries, _MM_SHUFFLE(3, 1, 0, 2))),
            _mm_mul_ps(_mm_shuffle_ps(lhs._entries, lhs._entries, _MM_SHUFFLE(3, 1, 0, 2)),
                       _mm_shuffle_ps(rhs._entries, rhs._entries, _MM_SHUFFLE(3, 0, 2, 1)))) };
    };
}; // namespace math

template<typename T>
inline auto FUNC_ATTRS operator+(const T &t)
{
    return math::unary_plus(t);
};

template<typename T>
inline auto FUNC_ATTRS operator-(const T &t)
{
    return math::unary_minus(t);
};

template<typename Tl, typename Tr>
inline auto FUNC_ATTRS operator+(const Tl &lhs, const Tr &rhs)
{
    return math::add(lhs, rhs);
};

template<typename Tl, typename Tr>
inline auto FUNC_ATTRS operator-(const Tl &lhs, const Tr &rhs)
{
    return math::subtract(lhs, rhs);
};

template<typename Tl, typename Tr>
inline auto FUNC_ATTRS operator*(const Tl &lhs, const Tr &rhs)
{
    return math::multiply(lhs, rhs);
};

template<typename Tl, typename Tr>
inline auto FUNC_ATTRS operator/(const Tl &lhs, const Tr &rhs)
{
    return math::divide(lhs, rhs);
};

#endif // LEARNING_OPENGL_MATHEMATICS_H
