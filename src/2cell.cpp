#include <2cell.h>

byte TwoCell::getLit(register byte y) {
  return (y & 1) ? this->rightLit : this->leftLit;
}

void TwoCell::setLit(register byte y, register byte val) {
  if (y & 1) {
    this->rightLit = val;
  } else {
    this->leftLit = val;
  }
}

byte TwoCell::getColourIdx(register byte y) {
  return (y & 1) ? this->rightColourIdx : this->leftColourIdx;
}

void TwoCell::setColourIdx(register byte y, register byte val) {
  if (y & 1) {
    this->rightColourIdx = val;
  } else {
    this->leftColourIdx = val;
  }
}

void TwoCell::decay() {
  this->rightColourIdx && this->rightColourIdx++;
  this->leftColourIdx && this->leftColourIdx--;
}
