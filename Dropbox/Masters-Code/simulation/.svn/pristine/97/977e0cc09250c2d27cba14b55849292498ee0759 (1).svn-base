/*
 * 	$Id$
 * 	@levd.rating RED Hash: 04BAEFE1FDF2F3A6E13946F48720CB34
 *
 *  Created on: 26.08.2010
 *      @author bayha
 *      @author alim
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

#include "variables_control.h"
#define PI 3.141592 
//#define POWER_LIMITATIONS
#endif

unsigned long int counter = 0;
unsigned long int start;
unsigned long int elapsed;
int step = 0;
int stepVertical = 0;
int flag = 1;
int rotationFlag = 0;
int directions[] = {1,1,1,1,1,1,1,1,4,1,1,1,1,2,1,1,1,1,3,1,1,1,1,1,1,1,1};
int sizeOfDirections = sizeof(directions)/sizeof(directions[0]);

double elevations[] = {0.6,1,0.5,0.3};

float pmdArray[PMD_RES_HEIGHT][PMD_RES_WIDTH];
float USReadings[8];
// int pmdHeight;
// int pmdWidth;

int sizeOfElevations = sizeof(elevations)/sizeof(elevations[0]);



void client_main();

void nickControl();

int ctrl_init()
{
#ifdef SIMULATION
    *output_desired_yaw = PI/2;
    *output_gas = 140;
    *output_yaw = 0;
    *output_nick = 0;
    *output_roll = 0;
    *output_elevation = 0.12; // variable
    *output_x = -23; //Variable
    *output_y = -4; //variable


    
//     pmdHeight = PMD_RES_HEIGHT;
//     pmdWidth = PMD_RES_WIDTH;
//     *output_x = *input_x_position;
//     *output_y = *input_y_position;
	//mexPrintf("Init\n");
#endif
}


void moveForward(){
    
    int x = (int) (*output_desired_yaw * (180/PI));

    if(flag == 1){
        start = counter;
        switch (x) {
            case 0:
              *output_x = *output_x + 0.5;
              break;
            case 180:
              *output_x = *output_x - 0.5;
              break;
            case (90):
              *output_y = *output_y + 0.5;
              break;
            case (270):
              *output_y = *output_y - 0.5;
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

        if(elapsed > 5){
            flag = 1;
            step ++;
        }
    }

}

void nickControl(){
    
    int x = (int) (*output_desired_yaw * (180/PI));
    
    switch (x) {
            case 0:
              *output_nick = *input_x_pid;
              *output_roll = (*input_y_pid);
              break;
            case 180:
              *output_nick = -1*(*input_x_pid);
              *output_roll = -1*(*input_y_pid);
              break;
            case (90):
              *output_nick = *input_y_pid;
              *output_roll = -1*(*input_x_pid);
              break;
            case (270):
              *output_nick = -1*(*input_y_pid);
              *output_roll = (*input_x_pid);
              break;
            default:
              // write here code for angles 45 later on
              break;
    }
}

void moveRight(){
    
    if(flag == 1){
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
            if(*output_desired_yaw == 1.5*PI){
                *output_desired_yaw = 0;
            }
            else{ 
                *output_desired_yaw = *output_desired_yaw + (PI/2);
            }
    }

    if(flag == 4){
        elapsed = counter - start;
        
        if(elapsed > 300){
            flag = 1;
            step ++;
            moveForward();
        }
    }  
}

void moveLeft(){
    
    if(flag == 1){
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
            if(*output_desired_yaw == 0){
                *output_desired_yaw = 1.5*PI;
            }
            else{ 
                *output_desired_yaw = *output_desired_yaw - (PI/2);
            }
    }

    if(flag == 4){
        elapsed = counter - start;
        
        if(elapsed > 300){
            flag = 1;
            step ++;
            moveForward();
        }
    }  
}


void moveBackward(){
    if(flag == 1){
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

        if(*output_desired_yaw == 0){
            *output_desired_yaw = PI;
        }
        else{
            if(*output_desired_yaw == (PI/2)){
                *output_desired_yaw = 1.5*PI;
            }
            else{ 
                *output_desired_yaw = *output_desired_yaw - PI;
            }
        }
    }

    if(flag == 4){
        elapsed = counter - start;

        if(elapsed > 350){
            flag = 1;
            step ++;
            moveForward();
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

void rotate(){
    *output_yaw = *input_yaw_pid;
}

void move(int direction){
    
    switch (direction) {
        case 1: moveForward(); break;
        case 2: moveBackward(); break;
        case 3: moveRight(); break;
        case 4: moveLeft(); break;
        default: break;
    }
}


void updatePmdArray(){
    
    int i;
    int j;
    int k = 0;
    
    for(i = 0;i < PMD_RES_HEIGHT;i++){
        for(j = 0; j < PMD_RES_WIDTH; j++){
            pmdArray[i][j] = input_pmd[k];
//             mexPrintf("%f ",pmdArray[i][j]);
            k++;
        }
//         mexPrintf("\n");
    }
    
}

void ctrl_step()
{   
    counter ++;
    if(counter > 150){
        if(step < sizeOfDirections){
            move(directions[step]);
//             updatePmdArray();
        }
        else{
            nickControl();
        }
    }
    
    if(stepVertical < sizeOfElevations){
        moveVertical(elevations[stepVertical]);
    }
    else{
        moveVertical(elevations[sizeOfElevations-1]);
    }
    
    stepVertical = counter / 300;
    USReadings[0] = *srf_gnd;
    USReadings[1] = *srf_rhs;
    USReadings[2] = *srf_lhs;
    USReadings[3] = *srf_front_rhs;
    USReadings[4] = *srf_front_ctr;
    USReadings[5] = *srf_front_lhs;
    USReadings[6] = *srf_rear;
    USReadings[7] = *srf_ceiling;
    
    rotate();
//     updatePmdArray();
     client_main();
//     mexPrintf("GND %f \n", USReadings[1]);
//     mexPrintf("output_x %f \n", *output_x);
}

void client_main()
{
// 	cout << "c\n";
	int sock;
	struct sockaddr_in server_socket;
    
    int sock2;
	struct sockaddr_in server_socket2;

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		exit(0);

    if ((sock2 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		exit(0);
    
    int one=1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &one, sizeof(one));
    memset(&server_socket, 0, sizeof(server_socket));
    server_socket.sin_family = AF_INET;
    server_socket.sin_addr.s_addr = inet_addr("192.168.20.255");
    server_socket.sin_port = htons(5555);
    
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &one, sizeof(one));
    memset(&server_socket2, 0, sizeof(server_socket2));
    server_socket2.sin_family = AF_INET;
    server_socket2.sin_addr.s_addr = inet_addr("192.168.20.255");
    server_socket2.sin_port = htons(5554);
    
	float buffer[] = {1.0,1.1,1.2,1.3,1.4};
    //while(1)
//    {   
// 		buffer[0] = buffer[0] + 1;
    if (sendto(sock, input_pmd, ((sizeof(one))*(PMD_RES_HEIGHT*PMD_RES_WIDTH)), 0, (struct sockaddr *) &server_socket, sizeof(server_socket)) < 0)
        {
//             mexPrintf("");
//             exit(0);
        }
    if (sendto(sock, buffer, ((sizeof(one))*5), 0, (struct sockaddr *) &server_socket2, sizeof(server_socket2)) < 0)
        {
//             mexPrintf("");
//             exit(0);
        }
// 	sleep(1);
//    }
    
//     mexPrintf("%f \n", input_pmd[191]);
    shutdown (sock, 1);
    close(sock);
    
    shutdown (sock2, 1);
    close(sock2);
}



// void oneStep(String direction){
//     
// }
