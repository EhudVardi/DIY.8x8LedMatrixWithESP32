#include "AnimationManager.h"
#include "Application/ApplicationProperties.h"

AnimationManager::AnimationManager(int screenSize) 
    : currAnimeIndex(0) // Default animation index
{
    // Initialize the list of animations
    animations.push_back(new TextDisplayAnime(screenSize, APP_TITLE_STRING));
    animations.push_back(new TheMatrixAnime(screenSize, 32, 3, 8, 1));
    animations.push_back(new BeatingHeartAnime(screenSize));
    animations.push_back(new SpiralAnime(screenSize));
    animations.push_back(new SnakeInteractiveAnime(screenSize));
    animations.push_back(new TetrisInteractiveAnime(screenSize));
}

void AnimationManager::init(LedMatrixHandler* ledMatrixHandler) {
    initCurrAnime(ledMatrixHandler);
}

BaseInteractiveAnime* AnimationManager::getCurrentAnime() {
    return animation;
}

void AnimationManager::skipToNextAnime(LedMatrixHandler* ledMatrixHandler) {
    currAnimeIndex = (currAnimeIndex + 1) % animations.size();
    initCurrAnime(ledMatrixHandler);
}

void AnimationManager::initCurrAnime(LedMatrixHandler* ledMatrixHandler) {
    animation = animations[currAnimeIndex];
    animation->init(ledMatrixHandler);
    ledMatrixHandler->clearMatrix();
}
