/*
 * Square.h
 *
 *  Created on: Nov 3, 2014
 *      Author: alim
 */

#ifndef SQUARE_H_
#define SQUARE_H_
#include <queue>
#include <deque>
#include <list>
#include "math.h"
#include "exchange.pb.h"

using namespace std;


class Square{

	double x;
	double y;
	double z;
	double eDist;
	int visited;
//	queue <Square> neighbours;

	public:
		Square(double xCoord, double yCoord, double zCoord);
		double getX();
		double getY();
		double getZ();
		void setX(double newX);
		void setY(double newY);
		void setZ(double newZ);
		void setDist(double dist);
		double getDist();
		double calcDist(Square Goal,Data d, int method); // x is 1 for  euclidean and 2 for manhattan
		void incrVisited();
		int getVisited();
		void setVisited(int x);
};



#endif /* SQUARE_H_ */
