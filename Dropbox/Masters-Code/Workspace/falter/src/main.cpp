#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

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
#include "TS.h"
//#include "SA.h"
#include "math.h"

#define PI 3.141592

using namespace cv;
using namespace std;

void server_main();
void client_main(int x);
void varInit();
void updatePmdArray(Data receive);
int TS(list<Square> *openList, list<Square> *tabuListShort,
		list<Square> *tabuListLong, Square *Current, Square Goal, Square *Start,
		list<Square> *decisionSquare, list<int> *movements, bool *localMinFlag,
		int method, double stepLength, double *error);

//int SA(list<Square> *openList, Square *Current, Square Goal,
//		list<int> *movements, bool *localMinFlag, int method, double stepLength,
//		double *globalMin, double *localMin, double *temperature);

// Server Variables
int sockSr;
struct sockaddr_in server_socket_sr;
struct sockaddr_in client_socket_sr;
int oneSr = 1;
socklen_t client_len;
queue<Data> dataQueue;
//------------------------

//Client Variables
int sockCl;
struct sockaddr_in server_socket_cl;
int oneCl = 1;
int buffer[] ={ 1 };
//------------------------------
#define PMD_RES_HEIGHT            32
#define PMD_RES_WIDTH             24

Mat pmdArray(32, 24, CV_32F);
//------------------------------

Square Current = Square(0, 0, 0);
list<Square> decisionSquare;
list<int> movements;
list<Square> openList;
list<Square> tabuListShort;
list<Square> tabuListLong;
Data d;
double errorVar = 100;
double temperature = 5;
double globalMin = -1;
//double localMin = -1;

bool localMinFlag;

int imFlag;

int main()
{
	varInit();
//	Square Goal = Square(-23, 4, 1);
//	Square Goal = Square(21, 4, 1);
	Square Goal = Square(-21, 5, 1);
//	Square Goal = Square(-23, -5, 1);

//	Square Goal = Square(21, 12, 1);
//	Square Goal = Square(-8, 1, 1);

	server_main();
	d = dataQueue.back();
	localMinFlag = false;
	int x = 0;
	Square Start = Square(d.xpos(), d.ypos(), d.zpos());
	while ((x != -1) && (x != 1000))
	{
//		x = SA(&openList, &Current, Goal, &movements, &localMinFlag, 2, 0.5,
//				&globalMin, &localMin, &temperature);
		x = TS(&openList, &tabuListShort, &tabuListLong, &Current, Goal, &Start,
				&decisionSquare, &movements, &localMinFlag, 2, 0.5, &errorVar);
	}
	return 0;
}

double filterZ(double z)
{
	if (z < 0.1)
	{
		return 0;
	}
	else
	{
		return z;
	}
}

//int SA(list<Square> *openList, Square *Current, Square Goal,
//		list<int> *movements, bool *localMinFlag, int method, double stepLength,
//		double *globalMin, double *localMin, double *temperature)
//{
//	double diffX;
//	double diffY;
//	double diffZ;
//	int x;
//
//	(*Current).setX(dataQueue.back().xpos());
//	(*Current).setY(dataQueue.back().ypos());
//	(*Current).setZ(filterZ(dataQueue.back().zpos()));
//	(*Current).setDist((*Current).calcDist(Goal, d, 2));
//	diffX = fabs((*Current).getX() - Goal.getX());
//	diffY = fabs((*Current).getY() - Goal.getY());
//	diffZ = fabs((*Current).getZ() - Goal.getZ());
//
//	if ((diffX > 0.1) || (diffY > 0.1) || (diffZ > 0.1))
//	{
////		(*Current).incrVisited();
////		cout << " Current Xcord " << (*Current).getX() << endl;
////		cout << " Current Ycord " << (*Current).getY() << endl;
////		cout << " Current Zcord " << (*Current).getZ() << endl;
//		d = dataQueue.back();
//		x = nextStepSA(openList, d, Current, Goal, movements, localMinFlag,
//				method, stepLength, globalMin, localMin, temperature);
//		cout << "Step " << x << endl;
//		client_main(x);
//		server_main();
//		return x;
//	}
//	else
//	{
//		cout << "Goal Reached" << endl;
//		client_main(1000);
//		return 1000;
//	}
//
//	return 0;
//}

int TS(list<Square> *openList, list<Square> *tabuListShort,
		list<Square> *tabuListLong, Square *Current, Square Goal, Square *Start,
		list<Square> *decisionSquare, list<int> *movements, bool *localMinFlag,
		int method, double stepLength, double *error)
{

	double diffX;
	double diffY;
	double diffZ;
	int x;

	(*Current).setX(dataQueue.back().xpos());
	(*Current).setY(dataQueue.back().ypos());
	(*Current).setZ(filterZ(dataQueue.back().zpos()));
	(*Current).setDist((*Current).calcDist(Goal, d, 2));
	diffX = fabs((*Current).getX() - Goal.getX());
	diffY = fabs((*Current).getY() - Goal.getY());
	diffZ = fabs((*Current).getZ() - Goal.getZ());

	if ((diffX > 0.1) || (diffY > 0.1) || (diffZ > 0.1))
	{
//		(*Current).incrVisited();
		cout << " Current Xcord " << (*Current).getX() << endl;
		cout << " Current Ycord " << (*Current).getY() << endl;
		cout << " Current Zcord " << (*Current).getZ() << endl;
		d = dataQueue.back();
		if ((*localMinFlag))
		{
			(*openList).push_back((*Current));
		}
		x = nextStepTS(d, openList, tabuListShort, tabuListLong, Current, Goal,
				Start, decisionSquare, movements, localMinFlag, method,
				stepLength, error);
		cout << "Step " << x << endl;
		client_main(x);
		server_main();
		return x;
	}
	else
	{
		cout << "Goal Reached" << endl;
		client_main(1000);
		return 1000;
	}
}

void varInit()
{

	imFlag = 1;
	//Server Initialization
	if ((sockSr = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		exit(0);

	setsockopt(sockSr, SOL_SOCKET, SO_REUSEPORT, &oneSr, sizeof(oneSr));

	memset(&server_socket_sr, 0, sizeof(server_socket_sr));
	server_socket_sr.sin_family = AF_INET;
	server_socket_sr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_socket_sr.sin_port = htons(5555);

	client_len = sizeof(client_socket_sr);

	if (bind(sockSr, (struct sockaddr *) &server_socket_sr,
			sizeof(server_socket_sr)) < 0)
		exit(0);
	//------------------------------------------------------------------

	//Client Initialization
	if ((sockCl = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		exit(0);

	setsockopt(sockCl, SOL_SOCKET, SO_BROADCAST, &oneCl, sizeof(oneCl));

	memset(&server_socket_cl, 0, sizeof(server_socket_cl));
	server_socket_cl.sin_family = AF_INET;
	//server_socket_cl.sin_addr.s_addr = inet_addr("192.168.20.255"); // fortiss
//	server_socket_cl.sin_addr.s_addr = inet_addr("10.149.187.255");
	server_socket_cl.sin_addr.s_addr = inet_addr("50.0.30.239"); // GUC
	server_socket_cl.sin_port = htons(5554);
	//-----------------------------------------------------------------
	cout << "Init Done" << endl;
}

void server_main()
{
//	cout << "s" << endl;
	Data receive;
//	SrfData srf;
	int rcv;
	std::vector<uint32_t> encodedData;
//	receive.ParseFromArray(encodedData.data(),encodedData.size());

//	encodedData.reserve(65536);
	encodedData.resize(65536);

	if ((rcv = recvfrom(sockSr, encodedData.data(), 65536, 0,
			(struct sockaddr *) &client_socket_sr, &client_len)) < 0)
	{
		cout << "Recieving error number: " << errno << endl;
		return;
		//exit(0);
	}

	receive.ParseFromArray(encodedData.data(), encodedData.size());
	//	updatePmdArray(&(receive.image(0).input_pmd()));
	dataQueue.push(receive);
//	updatePmdArray(receive.image(0).input_pmd().Mutable(0));

//	for(int i = 0; i < 192; i++){
//		cout << receive.image(0).input_pmd(i) << " ";
////		if((i != 0) && ((i%12) == 0)){
////			cout <<endl;
////		}
//	}
//	cout <<endl;

	updatePmdArray(receive);

//	if (imFlag == 1)
//	{
//		namedWindow("Display window", WINDOW_NORMAL); // Create a window for display.
//		imFlag = 0;
//	}

	Mat M = getRotationMatrix2D(
			Point((PMD_RES_WIDTH / 2), (PMD_RES_HEIGHT / 2)), -90, 1);
	Mat rotatedImg;
	warpAffine(pmdArray, rotatedImg, M, pmdArray.size());

	rotatedImg = rotatedImg / 15;
	Mat final;
	flip(rotatedImg, final, 1);

//	imshow("Display window", final);
//    cout << pmdArray <<endl;
	waitKey(10);

}
void updatePmdArray(Data receive)
{

	int i;
	int j;
	int k = 0;

//    cout<< "pmd:" <<input_pmd[k] << endl;

	for (i = 0; i < PMD_RES_HEIGHT; i++)
	{
		for (j = 0; j < PMD_RES_WIDTH; j++)
		{
			pmdArray.at<float>(i, j) = receive.image(0).input_pmd(k);
//            cout << pmdArray.at<float>(i,j);
//            cout<< "  " <<receive.image(0).input_pmd(k) << endl;
			k++;
		}
	}

}
void client_main(int x)
{
//	cout << "c\n" << endl << endl;

	buffer[0] = x;
	int sent;
//		sleep(1);
//	usleep(200000);
	//         sizeof(int) // argument 3 in sendto
	//sent = send(sock, (char*)buffer, sizeof(int), MSG_DONTWAIT, (struct sockaddr *) &server_socket, sizeof(server_socket)
	if ((sent = sendto(sockCl, (char*) buffer, sizeof(int), 0,
			(struct sockaddr *) &server_socket_cl, sizeof(server_socket_cl)))
			< 0)
	{
//			cout << "here --------------" << buffer[0] << endl;
//			cout << "Error number is : " << errno << endl<<endl;
		if (errno == EAGAIN)
		{
//					cout << "here 1 and the buffer value is : "<< buffer[0]<< endl;
			return;
		}
		else if ( errno == EWOULDBLOCK)
		{
			cout << "here 2" << endl;
			return;
		}
		else
		{
			return;
//					exit(0);
		}
	}
//		cout << "here buffer is incremented-----------------------------" << buffer[0]<< endl;
//	buffer[0] = buffer[0] + 1;
//			usleep(10000);
//	cout <<"buffer: "<< buffer[0] << endl;
}
