#ifndef HEADER_MODEL_CLASS
#define HEADER_MODEL_CLASS
#include <config.h>

class Model{
public:
  float linearSpeed[2];
  int motorVals[motorChannelsCount];
  float angularSpeed[3];
  float sonarAngle[2][sonarCount];
  float sonarDistance[sonarCount];
  float sonarData[sonarCount][180];
  bool isSonarMeasureNeed;
  unsigned int borderValues[borderSensorsCount];
  Model();
  void inflateMessage(Message*);
  void update(Message*);
};

#endif
