/*
 * Odometry.cpp memiliki kelas Odometry yang digunakan untuk membaca posisi robot (X, Y, Theta)
 * Parameter angle harus diset sesuai penempatan rotary encoder pada robot
*/

#include "OdometryABU.h"

Odometry::Odometry(int dia, int resA, int resB, int resC) {
  wheelDia = dia;
  encResA = resA;
  encResB = resB;
  encResC = resC;

  posX = 0;
  posY = 0;
  prevLeft = 0;
  prevRight = 0;
  prevBack = 0;
  theta = 0;
}

void Odometry::readCoordinate(double encLeft, double encRight, double encBack, int heading) {
  double DistLeft = PI * wheelDia * (encLeft / encResA);
  double DistRight = PI * wheelDia * (encRight / encResB);
  double DistBack = PI * wheelDia * (encBack / encResC);

  double diffLeft = DistLeft - prevLeft;
  double diffRight = DistRight - prevRight;
  double diffBack = DistBack - prevBack;

  prevLeft = DistLeft;
  prevRight = DistRight;
  prevBack = DistBack;

  this->theta = (double)heading * (PI / 180.0);

  double localDY = (diffLeft + diffRight) / 2.0;
  double localDX = diffBack; 

  this->posX += (localDX * cos(this->theta)) - (localDY * sin(this->theta));
  this->posY += (localDX * sin(this->theta)) + (localDY * cos(this->theta));
}
