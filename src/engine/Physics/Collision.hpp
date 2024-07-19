#pragma once

#include <algorithm>
#include <engine/Components/AABB.hpp>
#include <engine/Components/BSphere.hpp>

#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>

namespace engine
{

struct CollisionResult
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::float32 penetration;
};

struct IntersectionVisitor
{
    bool operator()(const AABB &a, const AABB &b) const
    {
        bool intersectsX = a.Min().x <= b.Max().x && a.Max().x >= b.Min().x;
        bool intersectsY = a.Min().y <= b.Max().y && a.Max().y >= b.Min().y;
        bool intersectsZ = a.Min().z <= b.Max().z && a.Max().z >= b.Min().z;

        return intersectsX && intersectsY && intersectsZ;
    }

    bool operator()(const BSphere &a, const BSphere &b) const
    {
        float radii = a.Radius() + b.Radius();
        glm::vec3 delta = b.Center() - a.Center();

        return glm::length(delta) < radii;
    }

    bool operator()(const AABB &a, const BSphere &b) const
    {
        glm::vec3 closestPoint;

        closestPoint.x = std::max(a.Min().x, std::min(b.Center().x, a.Max().x));
        closestPoint.y = std::max(a.Min().y, std::min(b.Center().y, a.Max().y));
        closestPoint.z = std::max(a.Min().z, std::min(b.Center().z, a.Max().z));

        glm::vec3 delta = closestPoint - b.Center();

        return glm::length(delta) < b.Radius();
    }

    bool operator()(const BSphere &a, const AABB &b) const
    {
        return (*this)(b, a);
    }
};

struct CollisionVisitor
{
    CollisionResult operator()(const AABB &a, const AABB &b)
    {
        CollisionResult result;

        glm::vec3 minA = a.Min();
        glm::vec3 minB = b.Min();

        glm::vec3 maxA = a.Max();
        glm::vec3 maxB = b.Max();

        glm::vec3 halfWidthA = (maxA - minA) * 0.5f;
        glm::vec3 halfWidthB = (maxB - minB) * 0.5f;

        glm::vec3 centerA = (maxA + minA) * 0.5f;
        glm::vec3 centerB = (maxB + minB) * 0.5f;

        glm::vec3 difference = (centerB - centerA);
        glm::vec3 overlap = halfWidthA + halfWidthB - glm::abs(difference);

        if (overlap.x < overlap.y && overlap.y < overlap.z)
        {
            result.normal = glm::vec3(1.0f, 0.0f, 0.0f);
            result.position = glm::vec3(centerA.x + glm::sign(difference.x) * halfWidthA.x, centerB.y, centerB.z);
        }
        else if (overlap.y < overlap.z)
        {
            result.normal = glm::vec3(0.0f, 1.0f, 0.0f);
            result.position = glm::vec3(centerB.x, centerA.y + glm::sign(difference.y) * halfWidthA.y, centerB.z);
        }
        else
        {
            result.normal = glm::vec3(0.0f, 0.0f, 1.0f);
            result.position = glm::vec3(centerB.x, centerB.y, centerA.z + glm::sign(difference.z) * halfWidthA.z);
        }

        if (glm::dot(difference, result.normal) < 0.0f)
        {
            result.normal = -result.normal;
        }

        result.penetration = glm::min(overlap.x, glm::min(overlap.y, overlap.z));

        return result;
    }

    CollisionResult operator()(const BSphere &a, const BSphere &b)
    {
        CollisionResult result;

        float radii = a.Radius() + b.Radius();
        glm::vec3 delta = b.Center() - a.Center();

        result.normal = glm::normalize(delta);
        result.penetration = radii - glm::length(delta);
        result.position = a.Center() + result.normal * b.Radius() + result.normal;

        return result;
    }

    CollisionResult operator()(const AABB &a, const BSphere &b)
    {
        CollisionResult result;

        result.position.x = std::max(a.Min().x, std::min(b.Center().x, a.Max().x));
        result.position.y = std::max(a.Min().y, std::min(b.Center().y, a.Max().y));
        result.position.z = std::max(a.Min().z, std::min(b.Center().z, a.Max().z));

        glm::vec3 delta = result.position - b.Center();

        if (glm::dot(delta, delta) != 0.0f)
        {
            result.normal = glm::normalize(delta);
        }
        // Centers of each object are on top of eachother, NaN
        else
        {
            result.normal = glm::vec3(1.0f, 0.0f, 0.0f);
        }

        result.penetration = b.Radius() - glm::length(delta);

        return result;
    }

    CollisionResult operator()(const BSphere &a, const AABB &b)
    {
        return (*this)(b, a);
    }
};

} // namespace engine