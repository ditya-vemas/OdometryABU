#ifndef ODOMETRYABU_H
#define ODOMETRYABU_H

#include <Arduino.h>

class Odometry {
public:
  double posX;
  double posY;

  Odometry(int dia, int resA, int resB, int resC);
  void readCoordinate(double encLeft, double encRight, double encBack, int heading);

private:
  double wheelDia;
  double encResA;
  double encResB;
  double encResC;

  double DistLeft, diffLeft, prevLeft;
  double DistRight, diffRight, prevRight;
  double DistBack, diffBack, prevBack;

  double theta; // Sudut dari CMPS14
};

#endif