#pragma once
#include <cstdint>
#include <Raylib/raylib.h>

namespace RE
{
    class FrameBuffer
    {
    public :
        FrameBuffer() = default;
        FrameBuffer(std::uint32_t width, std::uint32_t height);

        void render();

        RenderTexture2D target;
        std::uint32_t width;
        std::uint32_t height;

    private :
        
    };
}