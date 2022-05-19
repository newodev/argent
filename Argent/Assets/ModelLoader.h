#pragma once

#include <Vertex.h>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <unordered_map>
#include <string>

namespace ag
{
	namespace asset
	{
		void LoadModel(std::vector<Vertex>* vertices, std::vector<uint32_t>* indices, std::string path)
        {
            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::string warn, err;

            /// \TODO: Use a different map type. This is not optimal
            std::unordered_map<Vertex, uint32_t> uniqueVertices{};

            if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str()))
            {
                throw std::runtime_error(warn + err);
            }

            for (const auto& shape : shapes)
            {
                for (const auto& index : shape.mesh.indices)
                {
                    Vertex vertex{};

                    vertex.pos = {
                        attrib.vertices[3 * index.vertex_index + 0],
                        attrib.vertices[3 * index.vertex_index + 1],
                        attrib.vertices[3 * index.vertex_index + 2]
                    };

                    vertex.uv = {
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                    };

                    if (uniqueVertices.count(vertex) == 0) {
                        uniqueVertices[vertex] = static_cast<uint32_t>(vertices->size());
                        vertices->push_back(vertex);
                    }

                    indices->push_back(uniqueVertices[vertex]);
                }
            }
        }
	}
}