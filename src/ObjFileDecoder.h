#pragma once

#include <string>
#include <glm/glm.hpp>
#include <vector>

class ObjFileDecoder {
public:
    static ObjFileDecoder & getInstance();
    ObjFileDecoder(ObjFileDecoder const &) = delete;
    void operator=(ObjFileDecoder const &) = delete;

    void decode(const std::string & obj_filename,
                std::string & object_name,
                std::vector<glm::vec3> & positions,
                std::vector<glm::vec3> & normals,
                std::vector<glm::vec2> & uv_coords) const;

private:
    ObjFileDecoder();
};

