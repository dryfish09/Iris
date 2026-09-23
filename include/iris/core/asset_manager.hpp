#pragma once

#include "nutils/types.hpp"
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace iris {
    struct texture {
        friend class asset_manager;
    private:
        std::vector<u8> data;
        u32 width = 0;
        u32 height = 0;
        u32 channels = 0;
    };

    class asset_manager {
    public:
        struct config {
            bool auto_unload : 1;

            config() noexcept
                : auto_unload(false)
            {}
        };
    private:
        std::unordered_map<std::string, texture> registered_textures;
        config config;

        void intl_load_texture(const std::vector<u8> &data, const std::string &key) noexcept;
    public:
        void load_texture(const std::filesystem::path &path, const std::string &key) noexcept;
        void load_texture(const std::vector<u8> &data, const std::string &key) noexcept;
        texture& texture(const std::string &key) noexcept;

        asset_manager(struct config config = {}) noexcept;
        ~asset_manager();
    };
}
