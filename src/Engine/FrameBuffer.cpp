#include "FrameBuffer.hpp"
#include "../Settings.hpp"

RE::FrameBuffer::FrameBuffer(std::uint32_t width, std::uint32_t height) : target(LoadRenderTexture(width, height))
{
	this->width = width;
	this->height = height;
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
}

void RE::FrameBuffer::render()
{
	DrawTexturePro(target.texture,
		{ 0, 0, (float)width,  -(float)height },
		{ 0, 0, (float)Settings::width, (float)Settings::height },
		Vector2(0, 0),
		0,
		WHITE
	);
}