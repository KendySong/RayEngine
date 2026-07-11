#include "FrameBuffer.hpp"

RE::FrameBuffer::FrameBuffer(std::uint32_t width, std::uint32_t height) : target(LoadRenderTexture(width, height))
{
	this->width = width;
	this->height = height;
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
}