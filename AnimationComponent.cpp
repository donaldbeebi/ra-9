#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(std::string texture, Vector2u imageCount) {
	m_TextureName = texture;
	Texture& tempTexture = TextureManager::getTexture("graphics/objects/" + texture + ".png");
	m_TextRect.left = 0;
	m_TextRect.top = 0;
	m_TextRect.width = tempTexture.getSize().x / imageCount.x;
	m_TextRect.height = tempTexture.getSize().y / imageCount.y;
	m_TextureSize = Vector2f(m_TextRect.width, m_TextRect.height);
	
	m_ImageCount = imageCount;
	m_ConstantSwitchTime = 0.0f;
	m_VariedSwitchTimes = nullptr;
	m_CurrentSwitchTime = 0.0f;
	m_TotalTime = 0.0f;
	m_CurrentImage.x = 0;
	m_CurrentImage.y = 0;
	m_HasVariedSwitchTimes = false;
	m_IsStopped = true;
}

void AnimationComponent::play() {
	if (m_IsStopped) {
		m_IsStopped = false;
	}
}

void AnimationComponent::stop() {
	if (!m_IsStopped) {
		m_IsStopped = true;
	}
}

void AnimationComponent::setConstantSwitchTime(float constantSwitchTime) {
	if (!m_HasVariedSwitchTimes) {
		m_ConstantSwitchTime = constantSwitchTime;
		m_CurrentSwitchTime = constantSwitchTime;
	}
	else {
#ifdef debuggingOnConsole
		cout << "This animation is already set to have varied switch times already!";
#endif
	}
}

//IMPLEMENT - do I really need varied switch time???
void AnimationComponent::setVariedSwitchTimes(std::unique_ptr<std::vector<float>> variedSwitchTimes) {
#ifdef debuggingOnConsole
	assert(variedSwitchTimes->size() != m_ImageCount.x);
	cout << "The number of switch times does not match with the imagecount.y!";
#endif
	m_VariedSwitchTimes = move(variedSwitchTimes);
	m_CurrentSwitchTime = (*m_VariedSwitchTimes)[0];
	m_HasVariedSwitchTimes = true;
}

void AnimationComponent::resetFrame() {
	m_CurrentImage.x = 0;
	m_TotalTime = 0.0f;
}

std::string AnimationComponent::getTextureName() {
	return m_TextureName;
}

Vector2f AnimationComponent::getTextureSize() {
	return m_TextureSize;
}

Vector2u AnimationComponent::getImageCount() {
	return m_ImageCount;
}