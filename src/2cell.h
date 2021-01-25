typedef unsigned char byte;

struct TwoCell {
  byte leftLit : 1;
  byte leftColourIdx : 3;
  byte rightLit : 1;
  byte rightColourIdx : 3;

  byte getLit(byte);
  void setLit(byte, byte);
  byte getColourIdx(byte);
  void setColourIdx(byte, byte);
  void decay();
};
