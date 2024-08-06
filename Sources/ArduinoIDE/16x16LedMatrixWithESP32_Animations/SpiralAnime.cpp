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
    : BaseAnime(size), trailInOrOut(true) {}

void SpiralAnime::init() {
  stepDirection = Down;
  currTrailLength = 0;
  currRowIdx = currColIdx = N/2;
  currTrailStep = 0;
}

void SpiralAnime::step() {
  
  if (currTrailStep == 0) { // current trail draw finished
    if (currTrailLength == N) {
      setPixel(currRowIdx,currColIdx,trailInOrOut); //make sure the last trail of the spiral is also drawn, before switching direction
      // spiral complete. switch trail in/out
      init();
      trailInOrOut = !trailInOrOut;
    }

    stepDirection = static_cast<Direction>((stepDirection + 1) % 4); // move to next direction
    if (stepDirection == Left || stepDirection == Right){ // increase length of current direction trail
      currTrailLength++; 
    }
    currTrailStep = currTrailLength;
    if (currTrailLength == N)
      currTrailStep--;
  }
  
  setPixel(currRowIdx,currColIdx,trailInOrOut);

  if (currTrailStep > 0) {
    switch (stepDirection){
      case Down:  { currRowIdx++;  break; }
      case Left:  { currColIdx--;  break;}
      case Up:    { currRowIdx--;  break;}
      case Right: { currColIdx++;  break;}
    }
    currTrailStep--;
  }

}

