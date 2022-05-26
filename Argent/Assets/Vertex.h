#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <vulkan/vulkan.hpp>

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

        static vk::VertexInputBindingDescription getBindingDescription()
        {
            vk::VertexInputBindingDescription bindingDesc(
                0,
                sizeof(Vertex),
                vk::VertexInputRate::eVertex  // Here we can change to per-instance mode
            );

            return bindingDesc;
        }

        static std::array<vk::VertexInputAttributeDescription, 2> getAttributeDescriptions()
        {
            std::array<vk::VertexInputAttributeDescription, 2> attributeDescs{};
            attributeDescs[0] = vk::VertexInputAttributeDescription(
                0, // Binding
                0, // Location
                vk::Format::eR32G32B32Sfloat, // Format (3 dimensions)
                offsetof(Vertex, pos)
            );
            attributeDescs[0] = vk::VertexInputAttributeDescription(
                0, // Binding
                1, // Location
                vk::Format::eR32G32Sfloat, // Format (2 dimensions)
                offsetof(Vertex, uv)
            );

            return attributeDescs;
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