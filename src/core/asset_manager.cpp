#include <fstream>
#include <iris/core/asset_manager.hpp>
#include "error.hpp"
#include "lib/stb_image.h"

namespace iris {
    asset_manager::asset_manager(struct config config) noexcept {
        this->config = config;
    }

    void asset_manager::intl_load_texture(const std::vector<u8> &data, const std::string &key) noexcept {
        i32 width, height;
        i32 channels;
        u8 *pixel_data = stbi_load_from_memory(data.data(), data.size(), &width, &height, &channels, 0);

        struct texture texture;
        texture.width = width;
        texture.height = height;
        texture.channels = channels;
        size_t sz = width * height * channels;
        texture.data.reserve(sz);
        texture.data.insert(texture.data.begin(), pixel_data, pixel_data + sz);
    }

    void asset_manager::load_texture(const std::vector<u8> &data, const std::string &key) noexcept {
        if (data.size() == 0) {
            iris::error(error_code::malformed_input, "Input data vector size() was 0 bytes");
            return;
        }
        this->intl_load_texture(data, key);
    }

    void asset_manager::load_texture(const std::filesystem::path &path, const std::string &key) noexcept {
        if (!std::filesystem::exists(path)) {
            iris::error(error_code::file_not_found, path.string());
            return;
        }

        std::ifstream file(path);

        if (!file.is_open()) {
            iris::error(error_code::filesystem_error);
            return;
        }

        file.seekg(0, std::ios::end);
        std::vector<u8> data;
        data.resize(file.tellg());
        file.seekg(0, std::ios::beg);

        file.read((char*) data.data(), data.size());
        file.close();
    }

    texture& asset_manager::texture(const std::string &key) noexcept {}

    asset_manager::~asset_manager() {}
}
