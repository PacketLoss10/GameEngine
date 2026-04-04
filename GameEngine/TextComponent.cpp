#include "TextComponent.h"

TextComponent::TextComponent(Entity* owner) :RenderComponent(owner), ZSortable(0) {}

RenderDataType TextComponent::get_type() const
{
	return RenderDataType::Text;
}

TextRenderData TextComponent::build_render_data() const
{
	TextRenderData data;
	
	data.text = text;
	data.fontFilepath = fontFilepath;
	data.characterSize = characterSize;
	data.autoCenter = autoCenter;
	data.fillColor = fillColor;
	data.outlineColor = outlineColor;
	data.outlineThickness = outlineThickness;
	data.lighting = LightingData(lit, NormalMap());
	data.zOrder = get_zOrder();
	data.transform = get_worldTransform();
	data.enabled = enabled;
	
	return data;
}

const std::string& TextComponent::get_text() const
{
	return text;
}

void TextComponent::set_text(const std::string& text)
{
	this->text = text;
}

const std::string& TextComponent::get_fontFilepath() const
{
	return fontFilepath;
}

void TextComponent::set_fontFilepath(const std::string& fontFilepath)
{
	this->fontFilepath = fontFilepath;
}

int TextComponent::get_characterSize() const
{
	return characterSize;
}

void TextComponent::set_characterSize(int characterSize)
{
	this->characterSize = characterSize;
}

bool TextComponent::is_autoCenter() const
{
	return autoCenter;
}

void TextComponent::set_autoCenter(bool autoCenter)
{
	this->autoCenter = autoCenter;
}

const Color& TextComponent::get_fillColor() const
{
	return fillColor;
}

void TextComponent::set_fillColor(const Color& fillColor)
{
	this->fillColor = fillColor;
}

const Color& TextComponent::get_outlineColor() const
{
	return outlineColor;
}

void TextComponent::set_outlineColor(const Color& outlineColor)
{
	this->outlineColor = outlineColor;
}

float TextComponent::get_outlineThickness() const
{
	return outlineThickness;
}

void TextComponent::set_outlineThickness(float outlineThickness)
{
	this->outlineThickness = outlineThickness;
}

bool TextComponent::is_lit() const
{
	return lit;
}

void TextComponent::set_lit(bool lit)
{
	this->lit = lit;
}