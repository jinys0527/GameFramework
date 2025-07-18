#include "pch.h"
#include <fstream>
#include "json.hpp"
#include "JsonParser.h"

AnimationClips JsonParser::LoadAnimation(const std::filesystem::path& jsonPath)
{
	std::ifstream ifs(jsonPath);

	if (!ifs.is_open())
	{
		std::cerr << "파일을 열 수 없습니다.\n";
		return {};
	}

	std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	auto parsed = nlohmann::json::parse(content, nullptr, false);

	if (parsed.is_discarded())
	{
		std::cerr << "JSON 파싱 실패 : 유효하지 않은 문서입니다.\n";
		return {};
	}

	const auto& root = parsed;

	AnimationClip clip;
	
	auto& framesNode = root["frames"];
	if (framesNode.is_object())
	{
		for (auto it = framesNode.begin(); it != framesNode.end(); ++it)
		{
			const auto& frame = it.value();

			Frame fd;
			fd.srcRect.left = frame["frame"]["x"];
			fd.srcRect.top = frame["frame"]["y"];
			fd.srcRect.right = fd.srcRect.left + frame["frame"]["w"];
			fd.srcRect.bottom = fd.srcRect.top + frame["frame"]["h"];
			fd.duration = frame["duration"] / 1000.0f;
			clip.AddFrame(fd);
		}
	}
	else if (framesNode.is_array())
	{
		for (const auto& frame : framesNode)
		{
			Frame fd;
			fd.srcRect.left = frame["frame"]["x"];
			fd.srcRect.top = frame["frame"]["y"];
			fd.srcRect.right = fd.srcRect.left + frame["frame"]["w"];
			fd.srcRect.bottom = fd.srcRect.top + frame["frame"]["h"];
			fd.duration = frame["duration"] / 1000.0f;
			clip.AddFrame(fd);
		}
	}
	else
	{
		std::cerr << "Unsupported 'frames' format" << '\n';
		return {};
	}

	std::filesystem::path keyPath = jsonPath;
	keyPath.replace_extension();
	std::string key = keyPath.string();

	AnimationClips clips;

	if (root["meta"].contains("frameTags"))
	{
		for (const auto& fTag : root["meta"]["frameTags"])
		{
			Tag tag;
			tag.m_name = fTag["name"];
			tag.m_from = fTag["from"];
			tag.m_to = fTag["to"];
			tag.m_direction = fTag["direction"];

			AnimationClip subClip;

			for (int i = tag.m_from; i <= tag.m_to; i++)
			{
				subClip.AddFrame(clip.GetFrame(i));
			}

			clips.emplace_back(std::make_pair(tag.m_name, subClip));
		}
	}
	else
	{
		clips.emplace_back(std::make_pair(key, clip));
	}

	return clips;
}
