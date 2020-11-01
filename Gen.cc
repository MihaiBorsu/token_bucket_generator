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
#include <pthread.h>
#include <chrono>
#include <thread>

using namespace omnetpp;

class Gen : public cSimpleModule{
private:
    int no_sent;
    int no_of_packets_in_buffer;
    int generation_rate; // packets / second (random function works real random only if geneartion_rate is <=1 (max 1 ip per second))
    int transmission_rate; // packets / second
    cMessage *buffer[512]; // fixed sized buffer for now, to be done: dynamically allocate space into the buffer as it gets full

protected:
    virtual void initialize();
    virtual void generate_ip_packet(); // generates a random ip (i.e. 192.168.0.1), it constructs a packet using the ip and puts the packet in the buffer
    virtual void send_ip_packet(cMessage *ip);
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

Define_Module(Gen);

void Gen::initialize(){
    no_sent = 0;
    no_of_packets_in_buffer = 0;
    generation_rate = 10;
    transmission_rate = 10;

    while(no_sent < 4){
        this->generate_ip_packet();
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

}

void Gen::generate_ip_packet(){
    // generates 4 bytes of values between 1 and 255
    srand(time(NULL));
    int byte1 = rand() % 255 + 1;
    int byte2 = rand() % 255 + 1;
    int byte3 = rand() % 255 + 1;
    int byte4 = rand() % 255 + 1;

//    std::cout << "\nrandom generated numbers to form the ip are:" << "\n\n";
//    std::cout << byte1 << "\n";
//    std::cout << byte2 << "\n";
//    std::cout << byte3 << "\n";
//    std::cout << byte4 << "\n";
//    std::cout << "\n\n";

    // constructs the ip string
    std::string ip_string = "";

    ip_string += std::to_string(byte1);
    ip_string += ".";

    ip_string += std::to_string(byte2);
    ip_string += ".";

    ip_string += std::to_string(byte3);
    ip_string += ".";

    ip_string += std::to_string(byte4);

    // sleep to allow random function to work properly (not obtain the same values)
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // constructs the message to be sent to buffer
    std::cout << "\n";
    std::cout << "random generated ip is: " << "\n";
    std::cout << ip_string << "\n";
    cMessage *ip = new cMessage(ip_string.c_str());

//    std::cout << "trying to print cMessage object" << ip;

    // stores the message into the buffer
    buffer[no_of_packets_in_buffer] = ip;
    no_of_packets_in_buffer++;

    this->send_ip_packet(ip);
}

void Gen::send_ip_packet(cMessage *ip){
    send(ip,"out");
    no_sent++;
}

void Gen::handleMessage(cMessage *msg){
}

void Gen::finish(){
    //add code here
}
