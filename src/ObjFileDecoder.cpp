#include "ObjFileDecoder.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>

ObjFileDecoder & ObjFileDecoder::getInstance() {
    static ObjFileDecoder instance;
    return instance;
}

void ObjFileDecoder::decode(const std::string & obj_filename,
                            std::string & object_name,
                            std::vector<glm::vec3> & positions,
                            std::vector<glm::vec3> & normals,
                            std::vector<glm::vec2> & uv_coords) const
{
    // Empty containers, and start fresh before inserting data from .obj file
    positions.clear();
    normals.clear();
    uv_coords.clear();

    std::ifstream in(obj_filename, std::ios::in);
    in.exceptions(std::ifstream::badbit);
    if (!in) {
        std::stringstream err;
        err << "Unable to open .obj file " << obj_filename << std::endl;
        throw std::runtime_error(err.str());
    }

    std::string curr_line;
    int pos_idx_A, pos_idx_B, pos_idx_C;
    int normal_idx_A, normal_idx_B, normal_idx_C;
    int uv_coord_idx_A, uv_coord_idx_B, uv_coord_idx_C;
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_uv_coords;

    object_name = "";

    while (!in.eof()) {
        try {
            getline(in, curr_line);
        } catch (const std::ifstream::failure &e) {
            in.close();
            std::stringstream err;
            err << "Error calling getline() -- " << e.what() << std::endl;
            throw std::runtime_error(err.str());
        }
        if (curr_line.substr(0, 2) == "o ") {
            // Get entire line excluding first 2 chars.
            std::istringstream s(curr_line.substr(2));
            s >> object_name;
        } else if (curr_line.substr(0, 2) == "v ") {
            // Vertex data on this line.
            // Get entire line excluding first 2 chars.
            std::istringstream s(curr_line.substr(2));
            glm::vec3 vertex;
            s >> vertex.x;
            s >> vertex.y;
            s >> vertex.z;
            temp_positions.push_back(vertex);
        } else if (curr_line.substr(0, 3) == "vn ") {
            // Normal data on this line.
            // Get entire line excluding first 2 chars.
            std::istringstream s(curr_line.substr(2));
            glm::vec3 normal;
            s >> normal.x;
            s >> normal.y;
            s >> normal.z;
            temp_normals.push_back(normal);
        } else if (curr_line.substr(0, 3) == "vt ") {
            // Texture coordinate data on this line.
            // Get entire line excluding first 2 chars.
            std::istringstream s(curr_line.substr(2));
            glm::vec2 textureCoord;
            s >> textureCoord.s;
            s >> textureCoord.t;
            temp_uv_coords.push_back(textureCoord);
        } else if (curr_line.substr(0, 2) == "f ") {
            // Face index data on this line.
            int index;

            // sscanf will return the number of matched index values it found
            // from the pattern.
            int num_idx_matches = sscanf(curr_line.c_str(), "f %d/%d/%d", &index, &index, &index);
            if (num_idx_matches == 3) {
                // Line contains indices of the pattern vertex/uv-cord/normal.
                sscanf(curr_line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                       &pos_idx_A, &uv_coord_idx_A, &normal_idx_A,
                       &pos_idx_B, &uv_coord_idx_B, &normal_idx_B,
                       &pos_idx_C, &uv_coord_idx_C, &normal_idx_C);

                // .obj file uses indices that start at 1, so subtract 1 so they start at 0.
                uv_coord_idx_A--;
                uv_coord_idx_B--;
                uv_coord_idx_C--;

                uv_coords.push_back(temp_uv_coords[uv_coord_idx_A]);
                uv_coords.push_back(temp_uv_coords[uv_coord_idx_B]);
                uv_coords.push_back(temp_uv_coords[uv_coord_idx_C]);
            } else {
                // Line contains indices of the pattern vertex//normal.
                sscanf(curr_line.c_str(), "f %d//%d %d//%d %d//%d",
                       &pos_idx_A, &normal_idx_A,
                       &pos_idx_B, &normal_idx_B,
                       &pos_idx_C, &normal_idx_C);
            }

            pos_idx_A--;
            pos_idx_B--;
            pos_idx_C--;
            normal_idx_A--;
            normal_idx_B--;
            normal_idx_C--;

            positions.push_back(temp_positions[pos_idx_A]);
            positions.push_back(temp_positions[pos_idx_B]);
            positions.push_back(temp_positions[pos_idx_C]);

            normals.push_back(temp_normals[normal_idx_A]);
            normals.push_back(temp_normals[normal_idx_B]);
            normals.push_back(temp_normals[normal_idx_C]);
        }
    }

    in.close();

    if (object_name.compare("") == 0) {
        // No 'o' object name tag defined in .obj file, so use the file name
        // minus the '.obj' ending as the object_name.
        const char * ptr = strrchr(obj_filename.c_str(), '/');
        object_name.assign(ptr + 1);
        const size_t pos = object_name.find('.');
        object_name.resize(pos);
    }
}

ObjFileDecoder::ObjFileDecoder() {}

