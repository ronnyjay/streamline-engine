#pragma once

#include <engine/Components/AABB.hpp>
#include <engine/Components/BSphere.hpp>

#include <glm/common.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>

namespace engine
{

struct CollisionResult
{
    glm::vec3 normal;

    // world coords.
    glm::vec3 localA; // position a + collision point
    glm::vec3 localB; // position b + collision point

    float penetration;

    bool collided;
};

struct CollisionVisitor
{
    CollisionResult operator()(const AABB &a, const AABB &b) const
    {
        CollisionResult result;

        bool intersectsX = a.Min().x <= b.Max().x && a.Max().x >= b.Min().x;
        bool intersectsY = a.Min().y <= b.Max().y && a.Max().y >= b.Min().y;
        bool intersectsZ = a.Min().z <= b.Max().z && a.Max().z >= b.Min().z;

        if (intersectsX && intersectsY && intersectsZ)
        {
            // clang-format off
            static const glm::vec3 faces[6] = {
                glm::vec3(-1.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, -1.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, -1.0f),
                glm::vec3(0.0f, 0.0f, 1.0f)
                
            };

            float distances[6] = {
                (b.Max().x - a.Min().x),
                (a.Max().x - b.Min().x),
                (b.Max().y - a.Min().y),
                (a.Max().y - b.Min().y),
                (b.Max().z - a.Min().z),
                (a.Max().z - b.Min().z)
            };
            // clang-format on

            result.penetration = FLT_MAX;

            for (int i = 0; i < 6; i++)
            {
                if (distances[i] < result.penetration)
                {
                    result.penetration = distances[i];
                    result.normal = faces[i];
                }
            }

            result.localA = a.Center();
            result.localB = b.Center();
            result.collided = true;
        }
        else
        {
            result.collided = false;
        }

        return result;
    }

    CollisionResult operator()(const BSphere &a, const BSphere &b) const
    {
        CollisionResult result;

        float radii = a.Radius() + b.Radius();
        glm::vec3 delta = b.Center() - a.Center();

        if (glm::length(delta) < radii)
        {
            result.penetration = radii - glm::length(delta);
            result.normal = glm::normalize(delta);
            result.localA = a.Center() + result.normal * a.Radius();
            result.localB = b.Center() - result.normal * b.Radius();
            result.collided = true;
        }
        else
        {
            result.collided = false;
        }

        return result;
    }

    CollisionResult operator()(const AABB &a, const BSphere &b) const
    {
        CollisionResult result;

        glm::vec3 delta = b.Center() - a.Center();

        glm::vec3 closestPoint = glm::clamp(delta, -a.HalfDimensions(), a.HalfDimensions());
        glm::vec3 localPoint = delta - closestPoint;

        float distance = glm::length(localPoint);

        if (distance < b.Radius())
        {
            result.normal = glm::normalize(localPoint);
            result.penetration = b.Radius() - distance;
            result.localA = a.Center();
            result.localB = b.Center();
            result.collided = true;
        }
        else
        {
            result.collided = false;
        }

        return result;
    }

    CollisionResult operator()(const BSphere &a, const AABB &b) const
    {
        CollisionResult result;

        glm::vec3 delta = a.Center() - b.Center();

        glm::vec3 closestPoint = glm::clamp(delta, -b.HalfDimensions(), b.HalfDimensions());
        glm::vec3 localPoint = delta - closestPoint;

        float distance = glm::length(localPoint);

        if (distance < a.Radius())
        {
            result.normal = glm::normalize(localPoint);
            result.penetration = distance - a.Radius();
            result.localA = a.Center();
            result.localB = b.Center();
            result.collided = true;
        }
        else
        {
            result.collided = false;
        }

        return result;
    }
};

} // namespace engine