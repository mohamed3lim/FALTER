        /*
 * 	$Id$
 * 	@levd.rating RED Hash: 04BAEFE1FDF2F3A6E13946F48720CB34
 *
 *  Created on: 26.08.2010
 *      @author bayha
 *      @author alim edited starting 15.08.2014
 */

#ifdef SIMULATION
// Defining MAGIC_VELOCITIES enables the simulation input of real velocities
//#define MAGIC_VELOCITIES
#include <mex.h>
#include <unistd.h>
#include <math.h>
// #include <iostream>
#include <unistd.h>
// #include <cstdlib>

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
#include "exchange.pb.h"

#include "variables_control.h"
#define PI 3.141592 
//#define POWER_LIMITATIONS
#endif
#include <errno.h>


#include <iostream>
using namespace std;
unsigned long int counter = 0;
unsigned long int start;
unsigned long int elapsed;

double angle;

int step = 0;
int next = 0;
int stepVertical = 0;
int flag = 1;
int directions[] = {1,1,1,1,1,1,1,1,6,1,3,1,3,1,3,1,5,1,2,1};
int sizeOfDirections = sizeof(directions)/sizeof(directions[0]);
int direction = 0;

bool goalReached = false;
bool moveError = false;

double elevations[] = {0.6,1,0.5,0.3,0.6};

float pmdArray[PMD_RES_HEIGHT][PMD_RES_WIDTH];
float USReadings[8];

int sizeOfElevations = sizeof(elevations)/sizeof(elevations[0]);

int curr = 0;
int prev = 0;

Data data;
SrfData *srf;

double srfMax = 6.0; // varry according to the sensor used

double stepLength = 0.5;

// Server variables
int sockSr;
struct sockaddr_in server_socket_sr;
struct sockaddr_in client_socket_sr;
int oneSr = 1;
int received;
socklen_t client_len_sr = sizeof(client_socket_sr);
queue<int> directionsQueue;
//----------------

// Client Variables
int sockCl;
struct sockaddr_in server_socket_Cl;
int oneCl = 1;

//---------------------------

void client_main();
void server_main();
void nickControl();
double srfFilter(double srfValue);

extern "C" int ctrl_init()
{
#ifdef SIMULATION
    
    angle = 0; //90
    *output_gas = 140;
    *output_yaw = 0;
    *output_nick = 0;
    *output_roll = 0;
    *output_elevation = 0; //[-23 0.12 -4]  0.12
    *output_x = 0; //23
    *output_y = 0; //-4
    *output_desired_yaw = 0; //[0 (-pi*1)/2 0] PI/2
    
    // Server Sockets initialization


	if ((sockSr = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        cout <<"Error number is" << errno << endl;//fflush(stdout);sleep(1);
        exit(0);
    }

	setsockopt(sockSr, SOL_SOCKET, SO_REUSEPORT, &oneSr, sizeof(oneSr));

	memset(&server_socket_sr, 0, sizeof(server_socket_sr));
	server_socket_sr.sin_family = AF_INET;
	server_socket_sr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_socket_sr.sin_port = htons(5554);

	if (bind(sockSr, (struct sockaddr *) &server_socket_sr, sizeof(server_socket_sr)) < 0)
		exit(0);
    //------------------------------------------------------
    // Client Socket Initialization
    if ((sockCl = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        exit(0);
    
    setsockopt(sockCl, SOL_SOCKET, SO_BROADCAST, &oneCl, sizeof(oneCl));
    memset(&server_socket_Cl, 0, sizeof(server_socket_Cl));
    server_socket_Cl.sin_family = AF_INET;
    //server_socket_Cl.sin_addr.s_addr = inet_addr("192.168.20.255");
//     server_socket_Cl.sin_addr.s_addr = inet_addr("10.149.187.255");
    server_socket_Cl.sin_addr.s_addr = inet_addr("50.0.30.239"); // GUC
    server_socket_Cl.sin_port = htons(5555);
    //----------------------------


    
//     pmdHeight = PMD_RES_HEIGHT;
//     pmdWidth = PMD_RES_WIDTH;
//     *output_x = *input_x_position;
//     *output_y = *input_y_position;
	//mexPrintf("Init\n");
#endif
}


void moveForward(){
    
//     int x = (int) (*output_desired_yaw * (180/PI));
    int x = angle;

    if(flag == 1){
        step = 1;
        start = counter;
        switch (x) {
            case 0:
                *output_x = *output_x - stepLength;
                break;
            case 180:
                *output_x = *output_x + stepLength;
                break;
            case (90):
                *output_y = *output_y + stepLength;
                break;
            case (270):
                *output_y = *output_y - stepLength;
                break;
            case 45:
                *output_x = *output_x - stepLength;
                *output_y = *output_y + stepLength;
                break;
            case 135:
                *output_x = *output_x + stepLength;
                *output_y = *output_y + stepLength;
                break;
            case 225:
                *output_x = *output_x + stepLength;
                *output_y = *output_y - stepLength;
                break;
            case 315:
                *output_x = *output_x - stepLength;
                *output_y = *output_y - stepLength;
              break;
            default:
              // write here code for angles 45 later on
              break;
        }

        flag = 2;
    }
    
    if(flag = 2){
        elapsed = counter - start;
        nickControl();

        if(elapsed > 70){
            flag = 1;
            step = 2;
            next ++;
        }
    }

}

void nickControl(){
    
//     int x = (int) (*output_desired_yaw * (180/PI));
    int x = angle;
    
    switch (x) {
            case 0:

                *output_nick = -1*(*input_x_pid);
                *output_roll = (*input_y_pid);
                break;
            case 180:

                *output_roll = -1*(*input_y_pid);
                *output_nick = (*input_x_pid);

                break;
            case (90):
                *output_nick = *input_y_pid;
                *output_roll = (*input_x_pid);

                break;
            case (270):
                *output_nick = -1*(*input_y_pid);
                *output_roll = -1*(*input_x_pid);

                break;
            case 45:
                *output_nick = -1*(*input_x_pid);
                *output_roll = (*input_y_pid);
                break;
            case 135:
                *output_nick = *input_y_pid;
                *output_roll = (*input_x_pid);
                break;
            case 225:
                *output_roll = -1*(*input_y_pid);
                *output_nick = (*input_x_pid);
                break;
            case 315:
                *output_nick = -1*(*input_y_pid);
                *output_roll = -1*(*input_x_pid);
              break;
            default:
              // write here code for angles 45 later on
              break;
    }
}

void moveRight(){
    
    if(flag == 1){
        step = 1;
        start = counter;
        flag = 2;
    }
    
    if(flag == 2){
        elapsed = counter - start;
        if(elapsed < 150){
            nickControl();
        }
        else {
            flag = 3;
        }   
    }
    
    if(flag == 3){
        start = counter;
            flag = 4;
//             int x = (int) (*output_desired_yaw * (180/PI));
            int x = angle;
            
            switch (x) {
                case 0:
                    *output_desired_yaw = 0.5*PI;
                    angle = 90;
                    break;
                case 45:
                    *output_desired_yaw = (0.75*PI);
                    angle = 135;
                    break;
                case 90:
                    *output_desired_yaw = PI;
                    angle = 180;
                    break;
                case 135:
                    *output_desired_yaw = (1.25*PI);
                    angle = 225;
                    break;
                case 180:
                    *output_desired_yaw = 1.5*PI;
                    angle = 270;
                    break;
                case 225:
                    *output_desired_yaw = (1.75*PI);
                    angle = 315;
                    break;
                case 270:
                    *output_desired_yaw = 0;
                    angle = 0;
                    break;
                case 315:
                    *output_desired_yaw = (0.25*PI);
                    angle = 45;
                  break;
                default:
                  break;
        }
            
    }

    if(flag == 4){
        elapsed = counter - start;
        
        if(elapsed > 300){
            flag = 1;
            step = 2;
            next ++;
        }
    }  
}

void moveLeft(){
    
    if(flag == 1){
        start = counter;
        step = 1; 
        flag = 2;
    }
    
    if(flag == 2){
        elapsed = counter - start;
        if(elapsed < 150){
            nickControl();
        }
        else {
            flag = 3;
        }   
    }
    
    if(flag == 3){
        start = counter;
            flag = 4;
            int x = angle;
            
            switch (x) {
                case 0:
                    *output_desired_yaw = 1.5*PI;
                    angle = 270;
                    break;
                case 45:
                    *output_desired_yaw = (1.75*PI);
                    angle = 315;
                    break;
                case 90:
                    *output_desired_yaw = 0;
                    angle = 0;
                    break;
                case 135:
                    *output_desired_yaw = (0.25*PI);
                    angle = 45;
                    break;
                case 180:
                    *output_desired_yaw = 0.5*PI;
                    angle = 90;
                    break;
                case 225:
                    *output_desired_yaw = (0.75*PI);
                    angle = 135;
                    break;
                case 270:
                    *output_desired_yaw = (PI);
                    angle = 180;
                    break;
                case 315:
                    *output_desired_yaw = (1.25*PI);
                    angle = 225;
                  break;
                default:
                  break;
        }
    }

    if(flag == 4){
        elapsed = counter - start;
        
        if(elapsed > 300){
            flag = 1;
            step = 2;
            next ++;
        }
    }  
}


void moveBackward(){
    if(flag == 1){
        start = counter;
        step = 1;
        flag = 2;
    }
    
    if(flag == 2){
        elapsed = counter - start;
        if(elapsed < 200){
            nickControl();
        }
        else {
            flag = 3;
        }   
    }
        
    if(flag == 3){
        start = counter;
        flag = 4;
        int x = angle;
    
        switch (x) {
                case 0:
                    *output_desired_yaw = PI;
                    angle = 180;
                    break;
                case 45:
                    *output_desired_yaw = (1.25*PI);
                    angle = 225;
                    break;
                case 90:
                    *output_desired_yaw = (1.5*PI);
                    angle = 270;
                    break;
                case 135:
                    *output_desired_yaw = (1.75*PI);
                    angle = 315;
                    break;
                case 180:
                    *output_desired_yaw = 0;
                    angle = 0;
                    break;
                case 225:
                    *output_desired_yaw = (0.25*PI);
                    angle = 45;
                    break;
                case 270:
                    *output_desired_yaw = (0.5*PI);
                    angle = 90;
                    break;
                case 315:
                    *output_desired_yaw = (0.75*PI);
                    angle = 135;
                  break;
                default:
                  // write here code for angles 45 later on
                  break;
        }
    }

    if(flag == 4){
        elapsed = counter - start;

        if(elapsed > 300){
            flag = 1;
            step = 2;
            next ++;
        }
    }  
}

void moveFwdRight(){
    if(flag == 1){
        step = 1;
        start = counter;
        flag = 2;
    }
    
    if(flag == 2){
        elapsed = counter - start;
        if(elapsed < 200){
            nickControl();
        }
        else {
            flag = 3;
        }   
    }
    
    if(flag == 3){
        start = counter;
            flag = 4;
            int x = angle;
            switch (x) {
                case 0:
                    *output_desired_yaw = 0.25*PI;
                    angle = 45;
                    break;
                case 45:
                    *output_desired_yaw = (0.5*PI);
                    angle = 90;
                    break;
                case 90:
                    *output_desired_yaw = 0.75*PI;
                    angle = 135;
                    break;
                case 135:
                    *output_desired_yaw = PI;
                    angle = 180;
                    break;
                case 180:
                    *output_desired_yaw = 1.25*PI;
                    angle = 225;
                    break;
                case 225:
                    *output_desired_yaw = (1.5*PI);
                    angle = 270;
                    break;
                case 270:
                    *output_desired_yaw = (1.75*PI);
                    angle = 315;
                    break;
                case 315:
                    *output_desired_yaw = 0;
                    angle = 0;
                  break;
                default:
                  break;
        }
    }

    if(flag == 4){
        elapsed = counter - start;
        
        if(elapsed > 300){
            flag = 1;
            step = 2;
            next ++;
        }
    }  
}

void moveFwdLeft(){
      if(flag == 1){
        start = counter;
        step = 1;
        flag = 2;
    }
    
    if(flag == 2){
        elapsed = counter - start;
        if(elapsed < 200){
            nickControl();
        }
        else {
            flag = 3;
        }   
    }
    
    if(flag == 3){
        start = counter;
            flag = 4;
            int x = angle;
            
            switch (x) {
                case 0:
                    *output_desired_yaw = 1.75*PI;
                    angle = 315;
                    break;
                case 45:
                    *output_desired_yaw = 0;
                    angle = 0;
                    break;
                case 90:
                    *output_desired_yaw = (0.25*PI);
                    angle = 45;
                    break;
                case 135:
                    *output_desired_yaw = 0.5*PI;
                    angle = 90;
                    break;
                case 180:
                    *output_desired_yaw = (0.75*PI);
                    angle = 135;
                    break;
                case 225:
                    *output_desired_yaw = (PI);
                    angle = 180;
                    break;
                case 270:
                    *output_desired_yaw = (1.25*PI);
                    angle = 225;
                    break;
                case 315:
                    *output_desired_yaw = 1.5*PI;
                    angle = 270;
                  break;
                default:
                  break;
        }
    }

    if(flag == 4){
        elapsed = counter - start;
        if(elapsed > 300){
            flag = 1;
            step = 2;
            next ++;
        }
    }
}

void moveVertical(double desiredHeight){
        

    *output_elevation = 0.12 + desiredHeight;
    
    if((*output_gas - *input_z_pid) > 50.0){
        *output_gas = *output_gas - 50.0;
    }
    else{
        if((*output_gas - *input_z_pid) < -50.0){
            *output_gas = *output_gas + 50.0;
        }
        else{
            *output_gas = *input_z_pid;
        }
    }
}
void moveUp(){
    
    if(flag == 1){
        start = counter;
        step = 1;
        flag = 2;
        *output_elevation = *output_elevation + stepLength;
    }
    
    if(flag == 2){
        elapsed = counter - start;
        nickControl();
        if(elapsed > 50){
            flag = 1;
            step = 2;
        } 
    }
    
}
void moveDown(){
    if(flag == 1){
        start = counter;
        step = 1;
        flag = 2;
        *output_elevation = *output_elevation - stepLength;
    }
    
    if(flag == 2){
        elapsed = counter - start;
        nickControl();
        if(elapsed > 50){
            flag = 1;
            step = 2;
        } 
    }
}

void rotate(){
    *output_yaw = *input_yaw_pid;
}

void elevate(){
    
    if((*output_gas - *input_z_pid) > 50.0){
        *output_gas = *output_gas - 50.0;
    }
    else{
        if((*output_gas - *input_z_pid) < -50.0){
            *output_gas = *output_gas + 50.0;
        }
        else{
            *output_gas = *input_z_pid;
        }
    }
}

void move(int direction){
    
    switch (direction) {
        case 1: moveForward(); break;
        case 2: moveBackward(); break;
        case 3: moveRight(); break;
        case 4: moveLeft(); break;
        case 5: moveFwdRight(); break;
        case 6: moveFwdLeft(); break;
        case 7: moveUp(); break;
        case 8: moveDown();break;
        default: return;break;
    }
}


void updatePmdArray(){
    
    int i;
    int j;
    int k = 0;
    
    for(i = 0;i < PMD_RES_HEIGHT;i++){
        for(j = 0; j < PMD_RES_WIDTH; j++){
            pmdArray[i][j] = input_pmd[k];
            k++;
        }
    }
    
}

double srfFilter(double srfValue){
    if(srfValue == 0){
        return srfMax;
    }
    else{
        return srfValue;
    }
}

extern "C" void ctrl_step()
{   

    if(counter == 0){
        client_main();
    }
    
    counter ++;
    
    
    if(counter <= 10){
        *output_gas = 140;
        *output_nick = 0;
        *output_roll = 0;
    }
    else{
        rotate();
        elevate();
      
        
// //         *output_elevation = 1; // variable 1.12
// //         *output_x = 1; //Variable 24
// //         *output_y = 1; //variable -3
//         *output_desired_yaw = PI/2;
//         nickControl();

// // ---------------------------------------------------------------------        
        if(goalReached){
            nickControl();
            return;
        }
        if(moveError){
            nickControl();
            return;
        }
        
        if(step == 0){
            server_main();
            move(direction);
            cout<< "Command recieving and currently moving......."<< endl;
        }
        if(step == 2){
            client_main();
            cout << "Sending senseor data ......." << endl;
            step = 0;
        }
            
        if((direction > 0) && (direction < 9) && (step == 1)){
            move(direction);
        }
        else{
            if(direction < 0){ //check 0 or -1
                cout << "Movement error: " << direction << endl;
                moveError = true;
                cout << "Counter: " << counter << endl;
                return;
            }
            if(direction == 1000){
                cout << "Goal Reached" << endl;
                goalReached = true;
                nickControl();
                cout << "Counter: " << counter << endl;
            }
            if((direction > 8) && (direction != 1000)){
                cout << "invalid instruction : " << direction << endl;
                moveError = true;
                return;
            }     

        }
// // ----------------------------------------------------------------------------           
    }
}


void client_main()
{
    
    Data data;
    SrfData *srf;
    Image *image;
    
    data.set_xpos(*output_x);
    data.set_ypos(*output_y);
    data.set_zpos(*output_elevation - 0.12);
    data.set_currangle(angle);
    
    srf = data.add_srfdata();
    srf->set_srf_gnd(srfFilter(*srf_gnd));
    srf->set_srf_rhs(srfFilter(*srf_rhs));
    srf->set_srf_lhs(srfFilter(*srf_lhs));
    srf->set_srf_front_rhs(srfFilter(*srf_front_rhs));
    srf->set_srf_front_ctr(srfFilter(*srf_front_ctr));
    srf->set_srf_front_lhs(srfFilter(*srf_front_lhs));
    srf->set_srf_rear(srfFilter(*srf_rear));
    srf->set_srf_ceiling(srfFilter(*srf_ceiling));
    
    cout << "-------------------------------------------------------------------" << endl; 
    cout << "Front distance:                     " << srfFilter(*srf_front_ctr) << endl;
    cout << "Back distance:                      " << srfFilter(*srf_rear) << endl;
    cout << "Right distance:                     " << srfFilter(*srf_rhs) << endl;
    cout << "left distance:                      " << srfFilter(*srf_lhs) << endl;
    cout << "Front right distance: " << srfFilter(*srf_front_rhs) << endl;
    cout << "Front left distance: " << srfFilter(*srf_front_lhs) << endl;
    cout << "ceiling distance: " << srfFilter(*srf_ceiling) << endl;
    cout << "Gnd distance: " << srfFilter(*srf_gnd) << endl;
    cout << "Angle: " << angle << endl;
     
    
    image = data.add_image();
    
    for(int i = 0; i < (PMD_RES_HEIGHT*PMD_RES_WIDTH); i++){
            image->add_input_pmd(input_pmd[i]);
//             cout << input_pmd[i] << " ";
//             if((i != 0) && ((i%11) == 0)){
//                 cout <<endl;
//             }
    }
    
    std::vector<uint32_t> encodedData;
    encodedData.resize(data.ByteSize());
	data.SerializeToArray(encodedData.data() ,encodedData.size());
    
//     for(int i = 0; i < encodedData.size();i ++)
// 			cout << encodedData.at(i) << "  ";
// 		cout << "\n**"<<encodedData.size()<<"\n";
    if (sendto(sockCl, encodedData.data(), encodedData.size(), 0, (struct sockaddr *) &server_socket_Cl, sizeof(server_socket_Cl)) < 0)
        {
            cout << "sending error number: "<< errno << endl;
            return;
        }
}

void server_main(){
    
    int buffer[1];
    
    if ((received = recvfrom(sockSr, (char*)buffer, sizeof(int), 0, (struct sockaddr *) &client_socket_sr, &client_len_sr)) < 0 ) 
    if ( errno == EAGAIN)
    {
        return ;
    }
    else
    if ( errno == EWOULDBLOCK)
    {
        return ;
    }
    else
    if ( received  < 0)
    {
//         exit(0);
    }


    directionsQueue.push(buffer[0]);
    direction = buffer[0];
    cout << "Direction: " << buffer[0] << endl;
}

