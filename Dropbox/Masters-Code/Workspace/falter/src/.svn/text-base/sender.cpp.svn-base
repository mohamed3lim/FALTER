/*
 * sender.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: alim
 */

#include <unistd.h>
#include <cstdlib>

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#include <iostream>
#include <fstream>
#include <string>
#include "exchange.pb.h"



using namespace std;

//int main(int argc, char* argv[]){
//
//	GOOGLE_PROTOBUF_VERIFY_VERSION;
//
////	if (argc != 2) {
////		cerr << "Usage:  " << argv[0] << " Exchange" << endl;
////		return -1;
////	}
//
//	// Sending
//	usData test;
//	test.set_srf_ceiling(1.1);
//	test.set_srf_front_ctr(2.1);
//	test.set_srf_front_lhs(3.1);
//	test.set_srf_front_rhs(4);
//	test.set_srf_gnd(5);
//	test.set_srf_lhs(6);
//	test.set_srf_rear(7);
//	test.set_srf_rhs(8);
//
//	image sentImage;
//
//	for(int i = 0; i < 10;i++){
//		sentImage.add_input_pmd(i+0.5);
//	}
//
//
////	cout << sentImage.input_pmd_size() << endl;
//
//	std::vector<uint32_t> encodedData;
//	encodedData.resize(test.ByteSize());
//	test.SerializeToArray(encodedData.data() ,encodedData.size());
//
//	//Recieving
//
//	usData receive;
//
//	receive.ParseFromArray(encodedData.data(),encodedData.size());
//
//	cout << receive.srf_ceiling() << endl;
//
//    google::protobuf::ShutdownProtobufLibrary();
//
//	return 0;
//}
//
