/*
 * repAStar.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: alim
 */
#include "TS.h"

int nextStepTS(Data d, list<Square> *openList, list<Square> *TabuList,
		list<Square> *tabuListLong, Square *Current, Square Goal,
		Square *subGoal, list<Square> *decisionSquare, list<int> *movements,
		bool *localMinFlag, int method, double stepLength, double *error)
{
	int direction[8]; // change with dimentions increase
	int directionCounter = 0;
	double xTemp;
	double yTemp;
	double zTemp;
	Square tempSquare = Square(0, 0, 0);
	Square tempDS = Square(-1000, -1000, -1000);
	list<Square> tempList;
	if ((*movements).size() == 0)
	{
		(*subGoal) = Goal;
		(*Current).setVisited(1);
		(*decisionSquare).push_back((*Current));
		cout << "Set Decision node to: " << (*Current).getX() << " "
				<< (*Current).getY() << " " << (*Current).getZ()
				<< endl;
	}
//	(*openList).push_back((*Current));

	double diffX = fabs((*subGoal).getX() - (*Current).getX());
	double diffY = fabs((*subGoal).getY() - (*Current).getY());
	double diffZ = fabs((*subGoal).getZ() - (*Current).getZ());

	if ((diffX < 0.1) && (diffY < 0.1)) // && (diffZ < 0.1)
	{
		if ((*subGoal).getVisited() != 1)
		{
			(*subGoal) = (*decisionSquare).back();
			(*decisionSquare).pop_back();
			cout << "xSub " << (*subGoal).getX() << " ySub " << (*subGoal).getY()
					<< " zSub" << (*subGoal).getZ() << endl;
		}
		else
		{
			(*localMinFlag) = false;
			(*subGoal) = Goal;
		}
		if ((*decisionSquare).size() == 0)
		{
			cout << "DS list is empty" << endl;
		}
	}

	list<Square> tempOpenList;
	list<Square> visitedNeighbours;
//	int visitedDirectionsCounter = 0;
//	int visitedDirections[8] = {0,0,0,0,0,0,0,0};

	if ((*TabuList).size() == 20)
	{
		tempOpenList = (*TabuList);
		tempSquare = tempOpenList.back();
//		tempOpenList.pop_back();
//		double val1 = tempSquare.getDist();
		double val1 = (*Current).getDist();
//		double val1 = 0;
//		double val2 = 0;
//		cout << "prev " << tempSquare.getDist() << endl;
//		cout << "curr " << tempOpenList.back().getDist() << endl;
		for (int i = 0; i < 19; i++)
		{
//			if (i < 5)
//			{
//				val1 = val1 + tempOpenList.back().getDist();
//			}
//			if (i > 2)
//			{
//				val2 = val2 + tempOpenList.back().getDist();
//			}
			tempOpenList.pop_back();
		}
		double val2 = tempOpenList.back().getDist();
		*error = val2 - val1;
		cout << "Val1 " << val1 << endl;
		cout << "Val2 " << val2 << endl;
//		*error = (val1 - val2) / 5;
	}
	cout << "Error " << *error << endl;

	if ((*error >= (400 * stepLength)) && (!(*localMinFlag)))
//	if ((*error > (1.1)) && (!(*localMinFlag)))
	{
		*localMinFlag = true;
//		if ((*decisionSquare).back().getZ() != -1000)
//		{
		(*subGoal) = (*decisionSquare).back();
		(*decisionSquare).pop_back();
//			(*decisionSquare).push_back(tempDS);
//		}
//		else
//		{
//			(*subGoal) = updateSubGoal(openList, *TabuList);
//		}
		cout << "xSub " << (*subGoal).getX() << " ySub " << (*subGoal).getY()
				<< " zSub" << (*subGoal).getZ() << endl;
		(*TabuList).clear();
	}
	else
	{
		*error = 100;
	}

	double angle = d.currangle();

	int dirInt = angleFilter(angle);

	double front = d.srfdata(0).srf_front_ctr();
	double back = d.srfdata(0).srf_rear();
	double left = d.srfdata(0).srf_lhs();
	double right = d.srfdata(0).srf_rhs();
	double leftFront = d.srfdata(0).srf_front_lhs();
	double rightFront = d.srfdata(0).srf_front_rhs();
	double ground = d.srfdata(0).srf_gnd();
//	double ceiling = d.srfdata(0).srf_ceiling();
	bool side = ((*movements).back() == 3) || ((*movements).back() == 4)
			|| ((*movements).back() == 2);

	if ((*movements).size() > 0)
	{
		if ((((side && ((*decisionSquare).back().getVisited() == 1)))
				|| (((right > (stepLength * 2)) && (left > (stepLength * 2))
						&& (front > (stepLength * 2))
						&& (back > (stepLength * 2))))) && (!(*localMinFlag)))
		{
//			cout << "here ba2a" << endl;
			if (!isVisitedTS((*Current).getX(), (*Current).getY(),
					(*Current).getZ(), (*decisionSquare), true))
			{
//				(*decisionSquare).pop_back();
				(*Current).setVisited((*movements).back());
				(*decisionSquare).push_back((*Current));
				cout << "Set Decision node to: " << (*Current).getX() << " "
						<< (*Current).getY() << " " << (*Current).getZ()
						<< endl;
				if ((*tabuListLong).size() > 0)
				{
					(*tabuListLong).pop_back();
				}
			}
		}
		if (((*movements).back() != 1) && ((*movements).back() != 7)
				&& ((*movements).back() != 8))
		{
			(*movements).push_back(1);
//			(*TabuList).push_back(*Current);
			return 1;
		}
	}

	if ((front > stepLength) && ((*Current).getZ()>0))
	{
		switch (dirInt)
		{
		case 0:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 180:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 90:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 270:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 45:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 135:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 225:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 315:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		default:
			break;
		}
		tempSquare.setX(xTemp);
		tempSquare.setY(yTemp);
		tempSquare.setZ(zTemp);
		tempSquare.setDist(tempSquare.calcDist((*subGoal), d, method));

		if ((!isVisitedTS(xTemp, yTemp, zTemp, *TabuList, *localMinFlag)
				&& (!isTabu(xTemp, yTemp, zTemp, *tabuListLong))))
		{
			tempList.push_back(tempSquare);
			direction[directionCounter] = 1; // check for front
			directionCounter++;
		}
	}
	if (back > (stepLength * 2))
	{

		switch (dirInt)
		{
		case 0:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 180:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 90:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 270:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 45:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 135:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 225:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 315:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		default:
			// write here code for angles 45 later on
			break;
		}

		tempSquare.setX(xTemp);
		tempSquare.setY(yTemp);
		tempSquare.setZ(zTemp);
		tempSquare.setDist(tempSquare.calcDist((*subGoal), d, method));

		if ((!isVisitedTS(xTemp, yTemp, zTemp, *TabuList, *localMinFlag)
				&& (!isTabu(xTemp, yTemp, zTemp, *tabuListLong))))
		{
			tempList.push_back(tempSquare);
			direction[directionCounter] = 2;
			directionCounter++;
		}
	}

	if (right > (stepLength * 2))
	{

		switch (dirInt)
		{
		case 0:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 180:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 90:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 270:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 45:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 135:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 225:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 315:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		default:
			break;
		}

		tempSquare.setX(xTemp);
		tempSquare.setY(yTemp);
		tempSquare.setZ(zTemp);
		tempSquare.setDist(tempSquare.calcDist((*subGoal), d, method));

		if ((!isVisitedTS(xTemp, yTemp, zTemp, *TabuList, *localMinFlag)
				&& (!isTabu(xTemp, yTemp, zTemp, *tabuListLong))))
		{
			tempList.push_back(tempSquare);
			direction[directionCounter] = 3; // check for Right
			directionCounter++;
		}
	}
	if (left > (stepLength * 2))
	{

		switch (dirInt)
		{
		case 0:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 180:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 90:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 270:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 45:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 135:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() + stepLength;
			;
			zTemp = (*Current).getZ();
			break;
		case 225:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 315:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		default:
			// write here code for angles 45 later on
			break;
		}

		tempSquare.setX(xTemp);
		tempSquare.setY(yTemp);
		tempSquare.setZ(zTemp);
		tempSquare.setDist(tempSquare.calcDist((*subGoal), d, method));

		if ((!isVisitedTS(xTemp, yTemp, zTemp, *TabuList, *localMinFlag)
				&& (!isTabu(xTemp, yTemp, zTemp, *tabuListLong))))
		{
			tempList.push_back(tempSquare);
			direction[directionCounter] = 4; // check for left
			directionCounter++;
		}
	}

	if (rightFront > (stepLength * 100))
	{

		switch (dirInt)
		{
		case 0:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 45:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 90:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 135:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 180:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 225:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 270:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 315:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		default:
			break;
		}

		tempSquare.setX(xTemp);
		tempSquare.setY(yTemp);
		tempSquare.setZ(zTemp);
		tempSquare.setDist(tempSquare.calcDist((*subGoal), d, method));

		if ((!isVisitedTS(xTemp, yTemp, zTemp, *TabuList, *localMinFlag)
				&& (!isTabu(xTemp, yTemp, zTemp, *tabuListLong))))
		{
			tempList.push_back(tempSquare);
			direction[directionCounter] = 5;
			directionCounter++;
		}
//		else{
//			visitedNeighbours.push_back(tempSquare);
//			visitedDirections[visitedDirectionsCounter] = 5;
//			visitedDirectionsCounter++;
//		}
	}

	if (leftFront > (stepLength * 100))
	{

		switch (dirInt)
		{
		case 0:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 45:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 90:
			xTemp = (*Current).getX() - stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 135:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 180:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() + stepLength;
			zTemp = (*Current).getZ();
			break;
		case 225:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY();
			zTemp = (*Current).getZ();
			break;
		case 270:
			xTemp = (*Current).getX() + stepLength;
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		case 315:
			xTemp = (*Current).getX();
			yTemp = (*Current).getY() - stepLength;
			zTemp = (*Current).getZ();
			break;
		default:
			break;
		}

		tempSquare.setX(xTemp);
		tempSquare.setY(yTemp);
		tempSquare.setZ(zTemp);
		tempSquare.setDist(tempSquare.calcDist((*subGoal), d, method));

		if ((!isVisitedTS(xTemp, yTemp, zTemp, *TabuList, *localMinFlag)
				&& (!isTabu(xTemp, yTemp, zTemp, *tabuListLong))))
		{
			tempList.push_back(tempSquare);
			direction[directionCounter] = 6;
			directionCounter++;
		}
	}

	if ((2 - ground) > (stepLength * 2))
	{
		xTemp = (*Current).getX();
		yTemp = (*Current).getY();
		zTemp = (*Current).getZ() + stepLength;

		tempSquare.setX(xTemp);
		tempSquare.setY(yTemp);
		tempSquare.setZ(zTemp);
		tempSquare.setDist(tempSquare.calcDist((*subGoal), d, method));

		if ((!isVisitedTS(xTemp, yTemp, zTemp, *TabuList, *localMinFlag))
				&& (!isTabu(xTemp, yTemp, zTemp, *tabuListLong)))
		{
			tempList.push_back(tempSquare);
			direction[directionCounter] = 7;
			directionCounter++;
		}
	}
	if ((ground > (stepLength * 2)) && ((*Current).getZ() > 0))
	{
		xTemp = (*Current).getX();
		yTemp = (*Current).getY();
		zTemp = (*Current).getZ() - stepLength;

		tempSquare.setX(xTemp);
		tempSquare.setY(yTemp);
		tempSquare.setZ(zTemp);
		tempSquare.setDist(tempSquare.calcDist((*subGoal), d, method));

		if ((!isVisitedTS(xTemp, yTemp, zTemp, *TabuList, *localMinFlag))
				&& (!isTabu(xTemp, yTemp, zTemp, *tabuListLong)))
		{
			tempList.push_back(tempSquare);
			direction[directionCounter] = 8;
			directionCounter++;
		}
	}

	if (tempList.size() > 0)
	{
		double bestDist = tempList.front().getDist();
		Square bestSquare = tempList.front();
		int bestPos = 0;
		int j = tempList.size();
		for (int i = 0; i < j; i++)
		{
//			cout << "Current Distance " << tempList.front().getDist() << endl;
			if (tempList.front().getDist() < bestDist)
			{
				bestDist = tempList.front().getDist();
				bestSquare = tempList.front();
				bestPos = i;
			}
			tempList.push_back(tempList.front());
			tempList.pop_front();
		}

		for (int i = 0; i < j; i++)
		{
			tempList.front().setDist(tempList.front().calcDist(Goal, d, 2));
			if (!(isVisitedTS(bestSquare.getX(), bestSquare.getY(),
					bestSquare.getZ(), tempList, *localMinFlag)))
			{
				tempList.push_back(tempList.front());
			}
			tempList.pop_front();
		}

		j = tempList.size();

		for (int i = 0; i < j; i++)
		{
			(*openList).push_back(tempList.front());
			tempList.pop_front();
		}

		(*movements).push_back(direction[bestPos]);
		(*Current).setDist((*Current).calcDist(Goal, d, 2));
		if ((*localMinFlag)) // && (((*movements).back()!= 7) || ((*movements).back()!= 8))
		{
			cout << "Tabuing here forver................................."
					<< endl;
			(*tabuListLong).push_back((*Current));
		}
		else
		{
			if (((*decisionSquare).size() > 1)
					&& ((*subGoal).getVisited() == 1))
			{
				(*tabuListLong).push_back((*Current));
				cout << "Tabuing here as well................................."
						<< endl;
			}
			(*TabuList).push_back((*Current));
		}

		if (((*TabuList).size() > 20) && (!(*localMinFlag)))
		{
			(*TabuList).pop_front();
		}

		return direction[bestPos];
	}

	else
	{
		cout << "List empty" << endl;
		return -1;
	}

	return -10;
}

Square updateSubGoal(list<Square> *openList, list<Square> TabuList)
{

	int k = (*openList).size();
	for (int i = 0; i < k; i++)
	{
		if (isTabu((*openList).front().getX(), (*openList).front().getY(),
				(*openList).front().getZ(), TabuList))
		{
			(*openList).pop_front();
		}
		else
		{
			(*openList).push_back((*openList).front());
			(*openList).pop_front();
		}

	}

	Square subGoal = (*openList).front();
	double bestDist = (*openList).front().getDist();
	int j = (*openList).size();
	for (int i = 0; i < j; i++)
	{
//			cout << "Current Distance " << tempList.front().getDist() << endl;
		if ((*openList).front().getDist() <= bestDist)
		{
			bestDist = (*openList).front().getDist();
			subGoal = (*openList).front();
		}
		(*openList).push_back((*openList).front());
		(*openList).pop_front();
	}

	return subGoal;
}

bool isVisitedTS(double x, double y, double z, list<Square> TabuList,
		bool localMinFlag)
{

	Square temp = Square(0, 0, 0);
	double diffX;
	double diffY;
	double diffZ;

	int tabuListSize = TabuList.size();

	for (int i = 0; i < tabuListSize; i++)
	{
		temp.setX(TabuList.front().getX());
		temp.setY(TabuList.front().getY());
		temp.setZ(TabuList.front().getZ());

		diffX = fabs(temp.getX() - x);
		diffY = fabs(temp.getY() - y);
		diffZ = fabs(temp.getZ() - z);

		if ((diffX < 0.1) && (diffY < 0.1) && (diffZ < 0.1))
		{
			return true;
		}
		else
		{
			TabuList.pop_front();
			TabuList.push_back(temp);
		}
	}

	return false;
}
bool isTabu(double x, double y, double z, list<Square> TabuList)
{

	Square temp = Square(0, 0, 0);
	double diffX;
	double diffY;

	int tabuListSize = TabuList.size();

	for (int i = 0; i < tabuListSize; i++)
	{
		temp.setX(TabuList.front().getX());
		temp.setY(TabuList.front().getY());

		diffX = fabs(temp.getX() - x);
		diffY = fabs(temp.getY() - y);

		if ((diffX < 0.1) && (diffY < 0.1))
		{
			return true;
		}
		else
		{
			TabuList.pop_front();
			TabuList.push_back(temp);
		}
	}

	return false;
}
int angleFilter(double angle)
{
	int x = angle;
	switch (x)
	{
	case 0:
	case 1:
	case -1:
		return 0;
		break;
	case 180:
	case 179:
	case 181:
		return 180;
		break;
	case 90:
	case 91:
	case 89:
		return 90;
		break;
	case 270:
	case 271:
	case 269:
		return 270;
		break;
	case 45:
	case 44:
	case 46:
		return 45;
		break;
	case 135:
	case 134:
	case 136:
		return 135;
		break;
	case 225:
	case 224:
	case 226:
		return 225;
		break;
	case 315:
	case 314:
	case 316:
		return 315;
		break;
	default:
		cout << "Incorrect angle *************" << endl;
		return -1;
		break;
	}
	return -1;
}
