#include "HelpStyle.h"

#include "resources/Font.h"

HelpStyle::HelpStyle()
{
	position = Vector2f(Renderer::getScreenWidth() * 0.5f, Renderer::getScreenHeight() * 0.97f);
	origin = Vector2f(0.5f, 0.5f);
	iconColor = 0xB7B7B7FF;
	textColor = 0xB7B7B7FF;

	if(FONT_SIZE_SMALL != 0)
		font = Font::get(FONT_SIZE_SMALL);
	else
		font = nullptr;
}

void HelpStyle::applyTheme(const std::shared_ptr<ThemeData>& theme, const std::string& view)
{
	auto elem = theme->getElement(view, "help", "helpsystem");
	if(!elem)
		return;

	if(elem->has("pos"))
		position = elem->get<Vector2f>("pos") * Vector2f((float)Renderer::getScreenWidth(), (float)Renderer::getScreenHeight());

	if(elem->has("origin"))
		origin = elem->get<Vector2f>("origin");

	if(elem->has("textColor"))
		textColor = elem->get<unsigned int>("textColor");

	if(elem->has("iconColor"))
		iconColor = elem->get<unsigned int>("iconColor");

	if(elem->has("fontPath") || elem->has("fontSize"))
		font = Font::getFromTheme(elem, ThemeFlags::ALL, font);
}
