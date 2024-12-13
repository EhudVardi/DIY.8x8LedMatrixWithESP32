#include "StarTravelAnime.h"
#include <cmath>
#include <cstdlib>

StarTravelAnime::StarTravelAnime(int size, int starCount)
    : BaseInteractiveAnime(), matrixSize(size), speed(0.1f), fieldOfView(1.0f) {
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
        if (isSet)
            speed = std::max(0.05f, speed - 0.05f);  // Decrease Speed
    });
    RegisterInputHandler(1, [this](bool isSet) {
        if (isSet)
            speed = std::min(1.0f, speed + 0.05f);  // Increase Speed
    });
    RegisterInputHandler(2, [this](bool isSet) {
        if (isSet)
            fieldOfView = std::max(0.5f, fieldOfView - 0.1f);  // Reduce FoV
    });
    RegisterInputHandler(3, [this](bool isSet) {
        if (isSet)
            fieldOfView = std::min(2.0f, fieldOfView + 0.1f);  // Increase FoV
    });
}



// RegisterInputHandler(0, [this](bool isSet) {
//     if (isSet)
//         speed = std::max(0.05f, speed - 0.05f);
// });
// RegisterInputHandler(1, [this](bool isSet) {
//     if (isSet)
//         speed = std::min(1.0f, speed + 0.05f);
// });
// RegisterInputHandler(2, [this](bool isSet) {
//     if (isSet)
//         if (stars.size() > 1)
//             stars.resize(stars.size() - 1);
// });
// RegisterInputHandler(3, [this](bool isSet) {
//     if (isSet)
//         if (stars.size() < 100)
//             stars.resize(stars.size() + 1);
// });