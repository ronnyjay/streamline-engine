#pragma once

#include "engine/Components/Bone.hpp"
#include "engine/Components/Model.hpp"
#include <glm/matrix.hpp>
#include <assimp/Importer.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace engine
{

struct AssimpNodeData
{
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
};

class Animation
{
public:
    Animation() = default;

    Animation(const std::basic_string<char>& animationPath, std::shared_ptr<Model> model);

    ~Animation()
    {
    }

    Bone* FindBone(const std::string& name);

	
    inline float GetTicksPerSecond() { return m_TicksPerSecond; }

    inline float GetDuration() { return m_Duration;}

    inline const AssimpNodeData& GetRootNode() { return m_RootNode; }

    inline const std::unordered_map<std::string,BoneInfo>& GetBoneIDMap() 
    { 
        return m_BoneInfoMap;
    }

private:
    void ReadMissingBones(const aiAnimation* animation, Model& model);

    void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);
    float m_Duration;
    int m_TicksPerSecond;
    std::vector<Bone> m_Bones;
    AssimpNodeData m_RootNode;
    std::unordered_map<std::string, BoneInfo> m_BoneInfoMap;
};

};
