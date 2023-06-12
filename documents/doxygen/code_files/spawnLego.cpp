/**
 * @file spawnLego.cpp
 * @authors Filippo Conti, Nicola Gianuzzi, Mattia Meneghin
 * @brief Script used to spawn lego in the gazebo world
 * @version 0.1
 * @date 2023-06-12
 * 
 * @copyright Copyright (c) 2023
 * 
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

#define models_path "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/environment/legos/"
#define default_model_file "/model.sdf"
#define default_reference_frame "world"

#define type_numbers_of_legos 11
#define lego_colours_number 7
#define table_altitude 0.90

#define max_vector 10
#define min_vector -10
#define max_rotation 2 * M_PI
#define min_rotation 0

#define table_max_x 0.35
#define table_min_x 0.05
#define table_max_y 0.75
#define table_min_y 0.25

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

#define max_random_position_iterations 100
#define default_min_d_between 0.1

bool verbose_flag = true;

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

/**
 * @brief Check which params are selected
 * @param argc is the number of params inserted
 * @param argv is a list of all parameters inserted
 * @note parameters could be aX or sX
*/
void readParams(int argc, char **argv);

/**
 * @brief default function (if argc < 1)
*/
void defaultFunction();

/**
 * @brief Functuion executed in case parameters are not valid
*/
void unknownUsage();

/**
 * @brief Spawn a lego model
 * @param random_pos if true, the function calculates a random position
 * @param random_or if true, the function calculates a random orientation
 * @param keep_base_down if true, the lego will be spawned on its natural base
 * @param lego_class integer used to select lego class [0, 11)
 * @param colour_index integer used to select the colour of lego spawned
 * @param min_dis double used to indicate the minimal distance between legos
 * 
*/
bool spawnLego(bool random_pos, bool random_or, bool keep_base_down, int lego_class = -1, int colour_index = -1, double min_dis= 0 );

/**
 * @brief Gets the lego XML file
 * @param model_name is the name of xml file
*/
string getModelXML(string model_name);

/**
 * @brief Calculates a random orientation for legos
 * @param keep_base_d if false, the function calculates a random orientation
 * @note if kee_base_d=true, lego base will be down, so orientation will be (x=0, y=0, z=0, w=rand(max_rotation, min_rotation))
*/
void calculateRandomOr(bool keep_base_d);

/**
 * @brief Calculates a random lego pose
 * @param max_x is max x pose lego could have
 * @param min_x is min x pose lego could have
 * @param max_y is max y pose lego could have
 * @param min_y is min y pose lego could have
 * @param min_distance is the min distance between legos
*/
bool calculateRandomPose(double max_x, double min_x, double max_y, double min_y, double min_distance = 0);

/**
 * @brief Sets a color in lego model
 * @param l_xml is lego xml file
 * @param color_index index for color
*/
string setColour( string l_xml, int color_index = -1); 

/**
 * @brief Sends a spawn request to Gazebo spawn service 
*/
bool cliSpawnObjectRequest();

/**
 * @brief Calculates a random number
 * @param mad_d max double number
 * @param min_d min double number
 * @return a random double value
*/
double randomInInterval(double max_d, double min_d = 0);

/**
 * @brief Calculates a random number
 * @param max_n max integer number
 * @return a random integer number
*/
int randomNumber(int max_n);

/**
 * @defgroup assignmentX assignments 
 * Execute the assignment
 * @{
*/
void assignment1(); ///< Execute the first assignment
void assignment2(); ///< Execute the second assignment
void assignment3(); ///< Execute the third assignment
void assignment4(); ///< Execute the fourth assignment
/**@}*/

/**
 * @defgroup specialX specials
 * Functions used to test the spawner and take photo of legos
 * @{
*/
void special1(); ///< Execute the special 1
void special2(); ///< Execute the special 2
/**@}*/

/**
 * @brief Delete all spawned legos
*/
void deleteAllLego();

/**
 * @brief Sends a delete request to Gazebo spawn service 
*/
bool cliDeleteObjectRequest();

/**
 * @brief testing function used to link to another module
 * @param msg received by an external module
*/
void subSpawnCommanderCallback(const std_msgs::Int32::ConstPtr &msg);

/**
 * @brief testing function used to respond to another module
 * @param result int used to send the result of response
*/
void pubSpawnerAck(bool result);

/**
 * @brief sleep function used to wait a command
*/
void waitCommand();

/**
 * @brief Find the distance between two legos
 * @param obj1_x x coordinate of first object
 * @param obj1_y y coordinate of first object
 * @param obj1_z z coordinate of first object
 * @param obj2_x x coordinate of second object
 * @param obj2_y y coordinate of second object
 * @param obj2_z z coordinate of second object
 * @return Distance between two points
*/
double objectDistance(double obj1_x = 0, double obj1_y = 0, double obj1_z = 0, double obj2_x = 0, double obj2_y = 0, double obj2_z = 0);

/**
 * @brief Checks if there are collitions between legos
 * @param obj_x x pose coordinate
 * @param obj_y y pose coordinate
 * @param obj_z z pose coordinate
 * @param min_distance 
*/
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
        cout << "----------------------------" << endl << endl;
        cout << "Closing spawn module!" << endl;
        cout << "----------------------------" << endl << endl;
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

        cout << "----------------------------------------------" << endl;
        cout << "Unknown or too much parameters" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "USAGE: " << endl;
        cout << "-a <assignment numer from 1 to 4>  " << endl;
        cout << "-e <easter egg number from 1 to 2> " << endl;
        cout << "----------------------------------------------" << endl;
        cout << endl;
}
void defaultFunction() {

        cout << "----------------------------------------------" << endl;
        cout << "Default function selected" << endl;
        cout << "----------------------------------------------" << endl;
}
bool spawnLego(bool random_pos, bool random_or, bool keep_base_down, int lego_class, int colour_index, double min_dis ) { 

        if (random_pos) { 
                
                if (!calculateRandomPose(table_max_x, table_min_x, table_max_y, table_min_y, min_dis)) {

                        if (verbose_flag) cout << "Can't find space to make a valid random pose!" << endl;
                        return false;
                } 

        }
        
        if (random_or) { calculateRandomOr(keep_base_down); }

        if (lego_class == -1) { 
        
                lego_class = randomNumber(type_numbers_of_legos);
                if (verbose_flag) cout << "Lego class: " << lego_class << endl;
        
        } else if ( lego_class > type_numbers_of_legos ) {

                lego_class = type_numbers_of_legos;
                if (verbose_flag) cout << "Lego class out of range" << endl;
        }

        string spawn_name;
        spawn_name = "spawn_" + to_string( spawn_counter );

        string lego_xml = getModelXML(lego_names[lego_class]);

        if (lego_xml == "") {

                if (verbose_flag) cout << "Can't read xml model" << endl;
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
        if (verbose_flag) cout << "reading the file: " << filename << endl;

        ifstream file(filename);

        if (!file) {
        
                if (verbose_flag) cout << "Failed to open the file: " << filename << endl;
                return "";
        
        } else {

                stringstream buffer;
                buffer << file.rdbuf();
                string fileContents = buffer.str();
                file.close();

                return fileContents;
        }
}
void calculateRandomOr(bool keep_base_d) {

        if (keep_base_d) {

                pose_object.orientation.x = 0;
                pose_object.orientation.y = 0;
                pose_object.orientation.z = 1;
                pose_object.orientation.w = randomInInterval(max_rotation,min_rotation);

        } else {

                pose_object.orientation.x = randomInInterval(max_vector,min_vector);
                pose_object.orientation.y = randomInInterval(max_vector,min_vector);
                pose_object.orientation.z = randomInInterval(max_vector,min_vector);
                pose_object.orientation.w = randomInInterval(max_rotation,min_rotation);
        }
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
                        if (verbose_flag) cout << "Found valid random position" << endl;
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
                if (verbose_flag) cout << "Start position: " << start_position << " for find: " << lego_colours[i] << endl;

                if (start_position != -1) {

                        current_colour = lego_colours[i];

                        if (verbose_flag) cout << "current lego colour: " << current_colour << endl;
                        break;
                }
        }

        string new_xml;

        if (start_position == -1) { 
        
                if (verbose_flag) cout << "Unable to find current lego colour" << endl;
                return "";

        } else {

                new_xml = l_xml.replace(start_position, current_colour.length(), desidered_colour);

                if (verbose_flag) cout << "Replaced color with: " << desidered_colour << endl;
                return new_xml;
        }
}
bool cliSpawnObjectRequest() {

        if (!cli_spawner_commander_handle.call(msg_spawn_object)) {

                if (verbose_flag) cout << "Error during spawn service call!" << endl;
                return false;

        } else {

                if (verbose_flag) cout << "---------------------------------------" << endl;
                if (verbose_flag) cout << "Client: " << cli_spawner_commander << " requested some data:" << endl;      
                if (verbose_flag) cout << "---------------------------------------" << endl;   
                if (verbose_flag) cout << "Model name: " << msg_spawn_object.request.model_name << endl;
                if (verbose_flag) cout << "Model xml: " << msg_spawn_object.request.model_xml << endl;
                if (verbose_flag) cout << "Robot namespace: " << msg_spawn_object.request.robot_namespace << endl;
                if (verbose_flag) cout << "Initial pose x: " << msg_spawn_object.request.initial_pose.position.x << endl;
                if (verbose_flag) cout << "Initial pose y: " << msg_spawn_object.request.initial_pose.position.y << endl;
                if (verbose_flag) cout << "Initial pose z: " << msg_spawn_object.request.initial_pose.position.z << endl;
                if (verbose_flag) cout << "Initial pose qx: " << msg_spawn_object.request.initial_pose.orientation.x << endl;
                if (verbose_flag) cout << "Initial pose qy: " << msg_spawn_object.request.initial_pose.orientation.y << endl;
                if (verbose_flag) cout << "Initial pose qz: " << msg_spawn_object.request.initial_pose.orientation.z << endl;
                if (verbose_flag) cout << "Initial pose qw: " << msg_spawn_object.request.initial_pose.orientation.w << endl;
                if (verbose_flag) cout << "Reference frame: " << msg_spawn_object.request.reference_frame << endl;
                if (verbose_flag) cout << "---------------------------------------" << endl;
                if (verbose_flag) cout << "Success: " << msg_spawn_object.response.success << endl;
                if (verbose_flag) cout << "Status message: " << msg_spawn_object.response.status_message << endl;
                if (verbose_flag) cout << "---------------------------------------" << endl;

                return msg_spawn_object.response.success;
        }
}
double randomInInterval(double max_d, double min_d) {

        double random_d = ( (double) rand() / (double) RAND_MAX) * (max_d - min_d) + min_d;
        return random_d;
}
int randomNumber(int max_n) {

        int random_n = rand() % (max_n + 1);
        return random_n;       
}
void assignment1() {

        cout << "Assignment 1 selected!" << endl;

        spawnLego(true, true, true); // 1 lego base in giu, random pos e random or

        cout << "Ready for assignment 1!" << endl;
}
void assignment2() {

        cout << "Assignment 2 selected!" << endl;

        for (int i = 0; i < type_numbers_of_legos; i++) { // tutte le classi
                
                spawnLego(true, true, true, i, -1, default_min_d_between); // base in giu, random pos e random or
        }

        cout << "Ready for assignment 2!" << endl;

}
void assignment3() {

        cout << "Assignment 3 selected!" << endl;

        for (int i = 0; i < 8; i++) { // 8 lego a caso
                
                spawnLego(true, true, false, -1, -1, default_min_d_between); // random pos, random or, no base giu
        }

        cout << "Ready for assignment 3!" << endl;        

}
void assignment4() {

        cout << "Assignment 4 selected!" << endl;


        ////////////////////////////////////

        cout << "Ready for assignment 4!" << endl;

}
void special1() { 

        cout << "Easter egg 1 selected!" << endl;

        while (ros::ok()) { ros::spinOnce(); }    

        cout << "Finished!" << endl;    
}
void special2() { 

        cout << "Easter egg 2 selected!" << endl;
        cout << "Function for spawning legos in cycles" << endl;

        for (int i = 0; i < 500; i++) {     

                spawnLego(true, true, true, 10); 
                waitCommand(); 
                deleteAllLego();
        }

        cout << "Finished!" << endl;
}
void deleteAllLego() { 

        if (verbose_flag) cout << "Found " << spawn_counter << " legos to delete" << endl;

        while (spawn_counter > 0) {

                msg_delete.request.model_name = spawn_pool[spawn_counter -1].name;
                if (verbose_flag) cout << "Requestion the erase of " << msg_delete.request.model_name << endl;
                
                if ( cliDeleteObjectRequest() ) {

                        if (verbose_flag) cout << msg_delete.request.model_name << " succesfully deleted" << endl;
                        spawn_pool[spawn_counter -1].name = "";

                } else {

                        if (verbose_flag) cout << "Can't erase " << msg_delete.request.model_name << endl;
                }

                spawn_counter--;   
                if (verbose_flag) cout << "Remaining " << spawn_counter << " legos " << endl;
        }
}
bool cliDeleteObjectRequest() {

        if (!cli_delete_commander_handle.call(msg_delete)) {

                if (verbose_flag) cout << "Error during delete service call!" << endl;
                return false;

        } else {

                if (verbose_flag) cout << "---------------------------------------" << endl;
                if (verbose_flag) cout << "Client: " << cli_delete_commander << " requested some data:" << endl;      
                if (verbose_flag) cout << "---------------------------------------" << endl;   
                if (verbose_flag) cout << "Model name: " << msg_delete.request.model_name << endl;
                if (verbose_flag) cout << "---------------------------------------" << endl;
                if (verbose_flag) cout << "Success: " << msg_spawn_object.response.success << endl;
                if (verbose_flag) cout << "Status message: " << msg_spawn_object.response.status_message << endl;
                if (verbose_flag) cout << "---------------------------------------" << endl;

                return msg_delete.response.success;
        }
}
void subSpawnCommanderCallback(const std_msgs::Int32::ConstPtr &msg) {

        int visionCommand = msg->data;

        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Subscriber: " << sub_spawner_commander << " received some data:" << endl;      
        if (verbose_flag) cout << "---------------------------------------" << endl;    
        if (verbose_flag) cout << "Command: " << visionCommand << endl;
        if (verbose_flag) cout << "---------------------------------------" << endl;   

        bool spawn_result;

        if (visionCommand) {

                if (spawn_counter > 0) { deleteAllLego; }

                spawn_result = spawnLego(true, true, true);
                pubSpawnerAck(spawn_result);
        }
}
void pubSpawnerAck(bool resultat) {

        std_msgs::Int32 msg_ack;
        msg_ack.data = resultat;
        pub_spawner_ack_handle.publish(msg_ack);

        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Publisher: " << pub_spawner_ack << " sent some data:" << endl;
        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Success: " << resultat << endl;
        if (verbose_flag) cout << "---------------------------------------" << endl;
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
                if (verbose_flag) cout << "Distance is " << distan << endl;

                if (distan < min_distance) { 
                
                        collision = true;
                        break;
                }
        }

        if (verbose_flag) cout << "Collision is " << collision << endl;
        return collision;
}