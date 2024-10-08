#pragma once

#include "../Utils/myUtils.h"
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
//using json = nlohmann::json;

class TextInputBox
{
	std::vector<std::pair<u8, char>> allowedKeys;

	AEGfxVertexList* mesh;
	s8 font;
	
	const int MaxTextLen{ 14 };

	AEVec2 boxPos{ 0, 0 };
	AEVec2 boxSize;
	AEVec2 boxMargin{ 15, 15 };
	Color boxColor{ 255, 255, 255 };

	AEVec2 barPos{ 0, 0 };
	AEVec2 barSize;
	Color barColor{ 0, 0, 0 };

	float blinkSpeed{ 1.f };
	float blinkDt{ 0.f };
	bool barVisible{ true };

	bool inputEnabled{ true };
	std::string text = "";

public:
	TextInputBox();
	~TextInputBox();

	void Update(float dt);

	void DrawTextInputBox();
	void DrawBar(float dt);
	void DrawUserText();

	void UpdateText();
	std::string const GetText() const;

	void SaveToJson();
	void LoadFromJson();
};