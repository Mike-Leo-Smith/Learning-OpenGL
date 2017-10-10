#include "Mathematics.h"

Vector2D Mathematics::makeVector2D(float x = 0, float y = 0) {
    return Vector2D{x, y};
}

Vector3D Mathematics::makeVector3D(float x = 0, float y = 0, float z = 0) {
    return Vector3D{x, y, z};
}

Vector3D Mathematics::makeVector3D(const Vector2D &vector2d, float z = 0) {
    return Vector3D{vector2d.x, vector2d.y, z};
}

Vector4D Mathematics::makeVector4D(float x = 0, float y = 0, float z = 0, float w = 0) {
    return Vector4D{x, y, z, w};
}

Vector4D Mathematics::makeVector4D(const Vector2D &vector2d, float z = 0, float w = 0) {
    return Vector4D{vector2d.x, vector2d.y, z, w};
}

Vector4D Mathematics::makeVector4D(const Vector3D &vector3d, float w = 0) {
    return Vector4D{vector3d.x, vector3d.y, vector3d.z, w};
}
