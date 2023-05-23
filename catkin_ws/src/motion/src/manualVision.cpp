/*
* Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*/

#include <iostream>
#include "ros/ros.h"
#include "motion/legoFound.h"
#include "motion/eventResult.h"

using namespace std;

#define node_name "manual_vision_module"
#define pub_detect_commander "/vision/detectCommander"   
#define sub_detect_resulter "/planner/detectResulter"              

#define no_command 0
#define command_detect 1
#define command_quit 2

#define queque_size 10
#define loop_wait_rate 1000 // 1 secondo di attesa

ros::Publisher pub_detect_commander_handle; 
ros::Subscriber sub_detect_resulter_handle;      

bool is_real_robot = false;              

double un_momento;

struct WaitingTask {
        int command_id;
        double request_time;
        bool attesa;
};

WaitingTask task_attesa;

motion::legoFound msg_lego_detect;                       
motion::eventResult msg_evento_detect;

void pubDetectCommander(bool s_ack);
void subDetectResulterCallback(const motion::eventResult::ConstPtr &msg_evento);
double getTimeNow();
double getInterval(double start_t);

int main(int argc, char **argv) {

        cout << "----------------------------" << endl;
        cout << "Starting the manual vision module!" << endl;
        cout << "----------------------------" << endl;
    
        ros::init(argc, argv, node_name);
        ros::NodeHandle node_handle;
        cout << "Node: " << node_name << " initialized!" << endl;

        pub_detect_commander_handle = node_handle.advertise<motion::legoFound>(pub_detect_commander, queque_size);
        cout << "Publisher: " << pub_detect_commander << " enabled with queque: " << queque_size << endl;

        sub_detect_resulter_handle = node_handle.subscribe(sub_detect_resulter, queque_size, subDetectResulterCallback);
        cout << "Subscriber: " << sub_detect_resulter << " enabled with queque: " << queque_size << endl;

        ros::Rate loop_rate(loop_wait_rate);
        task_attesa.attesa = false;

        cout << "----------------------------" << endl;
        cout << "Manual vision module ready!" << endl;
        cout << "----------------------------" << endl << endl;

        cout << "Waiting for the planner module..." << endl;
        while (pub_detect_commander_handle.getNumSubscribers() < 1) { loop_rate.sleep(); }
        cout << "Planner module connected!" << endl;

        while (ros::ok()) {                       

                if (!task_attesa.attesa) {             

                        cout << "Insert the command id: ";
                        cin >> msg_lego_detect.command_id;

                        cout << "Insert the lego class: ";
                        cin >> msg_lego_detect.lego_class;

                        cout << "Insert the lego position (x y z): ";
                        cin >> msg_lego_detect.coord_x >> msg_lego_detect.coord_y >> msg_lego_detect.coord_z;
                        
                        cout << "Insert the lego orientation (roll pitch yaw): ";
                        cin >> msg_lego_detect.rot_roll >> msg_lego_detect.rot_pitch >> msg_lego_detect.rot_yaw;

                        cout << "Insert a comment: ";
                        cin >> msg_lego_detect.comment;

                        cout << "Send ack? ";
                        bool send_the_ack;
                        cin >> send_the_ack;
                        pubDetectCommander(send_the_ack);
                }       

                ros::spinOnce();
        }

        cout << endl;
        cout << "Exit process invoked, closing planner module!" << endl;
        return 0;    
}

void pubDetectCommander(bool s_ack) {

        msg_lego_detect.date_time = getTimeNow();
        msg_lego_detect.send_ack = s_ack;
        pub_detect_commander_handle.publish(msg_lego_detect);

        cout << "---------------------------------------" << endl;
        cout << "Publisher: " << pub_detect_commander << " sent some data:" << endl;      
        cout << "---------------------------------------" << endl;   
        cout << "Command ID " << msg_lego_detect.command_id << endl;
        cout << "Lego class: " << msg_lego_detect.lego_class << endl;
        cout << "X coordinate: " << msg_lego_detect.coord_x << endl;
        cout << "Y coordinate: " << msg_lego_detect.coord_y << endl;
        cout << "Z coordinate: " << msg_lego_detect.coord_z << endl;
        cout << "Roll orientation: " << msg_lego_detect.rot_roll << endl;
        cout << "Pitch orientation: " << msg_lego_detect.rot_pitch << endl;
        cout << "Yaw orientation: " << msg_lego_detect.rot_yaw << endl;
        cout << "Request datetime: " << msg_lego_detect.date_time << endl;
        cout << "Comment: " << msg_lego_detect.comment << endl;
        cout << "ACK: " << msg_lego_detect.send_ack << endl;
        cout << "---------------------------------------" << endl;
        
        if (s_ack) {

                task_attesa.command_id = msg_lego_detect.command_id;
                task_attesa.request_time = msg_lego_detect.date_time;
                task_attesa.attesa = true;

                cout << "Processo " << task_attesa.command_id << " messo in attesa" << endl;
        
        } else {

                task_attesa.attesa = false;                
        }
}

void subDetectResulterCallback(const motion::eventResult::ConstPtr &msg_evento) {

        msg_evento_detect.event_id = msg_evento->event_id;
        msg_evento_detect.result_id = msg_evento->result_id;
        msg_evento_detect.start_time = msg_evento->start_time;
        msg_evento_detect.duration_time = msg_evento->duration_time;
        msg_evento_detect.comment = msg_evento->comment;

        cout << "---------------------------------------" << endl;
        cout << "Subscriber: " << sub_detect_resulter << " received some data:" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Event ID: " << msg_evento_detect.event_id << endl;
        cout << "Result ID: " << msg_evento_detect.result_id << endl;
        cout << "Start time: " << msg_evento_detect.start_time << endl;
        cout << "Duration time: " << msg_evento_detect.duration_time << endl;
        cout << "Comment: " << msg_evento_detect.comment << endl;
        cout << "---------------------------------------" << endl;

        if (task_attesa.attesa) {

                if (task_attesa.command_id == msg_evento_detect.event_id && task_attesa.request_time == msg_evento_detect.start_time) {

                        task_attesa.attesa = false;
                        cout << "Processo " << task_attesa.command_id << " completato" << endl;
                }
                
        }
}

double getTimeNow() {
        ros::Time momento = ros::Time::now();        
        double tempo = momento.sec + (momento.nsec / 1000000);
        return tempo;
}

double getInterval(double start_t) {
        return (getTimeNow()- start_t);
}