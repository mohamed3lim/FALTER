/*
 * Square.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: alim
 */

#include "Square.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

Square::Square(double xCoord, double yCoord, double zCoord)
{
	x = xCoord;
	y = yCoord;
	z = zCoord;
	eDist = -1;
	visited = 0;
	// TODO Auto-generated constructor stub

}
double Square:: getX(){
	return x;
}
double Square:: getY(){
	return y;
}
double Square:: getZ(){
	return z;
}
void Square:: setX(double newX){
	x = newX;
}
void Square:: setY(double newY){
	y = newY;
}
void Square:: setZ(double newZ){
	z = newZ;
}
void Square:: setDist(double dist){
	eDist = dist;
}
double Square:: getDist(){
	return Square::eDist;
}

void Square::setVisited (int x){
	visited = x;
}
//
void Square:: incrVisited(){
	visited = visited +1 ;
}
//
int Square:: getVisited (){
	return visited;
}

double Square::calcDist(Square Goal,Data d, int x){

	double xGoal = Goal.getX();
	double yGoal = Goal.getY();
	double zGoal = Goal.getZ();

	double xCurr = Square::getX();
	double yCurr = Square::getY();
	double zCurr = Square::getZ();


	if(x == 1){
		return (sqrt(pow(xGoal - xCurr, 2.0) + pow(yGoal - yCurr, 2.0) + pow(zGoal - zCurr, 2.0)));
	}
	if(x == 2){
		return (fabs(xGoal - xCurr) + fabs(yGoal - yCurr) + fabs(zGoal - zCurr));
	}
	cout << "User Input error for method used!!" <<endl;
	return -1;
}

