#pragma once
#include "UIComponent.h"
#include <wrl/client.h>
#include <d2d1.h>

class D2DRenderer;
class ID2D1Bitmap1;

class UIImageComponent : public UIComponent
{
public:
	virtual ~UIImageComponent() = default;
	void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap);
	void SetUV(const D2D1_RECT_F& sourceRect);
	void Render(D2DRenderer* renderer);
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_Bitmap;
	D2D1_RECT_F m_SourceRect = {};
};

