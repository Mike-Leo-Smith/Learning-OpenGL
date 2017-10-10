#ifndef LEARNING_OPENGL_MATH_H
#define LEARNING_OPENGL_MATH_H

#include "Vector.h"

class Mathematics {
public:
    Mathematics() = delete;
    static Vector2D makeVector2D(float x = 0, float y = 0);
    static Vector3D makeVector3D(float x = 0, float y = 0, float z = 0);
    static Vector3D makeVector3D(const Vector2D &vector2d, float z = 0);
    static Vector4D makeVector4D(float x = 0, float y = 0, float z = 0, float w = 0);
    static Vector4D makeVector4D(const Vector2D &vector2d, float z = 0, float w = 0);
    static Vector4D makeVector4D(const Vector3D &vector3d, float w = 0);
};

#endif // LEARNING_OPENGL_MATH_H