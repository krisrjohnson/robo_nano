#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <string> 	//for debugging logic flow

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{

    // TODONE: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Moving the bot!");

    // Request robot to move with linear speed and turning radius
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv))
        ROS_ERROR("Failed to call service drive_bot");
}

// This callback function continuously executes and reads the image data
// http://docs.ros.org/melodic/api/sensor_msgs/html/msg/Image.html
void process_image_callback(const sensor_msgs::Image img)
{

    int pixel = -1, pixel_x_coord = -1, white_pixel = 255;

    // TODONE: Loop through each pixel in the image and check if there's a bright white one
    for (int i=0; i < img.height * img.step; i++) {
        if (img.data[i] == white_pixel) {
            pixel = i;
            break;
        }
    }
	
/*-------- turning left when he should be turning right
	1- set pixel incorrectly
	2- float math incorrect
------->
/* test cases:
	1) no ball, don't move
	2) ball in FOV left, move fwd and left
	3) ball in FOV right, move fwd and right
	4) ball in FOV middle, move fwd no angular velocity 
*/
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    if (pixel >= 0) {
        pixel_x_coord = float(pixel % img.width) / img.height;  //one float should cast the rest

	std::string s_imgWidth = std::to_string(img.width);
	std::string s_imgHeight = std::to_string(img.height);
	ROS_INFO_STREAM("img width: " << s_imgWidth << "\nimg height" << s_imgHeight);

	if (pixel) {
		std::string sPixel = std::to_string(pixel); 	//C++11, tested and this format works
		std::string sPixelCoord = std::to_string(pixel_x_coord);
		ROS_INFO_STREAM("pixel: " << sPixel << "\npixels coordinate: " << sPixelCoord); 	//Requires XML for this node to have output="screen"
	}

	//z>0 is to the left (counter-clockwise); z<0 to the right (clockwise)
        if (pixel_x_coord < .333) drive_robot(0.5, 0.3);
        else if (pixel_x_coord < .666) drive_robot(0.5, 0.0);
        else if (pixel_x_coord <= 1) drive_robot(0.5, -0.3);

        if (pixel_x_coord == -1) drive_robot(0.0, 0.0); // if there's no white ball, stop
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
