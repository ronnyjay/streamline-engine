#pragma once

#include <engine/Components/Animation.hpp>

namespace engine
{

class Animator
{
  public:
    Animator(std::shared_ptr<Animation> animation);

    void UpdateAnimation(float dt);

    void PlayAnimation(std::shared_ptr<Animation> pAnimation);

    void CalculateBoneTransform(const AssimpNodeData *node, glm::mat4 parentTransform);

    std::vector<glm::mat4> GetFinalBoneMatrices()
    {
        return m_FinalBoneMatrices;
    }

  private:
    std::vector<glm::mat4> m_FinalBoneMatrices;
    std::shared_ptr<Animation> m_CurrentAnimation;
    float m_CurrentTime;
    float m_DeltaTime;
};

}; // namespace engine
