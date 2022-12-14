#include "app.hpp"
#include "button.hpp"


extern App* __theApp__;


Button::Button(const std::string& text, int size, Widget* parent):
	Widget(parent)
{
	m_label = new Label(text, size, black, DEFAULT_FONT, this);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

	this->setDefaultTexture(Color(231, 178, 212, 255));
	this->setHoverTexture(Color(185, 130, 183, 255));

	this->setFrameColor(m_frameDefaultColor);
	this->setBackground(m_defaultTexture);
}

Button::Button(const std::string& text, const Rect& bounds, Widget* parent):
	Widget(bounds, parent)
{
	m_label = new Label(text, m_bounds.h, black, DEFAULT_FONT, this);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

	m_label->setGeometry((m_bounds.w - m_label->getBounds().w) / 2, 0);

	this->setDefaultTexture(Color(231, 178, 212, 255));
	this->setHoverTexture(Color(185, 130, 183, 255));

	this->setFrameColor(m_frameDefaultColor);
	this->setBackground(m_defaultTexture);
}

void Button::setShortcut(Key key)
{
	m_hasShortcut = true;
	m_shotrcut = key;
}

Button::~Button()
{
	delete m_label;
	m_label = nullptr;
}

void Button::setFrameHoverColor(const Color& color)
{
	m_frameHoverColor = color;
}

void Button::setFrameDefaultColor(const Color& color)
{
	m_frameDefaultColor = color;
}

void Button::setGeometry(const Rect& bounds)
{
	m_bounds = bounds;

	const std::string& oldText = m_label->getText();
	delete m_label;

	m_label = new Label(oldText, m_bounds.h, black, DEFAULT_FONT, this);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);
	
	m_label->setGeometry((m_bounds.w - m_label->getBounds().w) / 2, 0);
}

void Button::setGeometry(int x, int y, int w, int h)
{
	w = (w == -1) ? m_bounds.w : w;
	h = (h == -1) ? m_bounds.h : h;

	this->setGeometry({x, y, w, h});
}

void Button::draw()
{
	if (m_isHidden)
		return;

	drawSkin (this->getRealBounds());
	drawFrame(this->getRealBounds());

	m_label->draw();
}

bool Button::intersects(const Vec2& point)
{
	const Rect& bounds = this->getRealBounds();

	if (point.getX() < bounds.x || 
		point.getX() > bounds.x + bounds.w)
	{
		return false;
	}

	if (point.getY() < bounds.y || 
		point.getY() > bounds.y + bounds.h)
	{
		return false;
	}

	return true;
}

bool Button::onMouseMove(const Vec2& point, const Vec2&)
{
	if (m_isHidden)
		return false;

	if (!this->intersects(point)) {
		this->setBackground(m_defaultTexture);
		this->setFrameColor(m_frameDefaultColor);
		return false;
	}

	this->setBackground(m_hoverTexture);
	this->setFrameColor(m_frameHoverColor);
	return true;
}

bool Button::onButtonClick(MouseButton, const Vec2&)
{
	if (m_isHidden)
		return false;

	return false;
}

bool Button::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	if (this->intersects(point) && button == SDL_BUTTON_LEFT)
		buttonClick();

	return true;
}

bool Button::onKeyPress(Key key)
{
	if (m_isHidden)
		return false;

	if (key == SDLK_LCTRL) {
		m_ctrlPresed = true;
	}

	if (m_ctrlPresed && m_hasShortcut && key == m_shotrcut) {
		buttonClick();
		return true;
	}

	return false;
}

bool Button::onKeyRelease(Key key)
{
	if (m_isHidden)
		return false;

	if (key == SDLK_LCTRL) {
		m_ctrlPresed = false;
	}

	return false;
}

bool Button::onTick(Time)
{
	if (m_isHidden)
		return false;

	this->draw();
	return true;
}
