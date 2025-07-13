#pragma once

#include <unordered_map>
#include <filesystem>
#include <wrl/client.h>
#include "D2DRenderer.h"
#include "AnimationClip.h"
#include "UIData.h"
#include "MapData.h"

class AssetManager
{
public:
	using AnimationClips = std::vector<std::pair<std::string, AnimationClip>>;
	AssetManager() = default;
	~AssetManager() = default;

	void LoadTexture(D2DRenderer* renderer, std::wstring keyWide, std::filesystem::path fullPath);
	void LoadAnimation(D2DRenderer* renderer, std::wstring keyWide, std::filesystem::path fullPath);

	const ID2D1Bitmap1* GetTexture(const std::wstring& key) const;
	const AnimationClips& GetClips(const std::wstring& key) const;
	const UIData& GetUI(const std::wstring& key) const;
	const MapData& GetMap(const std::wstring& key) const;

private:
	std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_Textures;
	std::unordered_map<std::wstring, AnimationClips> m_Animations;
	std::unordered_map<std::wstring, UIData> m_UIs;
	std::unordered_map<std::wstring, MapData> m_Maps;
};

