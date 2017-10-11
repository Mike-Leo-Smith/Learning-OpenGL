#include <iostream>
#include "Framework/Mathematics/Mathematics.h"
#include "ThirdParty/GLM/glm.hpp"

struct V
{
    float x;
    float y;
    float z;
    float w;
};

inline V FUNC_ATTRS operator-(const V &v)
{
    return V { -v.x, -v.y, -v.z, -v.w };
}

inline V FUNC_ATTRS operator+(const V &v)
{
    return v;
}

inline V FUNC_ATTRS operator+(V lhs, const V &rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    lhs.w += rhs.w;
    return lhs;
}

inline V FUNC_ATTRS operator*(V lhs, const V &rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    lhs.z *= rhs.z;
    lhs.w *= rhs.w;
    return lhs;
}

inline V FUNC_ATTRS operator/(V lhs, float rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    lhs.w /= rhs;
    return lhs;
}

int main()
{
    auto v = math::makeVector4D(1.0f, 2.0f, 3.0f, 4.0f);
    auto t = math::makeVector2D(0.5f, 0.4f);
    glm::vec4 vv = { 1.0f, 2.0f, 3.0f, 4.0f };
    V vvv = { 1.0f, 2.0f, 3.0f, 4.0f };
    
    std::cout << math::dot(v, v) << std::endl;
    
    auto t0 = clock();
    for (auto i = 0; i < 100000001; i++) {
//        vv = vv / 1.1f;
//        v = v + v;
//        vvv = vvv + vvv;
//        v = v * v;
//        vv = vv + vv;
//        v = v / 1.1f;
//        vvv = vvv / 1.1f;
//        v = math::unary_minus(v);
//        v = v / 1.0f;
//        vvv = -vvv;
//        vvv = vvv * vvv;
//        v = v * v;
//        vvv = vvv + vvv;
//        vvv = -vvv;
//        vvv = +vvv;
//        vv = -vv;
//        v = +v;
//        v = v + v;
//        v._entries = -v._entries;
//        v = math::unary_minus(v);
//        v._entries = _mm_mul_ps(_mm_set_ps1(-1.0f), v._entries);
//        v._entries = _mm_set_ps1(-1.0f) * v._entries;
        v = math::makeVector4D(t, 1.3f, 1.2f);
//        v = math::normalized_approx(v);
//        vv = glm::normalize(vv);
    }
    auto t1 = clock();
    
    std::cout << t1 - t0 << std::endl;
    
    std::cout << v.x << " " << v.y << " " << v.z << " " << v.w << std::endl;
    std::cout << vv.x << " " << vv.y << " " << vv.z << " " << vv.w << std::endl;
    std::cout << vvv.x << " " << vvv.y << " " << vvv.z << " " << vvv.w << std::endl;
    std::cout << math::norm(v) << std::endl;
    std::cout << vv.length() << std::endl;
    
    return 0;
}
