#include "AnimatedGraphicsComponent.h"

AnimatedGraphicsComponent::AnimatedGraphicsComponent(std::shared_ptr<AnimationComponent> animation, std::shared_ptr<TransformComponent> TC) 
	: GraphicsComponent(animation->getImageCount().y){
	m_Animation = animation;
	Texture& tempTexture = TextureManager::getTexture("graphics/objects/" + m_Animation->getTextureName() + ".png");
	m_Sprite.setTexture(tempTexture);

	m_TextureSize = m_Animation->getTextureSize();
	m_Sprite.setOrigin(Vector2f(m_TextureSize.x / 2.0f, m_TextureSize.y / 2.0f));
	m_Sprite.setTextureRect(m_Animation->m_TextRect);
	m_TextRect = m_Sprite.getTextureRect();
	m_TC = TC;
	m_DrawOffsetY = (m_TextureSize.y - 64.0f * m_TC->getYDimension()) / 2.0f;
}

void AnimatedGraphicsComponent::setState(int state) {
	if (m_State != state) {
		m_Animation->resetFrame();
		GraphicsComponent::setState(state);
	}
}

void AnimatedGraphicsComponent::update(float dt) {
	m_Animation->update(dt);
	m_TextRect = m_Animation->m_TextRect;
	GraphicsComponent::update(dt);
}