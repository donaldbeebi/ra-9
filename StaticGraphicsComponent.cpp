#include "StaticGraphicsComponent.h"

StaticGraphicsComponent::StaticGraphicsComponent(std::string texture, unsigned int stateCount, std::shared_ptr<TransformComponent> TC) 
	: GraphicsComponent(stateCount) {
	Texture& tempTexture = TextureManager::getTexture("graphics/objects/" + texture + ".png");
	m_Sprite.setTexture(tempTexture);

	m_TextureSize = Vector2f(float(tempTexture.getSize().x), float(tempTexture.getSize().y) / float(stateCount));
	m_Sprite.setOrigin(Vector2f(m_TextureSize.x / 2.0f, m_TextureSize.y / 2.0f));

	//setting texture rect
	m_TextRect = m_Sprite.getTextureRect();
	m_TextRect.height /= stateCount;
	m_Sprite.setTextureRect(m_TextRect);
	m_TC = TC;
	m_DrawOffsetY = (m_TextureSize.y - 64.0f * m_TC->getYDimension()) / 2.0f;
}

void StaticGraphicsComponent::disableDrawOffset() {
	m_DrawOffsetY = 0.0f;
}