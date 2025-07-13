#include "pch.h"
#include "D2DRenderer.h"
#include "JsonParser.h"
#include "AssetManager.h"

void AssetManager::LoadTexture(D2DRenderer* renderer, std::wstring keyWide, std::filesystem::path fullPath)
{
	ComPtr<ID2D1Bitmap1> bitmap;

	std::wstring path = fullPath.wstring();

	renderer->CreateBitmapFromFile(path.c_str(), *bitmap.GetAddressOf());
	m_Textures.insert({ keyWide, bitmap });
}

void AssetManager::LoadAnimation(D2DRenderer* renderer, std::wstring keyWide, std::filesystem::path fullPath)
{
	m_Animations.insert({ keyWide, JsonParser::LoadAnimation(fullPath) });

	const AnimationClips& constClips = GetClips(keyWide);
	AnimationClips& clips = const_cast<AnimationClips&>(constClips);

	for (auto& clip : clips)
	{
		Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap;

		std::filesystem::path keyPath = fullPath.replace_extension(".png");
		std::wstring path = keyPath.wstring();

		renderer->CreateBitmapFromFile(path.c_str(), *bitmap.GetAddressOf());
		clip.second.SetTextureKey(keyWide);
		m_Textures.insert({ keyWide, bitmap });
	}
}

const ID2D1Bitmap1* AssetManager::GetTexture(const std::wstring& key) const
{
	auto it = m_Textures.find(key);
	if (it != m_Textures.end())
	{
		return it->second.Get();
	}

	return nullptr;
}

const AssetManager::AnimationClips& AssetManager::GetClips(const std::wstring& key) const
{
	auto it = m_Animations.find(key);
	if (it != m_Animations.end())
	{
		return it->second;
	}

	static const AnimationClips empty;
	return empty;
}

const UIData& AssetManager::GetUI(const std::wstring& key) const
{
	auto it = m_UIs.find(key);
	if (it != m_UIs.end())
	{
		return it->second;
	}

	static const UIData empty;
	return empty;
}

const MapData& AssetManager::GetMap(const std::wstring& key) const
{
	auto it = m_Maps.find(key);
	if (it != m_Maps.end())
	{
		return it->second;
	}

	static const MapData empty;
	return empty;
}
