/*
* Group: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*
*/

#include <stdio.h>
#include <string.h>
#include <sl/Camera.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
    
    int imgNumber = 25;
    int sleepDuration = 5;

    // Create a ZED Camera object
    sl::Camera zed;

    sl::InitParameters init_parameters;
    init_parameters.sdk_verbose = true;
    init_parameters.camera_resolution = sl::RESOLUTION::HD720;
    init_parameters.depth_mode = sl::DEPTH_MODE::NONE;

    // Open the camera
    auto returned_state = zed.open(init_parameters);
    if (returned_state != sl::ERROR_CODE::SUCCESS) {
        std::cout << "ERROR" << std::endl;
        return -1;
    }

    // Print camera information
    auto camera_info = zed.getCameraInformation();
    std::cout << std::endl;
    std::cout <<"ZED Model                 : "<<camera_info.camera_model << std::endl;
    std::cout <<"ZED Serial Number         : "<< camera_info.serial_number << std::endl;
    std::cout <<"ZED Camera Firmware       : "<< camera_info.camera_configuration.firmware_version <<"/"<<camera_info.sensors_configuration.firmware_version<< std::endl;
    std::cout <<"ZED Camera Resolution     : "<< camera_info.camera_configuration.resolution.width << "x" << camera_info.camera_configuration.resolution.height << std::endl;
    std::cout <<"ZED Camera FPS            : "<< zed.getInitParameters().camera_fps << std::endl;

    // Create a Mat to store images
    sl::Mat zed_image;

    std::string imgName;

    for (int i=0; i<imgNumber; i++) {
        std::cout << "Step #" << i << std::endl;
        // Check that a new image is succesfully acquired
        returned_state = zed.grab();

        if (returned_state == sl::ERROR_CODE::SUCCESS) {

            // Retrive left image
            zed.retrieveImage(zed_image, sl::VIEW::LEFT);

            // Convert sl::Mat to cv::Mat (share buffer)
            cv::Mat cvImage = cv::Mat((int) zed_image.getHeight(), (int) zed_image.getWidth(), CV_8UC4, zed_image.getPtr<sl::uchar1>(sl::MEM::CPU));

            imgName = "home/utente/pictures" + std::to_string(i+25) + ".jpg";
            bool check = imwrite(imgName, cvImage);

        } else {
            std::cout << "Error in retrieving the image" << std::endl;
        }

        std::cout << "Captured image #" << i+25 << std::endl << std::endl;
         sleep(sleepDuration);
    }

    // Exit
    zed.close();
    return 0;
}