#pragma once
#include <unordered_map>
#include <string>

#include <raylib/raylib.h>

#include "Model/ShaderSkeleton.hpp"
#include "Animator.hpp"

namespace RE
{
    class AssetManager
    {
    public:
        static AssetManager& instance();
        std::unordered_map<std::string, Texture2D> texture;
        std::unordered_map<std::string, Model> model;
        std::unordered_map<std::string, RE::Animator> animator;
        std::unordered_map<std::string, ShaderSkeleton*> shader;

        void setModeleTexture(const std::string& name, int mapType, const Texture2D& texture);
        void setMaterialShader(const std::string& name, const Shader& shader);

    private:
        AssetManager() = default;
        static AssetManager s_intance;
    };
}
