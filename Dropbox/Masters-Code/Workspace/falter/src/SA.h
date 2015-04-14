/*
 * SA.h
 *
 *  Created on: Dec 8, 2014
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
#include "exchange.pb.h"
#include <queue>
#include <deque>
#include <list>
#include <errno.h>
#include "Square.h"
#include "math.h"

int nextStepSA(list<Square> *openList,Data d, Square *Current, Square Goal,list<int> *movements,bool *localMinFlag, int method, double stepLength,double *globalMin,double *localMin, double *temperature);
bool isLocalMin(double x, double y, double z, list<Square> openList);

#define PI 3.141592

#endif /* REPASTAR_H_ */

