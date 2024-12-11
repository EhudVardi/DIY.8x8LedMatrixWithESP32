#include "SpiralAnime.h"

///Drawing algorithm:
/// movement directions: D=Down, L=Left, U=Up, R=Right
/// start from center of matrix: N/2
/// movements direction and count is shown in the following table.
///  each record shows the direction to move next and how many steps in that direction is required
///  example for N=16:
///				D	L	U	R
///	-> start	0	1	1	2
///				2	3	3	4
///				4	5	5	6
///				6	7	7	8
///				8	9	9	10
///				10	11	11	12
///				12	13	13	14
///				14	15	15	16(actually=15) -> end


SpiralAnime::SpiralAnime(int size)
    : BaseInteractiveAnime(size), trailInOrOut(true) {
    stepDuration = 5;
    SetInputHandlers();
}

void SpiralAnime::init(LedMatrixHandler* ledMatrixHandler) {
    stepDir = Down;
    currTrailLength = 0;
    currRowIdx = currColIdx = ledMatrixHandler->getSize() / 2;
    currTrailStep = 0;
}

void SpiralAnime::step(LedMatrixHandler* ledMatrixHandler) {

    int N = ledMatrixHandler->getSize();

    if (currTrailStep == 0) {  // current trail draw finished
        if (currTrailLength == N) {
            ledMatrixHandler->setPixel(currRowIdx, currColIdx, trailInOrOut);  //make sure the last trail of the spiral is also drawn, before switching direction
            // spiral complete. reset spiral head pos and switch trail in/out
            init(ledMatrixHandler);
            trailInOrOut = !trailInOrOut;
        }

        stepDir = static_cast<Dir>((stepDir + 1) % 4);  // move to next direction
        if (stepDir == Left || stepDir == Right) {      // increase length of current direction trail
            currTrailLength++;
        }
        currTrailStep = currTrailLength;
        if (currTrailLength == N)
            currTrailStep--;
    }

    ledMatrixHandler->setPixel(currRowIdx, currColIdx, trailInOrOut);

    if (currTrailStep > 0) {
        switch (stepDir) {
            case Down: { currRowIdx++; break; }
            case Left: { currColIdx--; break; }
            case Up: { currRowIdx--; break; }
            case Right: { currColIdx++; break; }
        }
        currTrailStep--;
    }
}

void SpiralAnime::SetInputHandlers() {
    RegisterInputHandler(0, [this](bool isSet) {
        if (isSet)
            stepDuration = max(10, stepDuration - 5);
    });
    RegisterInputHandler(1, [this](bool isSet) {
        if (isSet)
            stepDuration = min(1000, stepDuration + 5);
    });
    RegisterInputHandler(2, [this](bool isSet) {
        if (isSet)
            stepDuration = max(10, stepDuration - 50);
    });
    RegisterInputHandler(3, [this](bool isSet) {
        if (isSet)
            stepDuration = min(1000, stepDuration + 50);
    });
}
