import processing.serial.*;
Serial port;
final int portNumb=15, speed=115200;
boolean flag = true;
int currentAngle = 0;
float preAngle = -1;
class Point{
  public float x;
  public float y;
  Point(float a, float b){
    x=a;
    y=b;
  }
}
class SonarData{
  public float angle;
  public float distance;
}
FloatList hyst = new FloatList();
final Point C = new Point(600, 800);
final float K = 10;
ArrayList<SonarData> data = new ArrayList<SonarData>();
ArrayList<SonarData> data2 = new ArrayList<SonarData>();
void setup(){
  size(1200, 800);
  port = new Serial(this, "COM"+portNumb, speed);
  port.bufferUntil('\n');
  fill(255,0,0);
  noStroke();
}

void draw(){
  drawPoints();
  //drawWall();
  //drawHystogram();
}
void drawHystogram(){
  background(255,255,255);
  fill(255,0,0); 
  final int colWidth = 50;
  for(int i=0; i<hyst.size(); i++){
    if(i==5){
     fill(0,255,0); 
    }
    else if(i==6){
     fill(0,0,255); 
    }
     rect(100+colWidth*i, C.y - hyst.get(i)*K, colWidth-1, hyst.get(i)*K);
     stroke(0,0,0);
     line(0, C.y - 100*K, 1000, C.y - 100*K);
     //println(hyst.get(i));
  }
}
void drawWall(){
  if(flag){
    flag = false;
    background(255,255,255);
    noStroke();
    fill(255,0,0);
    if(data.size()>0){
      rect(200, C.y - data.get(0).distance*K, 100, data.get(0).distance*K);
    }
  }
}
void drawPoints(){
    if(flag){
      flag = false;
      background(255,255,255);
      noStroke();
      fill(255,0,0);
      for(int i=0; i<data.size(); i++){
        ellipse(C.x+data.get(i).distance*cos(radians(data.get(i).angle))*K, C.y - data.get(i).distance*sin(radians(data.get(i).angle))*K, 5, 5);
      }
      stroke(0,0,255);
      line(C.x, C.y, C.x+500*cos(radians(currentAngle)), C.y-500*sin(radians(currentAngle)));
      noFill();
      stroke(230,230,230);
      for(int i=0; i<=950; i+=20){
        arc(C.x, C.y, 2*i, 2*i, -PI, 0);
      }
  }
}
void serialEvent(Serial p){
   String message = port.readStringUntil('\n');
   SonarData temp = parseSonarData(message);
   if(temp.angle == -1){
     return; 
   }
   if(temp.angle <= currentAngle){
    data.clear();
   }
   data.add(temp);
   currentAngle = (int)temp.angle;
   if(message.charAt(0) == '%'){
     parseHystogram(message);
   }
   flag = true;
   println(temp.angle);
}
void parseHystogram(String mess){
  //FloatList hyst = new FloatList();
  hyst.clear();
  if(mess.indexOf('%')==0){
    int divider = 0;
    for(int i=0; i<7; i++){
      hyst.append(float(mess.substring(divider+1, mess.indexOf(':', divider+1))));
      println(mess.substring(divider+1, mess.indexOf(':', divider+1)));
      divider = mess.indexOf(':', divider+1);
    }
  }
}
SonarData parseSonarData(String mess){
    SonarData temp = new SonarData();
    if(mess.indexOf('#')!=0){
      temp.angle = -1;
      return temp;
    }
    int dividerPos = mess.indexOf(':');
    temp.angle = float(mess.substring(1, dividerPos));
    temp.distance = float(mess.substring(dividerPos+1, mess.length()-3));
    return temp;
}
