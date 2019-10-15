#include "pch.h"
#include "RenderJob.h"

RenderJob::RenderJob(
	string texture, 
	Vector2 start, 
	Vector2 end,
	bool alpha, 
	Vector2 textureSampleOffset, 
	bool wrapTextureX, 
	bool wrapTextureY
) :
	Texture(texture), 
	Start(start),
	End(end),
	Normal((End - Start).Right().Normalized()),
	Length((End - Start).Length()),
	Alpha(alpha), 
	TextureSampleOffset(textureSampleOffset),
	WrapTextureX(wrapTextureX), 
	WrapTextureY(wrapTextureY),
	Depth(0.0)
{
}