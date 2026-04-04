#pragma once

#include "RenderComponent.h"
#include "ZSortable.h"
#include "Color.h"
#include <string>

class TextComponent :public RenderComponent, public ZSortable
{
private:
	std::string text = "";
	std::string fontFilepath = "";
	int characterSize = 0;
	bool autoCenter = false;
	Color fillColor = Color();
	Color outlineColor = Color();
	float outlineThickness = 0.f;
	bool lit = false;
public:
	TextComponent(Entity* owner);
	virtual ~TextComponent() = default;

	RenderDataType get_type() const override;
	TextRenderData build_render_data() const;

	const std::string& get_text() const;
	void set_text(const std::string& text);

	const std::string& get_fontFilepath() const;
	void set_fontFilepath(const std::string& fontFilepath);

	int get_characterSize() const;
	void set_characterSize(int characterSize);

	bool is_autoCenter() const;
	void set_autoCenter(bool autoCenter);

	const Color& get_fillColor() const;
	void set_fillColor(const Color& fillColor);

	const Color& get_outlineColor() const;
	void set_outlineColor(const Color& outlineColor);

	float get_outlineThickness() const;
	void set_outlineThickness(float outlineThickness);

	bool is_lit() const;
	void set_lit(bool lit);
};