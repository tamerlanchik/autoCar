#include "Model.h"

Model::Model():isSonarMeasureNeed(false){
  for(unsigned int i = 0; i<2; i++){
    linearSpeed[i] = 0;
    angularSpeed[i] = 0;
  }
  angularSpeed[2] = 0;
  for(unsigned int i = 0; i<sonarCount; i++){
    sonarAngle[0][i] = sonarAngle[1][i] = 0;
    sonarDistance[i] = 0;
  }
  for(unsigned int i = 0; i<borderSensorsCount; i++){
    borderValues[i] = 0;
  }
}

void Model::inflateMessage(Message* mess){
  for(int i=0; i<sonarCount; i++){
    //mess->getSonar().setAngle(sonarAngle[0][i]);
    //mess->getSonar().setDistance(sonarDistance[i]);
  }
  //mess->getBorders()->values = borderValues;
}
void Model::update(Message* message){
  for(int i = 0; i < motorChannelsCount; i++){
    motorVals[i] = message->getChassis()->getValue(i);
  }
  /*for(int i=0; i<sonarCount; i++){
    sonarAngle[1][i] = message->getSonar()->getAngle(i);
  }*/
  isSonarMeasureNeed = true;
}
