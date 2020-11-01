/*
 * Gen.cc
 *
 *  Created on: Nov 1, 2020
 *      Author: mihai
 */

#include<omnetpp.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

using namespace omnetpp;

class TokenBucket: public cSimpleModule{
private:
    int no_rcvd;
    int no_of_packets_in_buffer;
    cMessage *buffer[512]; // fixed size of buffer for the received

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *ip);
    virtual void finish();
};

Define_Module(TokenBucket);


void TokenBucket::initialize(){
    no_rcvd = 0;
    no_of_packets_in_buffer = 0;
}

void TokenBucket::handleMessage(cMessage *ip){
    no_rcvd++;
    buffer[no_of_packets_in_buffer] = ip;
    no_of_packets_in_buffer++;

    std::cout << "\nip has been received! it is:" << "\n\n" << ip << "\n\n";
}

void TokenBucket::finish(){
    //add code here
}
