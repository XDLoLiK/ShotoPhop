#include "label.hpp"
#include "app.hpp"

Label::Label(const std::string& text, int size, const Color& color, 
	         const std::string& font, Widget* parent):
	Widget(parent),
	m_text(text)
{
	if (!size || text.length() == 0) {
		m_textTexture = nullptr;
		m_bounds = {0, 0, 0, 0};
		return;
	}

	m_textTexture = new Texture(m_text, size, color, font);
	m_bounds = Rect(0, 0, m_textTexture->getBounds().w, m_textTexture->getBounds().h);
}

Label::~Label()
{
	m_text = "";

	delete m_textTexture;
	m_textTexture = nullptr;
}

const std::string Label::getText() const
{
	return m_text;
}

void Label::setGeometry(const Rect& bounds)
{
	m_bounds.x = bounds.x;
	m_bounds.y = bounds.y;
}

void Label::setGeometry(int x, int y, int w, int h)
{
	this->setGeometry({x, y, w, h});
}

void Label::draw()
{
	Renderer* renderer = getApp()->getRenderer();
	renderer->copyTexture(m_textTexture, this->getRealBounds(), m_textTexture->getBounds());
}

bool Label::intersects(const Vec2& point)
{
	if (point.getX() < m_bounds.x || 
		point.getX() > m_bounds.x + m_bounds.w)
	{
		return false;
	}

	if (point.getY() < m_bounds.y || 
		point.getY() > m_bounds.y + m_bounds.h)
	{
		return false;
	}

	return true;
}

bool Label::onMouseMove(const Vec2&, const Vec2&)
{
	return false;
}

bool Label::onButtonClick(MouseButton, const Vec2&)
{
	return false;
}

bool Label::onButtonRelease(MouseButton, const Vec2&) 
{
	return false;
}

bool Label::onKeyPress(Key)
{
	return false;
}

bool Label::onKeyRelease(Key)
{
	return false;
}

bool Label::onTick(Time) 
{
	if (m_isHidden) {
		return false;
	}

	this->draw();
	return false;
}
