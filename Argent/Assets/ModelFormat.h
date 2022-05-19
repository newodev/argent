#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace ag
{
    struct Vertex
    {
        glm::vec3 pos;
        glm::vec2 uv;
        // glm::vec3 norm
        // glm::vec3 tan;
        // glm::vec3 bitan;

        bool operator==(const Vertex& other) const
        {
            return pos == other.pos && uv == other.uv;
        }

        static VkVertexInputBindingDescription getBindingDescription()
        {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // Here we can change to per-instance mode

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
        {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT; // Size of the attribute. Vec3
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT; // Size of the attribute. Vec2
            attributeDescriptions[1].offset = offsetof(Vertex, uv);

            return attributeDescriptions;
        }
    };
}

// Vertex hash function so it can be used in unordered collections
namespace std
{
    template<> struct hash<ag::Vertex>
    {
        size_t operator()(ag::Vertex const& vertex) const
        {
            return (hash<glm::vec3>()(vertex.pos)) ^
                (hash<glm::vec2>()(vertex.uv) << 1);
        }
    };
}