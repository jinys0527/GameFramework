#pragma once
#include "Component.h"
#include "wrl/client.h"
#include "SimpleMathHelper.h"

class ID2D1Bitmap1;

enum class SpritePivotPreset
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	Center
};

class SpriteRenderer : public Component
{
	using Vec2F = Math::Vector2F;
public:
	SpriteRenderer(SpritePivotPreset spp, const D2D1_SIZE_F& size);
	virtual ~SpriteRenderer() = default;

	void SetTexture(Microsoft::WRL::ComPtr<ID2D1Bitmap1> texture);
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> GetTexture() const;

	void SetFlipX(bool flipX);
	bool GetFlipX() const;

	void SetFlipY(bool flipY);
	bool GetFlipY() const;

	const Vec2F& GetPivot() const
	{
		return m_pivot;
	}

private:
	void SetPivotPreset(SpritePivotPreset spp, const D2D1_SIZE_F& size);
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_Sprite;
	bool m_flipX;
	bool m_flipY;
	Vec2F m_pivot;
};