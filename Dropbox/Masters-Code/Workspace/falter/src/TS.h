/*
 * repAStar.h
 *
 *  Created on: Nov 3, 2014
 *      Author: alim
 */

#ifndef REPASTAR_H_
#define REPASTAR_H_

#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <queue>
#include <deque>
#include <list>
#include <errno.h>
#include "exchange.pb.h"
#include "Square.h"
#include "math.h"

int nextStepTS(Data d, list<Square> *openList, list<Square> *TabuList,
		list<Square> *tabuListLong, Square *Current, Square Goal,
		Square *subGoal,list<Square> *decisionSquare, list<int> *movements, bool *localMinFlag, int method,
		double stepLength, double *globalMin);
bool isVisitedTS(double x, double y, double z, list<Square> TabuList,
		bool localMinFlag);
bool isTabu(double x, double y, double z, list<Square> tabuListLong);
Square updateSubGoal(list<Square> *openList, list<Square> TabuList);
//int localMin(list<int> *movements, bool *localMinFlag);
int localMin(list<int> *movements, bool *localMinFlag, list<Square> *TabuList,
		Square *Current);
int angleFilter(double angle);

#define PI 3.141592

#endif /* REPASTAR_H_ */
