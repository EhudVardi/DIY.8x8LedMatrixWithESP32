#include "StarTravelAnime.h"
#include <cmath>
#include <cstdlib>

StarTravelAnime::StarTravelAnime(int size, int starCount)
    : BaseInteractiveAnime(), matrixSize(size), speed(1.0f), fieldOfView(0.5f) {
    stars.resize(starCount);
    stepDuration = 5;
    SetInputHandlers();
}

void StarTravelAnime::init(LedMatrixHandler* ledMatrixHandler) {
    for (auto& star : stars) {
        respawnStar(star);
    }
}

void StarTravelAnime::respawnStar(Star& star) {
    star.x = static_cast<float>(rand() % matrixSize) - matrixSize / 2.0f;
    star.y = static_cast<float>(rand() % matrixSize) - matrixSize / 2.0f;
    star.z = static_cast<float>(rand() % matrixSize + 1);  // Ensure z > 0
}

void StarTravelAnime::step(LedMatrixHandler* ledMatrixHandler) {
    ledMatrixHandler->clearMatrix();  // Clear the screen

    for (auto& star : stars) {
        // Move the star closer
        star.z -= speed;

        if (star.z <= 0) {
            respawnStar(star);  // Respawn if it moves past the POV
            continue;
        }

        // Perspective projection to 2D with FoV adjustment
        float fovFactor = fieldOfView / star.z;
        int row = static_cast<int>(star.x * fovFactor + matrixSize / 2);
        int col = static_cast<int>(star.y * fovFactor + matrixSize / 2);

        // Draw the star if it's within bounds
        if (row >= 0 && row < matrixSize && col >= 0 && col < matrixSize) {
            ledMatrixHandler->setPixel(row, col, true);  // Assume true means "on"
        }
    }
}

void StarTravelAnime::SetInputHandlers() {
    RegisterInputHandler(0, [this](bool isSet) {
        if (isSet) {
            speed = std::max(0.02f, speed - 0.02f);  // Decrease Speed
            fieldOfView = std::min(2.0f, fieldOfView + 0.03f);  // Increase FoV
        }
    });
    RegisterInputHandler(1, [this](bool isSet) {
        if (isSet) {
            speed = std::min(1.0f, speed + 0.02f);  // Increase Speed
            fieldOfView = std::max(0.5f, fieldOfView - 0.03f);  // Reduce FoV
        }
    });
    RegisterInputHandler(2, [this](bool isSet) {
        if (isSet)
            if (stars.size() > 1)
                stars.resize(stars.size() - 1);  // Remove a star
    });
    RegisterInputHandler(3, [this](bool isSet) {
        if (isSet)
            if (stars.size() < 100)
                stars.resize(stars.size() + 1);  // Add a star
    });
}
