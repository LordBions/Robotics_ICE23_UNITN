/*
* Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*/

#include <iostream>
#include "ros/ros.h"
#include <cmath>
#include <ctime>
#include <complex>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Pose.h>
#include <gazebo_msgs/SpawnModel.h>
#include <gazebo_msgs/SpawnModelRequest.h>
#include <gazebo_msgs/SpawnModelResponse.h>
#include <gazebo_msgs//DeleteModel.h>

#include <fstream>
#include <sstream>

using namespace std;

#define node_name "spawn_module"
#define cli_spawner_commander "gazebo/spawn_sdf_model"
#define cli_delete_commander "gazebo/delete_model"
#define sub_spawner_commander "/vision/spawnerCommander"
#define pub_spawner_ack "/vision/spawnerAck"

#define models_path "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/worlds/models/"
#define default_model_file "/model.sdf"
#define default_reference_frame "world"

#define type_numbers_of_legos 11
#define lego_colours_number 7
#define table_altitude 0.90

#define max_vector 10
#define min_vector -10
#define max_rotation 2 * M_PI
#define min_rotation 0

#define table_max_x 0.50
#define table_min_x 0.05
#define table_max_y 0.75
#define table_min_y 0.20

#define queque_size 10

#define param0 "-a1"
#define param1 "-assignment1"
#define param2 "-a2"
#define param3 "-assignment2"
#define param4 "-a3"
#define param5 "-assignment3"
#define param6 "-a4"
#define param7 "-assignment4"
#define param8 "-s1"
#define param9 "-special1"
#define param10 "-s2"
#define param11 "-special2"

#define max_lego_spawn 500
#define max_lego_in_table 11
#define loop_wait_rate 0.75

#define max_random_position_iterations 50

ros::ServiceClient cli_spawner_commander_handle, cli_delete_commander_handle;
ros::Publisher pub_spawner_ack_handle;
ros::Subscriber sub_spawner_commander_handle;      

gazebo_msgs::SpawnModel msg_spawn_object;
geometry_msgs::Pose  pose_object;
gazebo_msgs::DeleteModel msg_delete;

string lego_names[] = {"X1-Y1-Z2", "X1-Y2-Z1", "X1-Y2-Z2", "X1-Y2-Z2-CHAMFER", "X1-Y2-Z2-TWINFILLET", "X1-Y3-Z2", "X1-Y3-Z2-FILLET", "X1-Y4-Z1", "X1-Y4-Z2", "X2-Y2-Z2", "X2-Y2-Z2-FILLET"};
string lego_colours[] = {"Gazebo/Indigo", "Gazebo/Orange", "Gazebo/Red", "Gazebo/Purple", "Gazebo/SkyBlue", "Gazebo/DarkYellow", "Gazebo/Green" };

struct spawnedLego {
        string name;
        int class_id;
        double coord_x;
        double coord_y;
        double coord_z;
        double orient_x;
        double orient_y;
        double orient_z;
        double orient_w;
};

spawnedLego spawn_pool[max_lego_spawn];
int spawn_counter = 0;

void readParams(int argc, char **argv);
void defaultFunction();
void unknownUsage();
bool spawnLego(bool random_pos, bool random_or, int lego_class = -1, int colour_index = -1, double min_dis= 0 );
string getModelXML(string model_name);
void calculateRandomOr();
bool calculateRandomPose(double max_x, double min_x, double max_y, double min_y, double min_distance = 0);
string setColour( string l_xml, int color_index = -1); 
bool cliSpawnObjectRequest();
double randomInInterval(double max_d, double min_d = 0);
int randomNumber(int max_n);
void assignment1();
void assignment2();
void assignment3();
void assignment4();
void special1();
void special2();
void deleteAllLego();
bool cliDeleteObjectRequest();
void subSpawnCommanderCallback(const std_msgs::Int32::ConstPtr &msg);
void pubSpawnerAck(bool result);
void waitCommand();
double objectDistance(double obj1_x = 0, double obj1_y = 0, double obj1_z = 0, double obj2_x = 0, double obj2_y = 0, double obj2_z = 0);
bool checkCollitions(double obj_x, double obj_y, double obj_z, double min_distance = 0);

int main(int argc, char **argv) {

        cout << "----------------------------" << endl;
        cout << "Starting the spawn module!" << endl;
        cout << "----------------------------" << endl;
    
        ros::init(argc, argv, node_name);
        ros::NodeHandle node_handle;
        cout << "Node: " << node_name << " initialized!" << endl;

        cli_spawner_commander_handle = node_handle.serviceClient<gazebo_msgs::SpawnModel>(cli_spawner_commander);
        cout << "Client: " << cli_spawner_commander << " enabled" << endl;

        cli_delete_commander_handle = node_handle.serviceClient<gazebo_msgs::DeleteModel>(cli_delete_commander);
        cout << "Client: " << cli_delete_commander << " enabled" << endl;

        sub_spawner_commander_handle = node_handle.subscribe(sub_spawner_commander, queque_size, subSpawnCommanderCallback);
        cout << "Subscriber: " << sub_spawner_commander << " enabled with queque: " << queque_size << endl;

        pub_spawner_ack_handle = node_handle.advertise<std_msgs::Int32>(pub_spawner_ack, queque_size);
        cout << "Publisher: " << pub_spawner_ack << " enabled with queque: " << queque_size << endl;

        srand(time(NULL)); 

        cout << "----------------------------" << endl;
        cout << "Spawn module ready!" << endl;
        cout << "----------------------------" << endl << endl;

        readParams(argc, argv);

        cout << endl;
        cout << "Closing spawn module!" << endl;
        return 0;  
  
}

void readParams(int argc, char **argv) {

        string parameter;

        if (argc <= 1) { defaultFunction(); }

        else {

                for (int i = 1; i < argc; i++) {

                        parameter = argv[i];

                        if (parameter == param0 || parameter == param1) { assignment1(); }
                        else if (parameter == param2 || parameter == param3) { assignment2(); }
                        else if (parameter == param4 || parameter == param5) { assignment3(); }
                        else if (parameter == param6 || parameter == param7) { assignment4(); }
                        else if (parameter == param8 || parameter == param9) { special1(); }
                        else if (parameter == param10 || parameter == param11) { special2(); }
                        else { unknownUsage(); } 
                }
        }
}

void unknownUsage() {

        cout << "Unknown or too much parameters" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "USAGE: " << endl;
        cout << "-a <assignment numer from 1 to 4>  " << endl;
        cout << "-e <easter egg number from 1 to 2> " << endl;
        cout << "----------------------------------------------" << endl;
        cout << endl;
}

void defaultFunction() {

        cout << "Default function selected" << endl;
}

bool spawnLego(bool random_pos, bool random_or, int lego_class, int colour_index, double min_dis ) { 

        if (random_pos) { 
                
                if (!calculateRandomPose(table_max_x, table_min_x, table_max_y, table_min_y, min_dis)) {

                        cout << "Can't find space to make a valid random pose!" << endl;
                        return false;
                } 

        }
        
        if (random_or) { calculateRandomOr(); }

        if (lego_class == -1) { 
        
                lego_class = randomNumber(type_numbers_of_legos);
                cout << "Lego class: " << lego_class << endl;
        
        } else if ( lego_class > type_numbers_of_legos ) {

                lego_class = type_numbers_of_legos;
                cout << "Lego class out of range" << endl;
        }

        string spawn_name;
        spawn_name = "spawn_" + to_string( spawn_counter );

        string lego_xml = getModelXML(lego_names[lego_class]);

        if (lego_xml == "") {

                cout << "Can't read xml model" << endl;
                return false;
        }

        msg_spawn_object.request.model_name = spawn_name;
        msg_spawn_object.request.model_xml = setColour(lego_xml, colour_index);
        msg_spawn_object.request.robot_namespace = node_name;
        msg_spawn_object.request.initial_pose = pose_object;
        msg_spawn_object.request.reference_frame = default_reference_frame;     
        
        if (cliSpawnObjectRequest()) {

                spawn_pool[spawn_counter].name = spawn_name;
                spawn_pool[spawn_counter].class_id = lego_class;
                spawn_pool[spawn_counter].coord_x = pose_object.position.x;
                spawn_pool[spawn_counter].coord_y = pose_object.position.y;
                spawn_pool[spawn_counter].coord_z = pose_object.position.z;
                spawn_pool[spawn_counter].orient_x = pose_object.orientation.x;
                spawn_pool[spawn_counter].orient_y = pose_object.orientation.y;
                spawn_pool[spawn_counter].orient_z = pose_object.orientation.z;
                spawn_pool[spawn_counter].orient_w = pose_object.orientation.w;

                spawn_counter++;
                return true;

        } else { 
                
                spawn_counter++;
                return false;
        }
}

string getModelXML(string model_name) {

        string filename = models_path + model_name + default_model_file;
        cout << "reading the file: " << filename << endl;

        ifstream file(filename);

        if (!file) {
        
                cout << "Failed to open the file: " << filename << endl;
                return "";
        
        } else {

                stringstream buffer;
                buffer << file.rdbuf();
                string fileContents = buffer.str();
                file.close();

                return fileContents;
        }
}

void calculateRandomOr() {

        pose_object.orientation.x = randomInInterval(max_vector,min_vector);
        pose_object.orientation.y = randomInInterval(max_vector,min_vector);
        pose_object.orientation.z = randomInInterval(max_vector,min_vector);
        pose_object.orientation.w = randomInInterval(max_rotation,min_rotation);
}

bool calculateRandomPose(double max_x, double min_x, double max_y, double min_y, double min_distance) {

        double spawn_x;
        double spawn_y;
        double spawn_z;

        bool success = false;

        for (int i = 0; i <= max_random_position_iterations; i++) {

                spawn_x = randomInInterval(max_x,min_x);
                spawn_y = randomInInterval(max_y,min_y);
                spawn_z = table_altitude;

                if ( !checkCollitions(spawn_x, spawn_y, spawn_z, min_distance) ) { 
                
                        pose_object.position.x = spawn_x;
                        pose_object.position.y = spawn_y;
                        pose_object.position.z = spawn_z;

                        success = true;
                        cout << "Found valid random position" << endl;
                        break;
                }
        }

        return success;
}

string setColour(string l_xml, int color_index) {

        string current_colour;
        string desidered_colour;

        if (color_index = -1) { desidered_colour = lego_colours[ randomNumber(lego_colours_number) ]; }
        else { desidered_colour = lego_colours[color_index]; }

        int start_position = -1;

        for (int i = 0; i <= lego_colours_number; i++) {

                start_position = l_xml.find( lego_colours[i] );
                cout << "Start position: " << start_position << " for find: " << lego_colours[i] << endl;

                if (start_position != -1) {

                        current_colour = lego_colours[i];

                        cout << "current lego colour: " << current_colour << endl;
                        break;
                }
        }

        string new_xml;

        if (start_position == -1) { 
        
                cout << "Unable to find current lego colour" << endl;
                return "";

        } else {

                new_xml = l_xml.replace(start_position, current_colour.length(), desidered_colour);

                cout << "Replaced color with: " << desidered_colour << endl;
                return new_xml;
        }
}

bool cliSpawnObjectRequest() {

        if (!cli_spawner_commander_handle.call(msg_spawn_object)) {

                cout << "Error during spawn service call!" << endl;
                return false;

        } else {

                cout << "---------------------------------------" << endl;
                cout << "Client: " << cli_spawner_commander << " requested some data:" << endl;      
                cout << "---------------------------------------" << endl;   
                cout << "Model name: " << msg_spawn_object.request.model_name << endl;
                cout << "Model xml: " << msg_spawn_object.request.model_xml << endl;
                cout << "Robot namespace: " << msg_spawn_object.request.robot_namespace << endl;
                cout << "Initial pose x: " << msg_spawn_object.request.initial_pose.position.x << endl;
                cout << "Initial pose y: " << msg_spawn_object.request.initial_pose.position.y << endl;
                cout << "Initial pose z: " << msg_spawn_object.request.initial_pose.position.z << endl;
                cout << "Initial pose qx: " << msg_spawn_object.request.initial_pose.orientation.x << endl;
                cout << "Initial pose qy: " << msg_spawn_object.request.initial_pose.orientation.y << endl;
                cout << "Initial pose qz: " << msg_spawn_object.request.initial_pose.orientation.z << endl;
                cout << "Initial pose qw: " << msg_spawn_object.request.initial_pose.orientation.w << endl;
                cout << "Reference frame: " << msg_spawn_object.request.reference_frame << endl;
                cout << "---------------------------------------" << endl;
                cout << "Success: " << msg_spawn_object.response.success << endl;
                cout << "Status message: " << msg_spawn_object.response.status_message << endl;
                cout << "---------------------------------------" << endl;

                return msg_spawn_object.response.success;
        }
}

double randomInInterval(double max_d, double min_d) {

        double random_d = ( (double) rand() / (double) RAND_MAX) * (max_d - min_d) + min_d;
        return random_d;
}

int randomNumber(int max_n) {

        int random_n = rand() % max_n;
        return random_n;       
}

void assignment1() {

        cout << "Assignment 1 selected!" << endl;

        spawnLego(true, false);

        cout << "Ready for assignment 1!" << endl;
}

void assignment2() {

        cout << "Assignment 2 selected!" << endl;

        for (int i = 0; i < type_numbers_of_legos; i++) {
                
                spawnLego(true, false, i, -1, 0.08);
        }

        cout << "Ready for assignment 2!" << endl;

}

void assignment3() {

        cout << "Assignment 3 selected!" << endl;

}

void assignment4() {

        cout << "Assignment 4 selected!" << endl;

}

void special1() { 

        cout << "Easter egg 1 selected!" << endl;
        cout << "Function for taking photos with publisher" << endl;

        while (ros::ok()) { ros::spinOnce(); }        
}

void special2() { 

        cout << "Easter egg 2 selected!" << endl;
        cout << "Function for spawning legos in cycles" << endl;

        for (int i = 0; i < max_lego_spawn; i++) {     

                spawnLego(true, true,10); 
                spawnLego(true, true,10); 

                spawnLego(true, true,9); 
                spawnLego(true, true,9); 
                spawnLego(true, true,9); 

                spawnLego(true, true,1); 
                spawnLego(true, true,1); 
                spawnLego(true, true,1); 
                spawnLego(true, true,1); 

                spawnLego(true, true,6); 

                spawnLego(true, true,3); 
                spawnLego(true, true,3);

                spawnLego(true, true,7); 

                waitCommand();        
                deleteAllLego();        
        }

        cout << "Finished!" << endl;
}

void deleteAllLego() { 

        cout << "Found " << spawn_counter << " legos to delete" << endl;

        while (spawn_counter > 0) {

                msg_delete.request.model_name = spawn_pool[spawn_counter -1].name;
                cout << "Requestion the erase of " << msg_delete.request.model_name << endl;
                
                if ( cliDeleteObjectRequest() ) {

                        cout << msg_delete.request.model_name << " succesfully deleted" << endl;
                        spawn_pool[spawn_counter -1].name = "";

                } else {

                        cout << "Can't erase " << msg_delete.request.model_name << endl;
                }

                spawn_counter--;   
                cout << "Remaining " << spawn_counter << " legos " << endl;
        }
}

bool cliDeleteObjectRequest() {

        if (!cli_delete_commander_handle.call(msg_delete)) {

                cout << "Error during delete service call!" << endl;
                return false;

        } else {

                cout << "---------------------------------------" << endl;
                cout << "Client: " << cli_delete_commander << " requested some data:" << endl;      
                cout << "---------------------------------------" << endl;   
                cout << "Model name: " << msg_delete.request.model_name << endl;
                cout << "---------------------------------------" << endl;
                cout << "Success: " << msg_spawn_object.response.success << endl;
                cout << "Status message: " << msg_spawn_object.response.status_message << endl;
                cout << "---------------------------------------" << endl;

                return msg_delete.response.success;
        }
}

void subSpawnCommanderCallback(const std_msgs::Int32::ConstPtr &msg) {

        int visionCommand = msg->data;

        cout << "---------------------------------------" << endl;
        cout << "Subscriber: " << sub_spawner_commander << " received some data:" << endl;      
        cout << "---------------------------------------" << endl;    
        cout << "Command: " << visionCommand << endl;
        cout << "---------------------------------------" << endl;   

        bool spawn_result;

        if (visionCommand) {

                if (spawn_counter > 0) { deleteAllLego; }

                spawn_result = spawnLego(true, true);
                pubSpawnerAck(spawn_result);
        }
}

void pubSpawnerAck(bool resultat) {

        std_msgs::Int32 msg_ack;
        msg_ack.data = resultat;
        pub_spawner_ack_handle.publish(msg_ack);

        cout << "---------------------------------------" << endl;
        cout << "Publisher: " << pub_spawner_ack << " sent some data:" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Success: " << resultat << endl;
        cout << "---------------------------------------" << endl;
}

void waitCommand() {

        ros::Rate wait_loop(loop_wait_rate);
        wait_loop.sleep();
}

double objectDistance(double obj1_x, double obj1_y, double obj1_z, double obj2_x, double obj2_y, double obj2_z) {

        return sqrt( pow((obj2_x - obj1_x),2) + pow((obj2_y - obj1_y),2) + pow((obj2_z - obj1_z),2) );        
}

bool checkCollitions(double obj_x, double obj_y, double obj_z, double min_distance) {

        if (min_distance == 0) { return false; };

        double distan;
        bool collision = false;

        for (int i = 0; i < spawn_counter; i++) {

                distan = objectDistance( spawn_pool[i].coord_x, spawn_pool[i].coord_y, spawn_pool[i].coord_z, obj_x, obj_y, obj_z );
                cout << "Distance is " << distan << endl;

                if (distan < min_distance) { 
                
                        collision = true;
                        break;
                }
        }

        cout << "Collision is " << collision << endl;
        return collision;
}