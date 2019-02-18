#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, ang_z) 
{
	// request service
	ball_chaser::DriveToTarget srv;

	// pass velocities to service
	srv.linear_x = lin_x;
	srv.angular_z = ang_z;

	// call the drive_bot service and pass the requested velocities
	if(!client.call(srv))
			ROS_ERROR("Failed to call service drive_bot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
	int pixel = -1;
	int pixel_x_coord, img_loc;
	// TODO: Loop through each pixel in the image and check if there's a bright white one
	// Identify where in the img this pixel is, left, right, or middle
	// Call the drive_bot fn and pass velocities to it
	// Request a stop when there's no white ball seen by the camera
	bool white_ball = false;

	for (int i=0; i < img.height * img.step; i++) {
		if(img.data[i] == white_pixel) {
			pixel = img.data[i];
			break;
		}
	}

	if (pixel >= 0) {
		// identify location as (left, middle, or right). Using labels (-1,0,1)
			// img.data[] is step*rows big
			// want to back out the x coordinate
			// img.data[i] % width = x_coord [0-indexed]
		pixel_x_coord = float(pixel % img.width) / float(img.height);  // int division rounds down

		if (pixel_x_coord < .333) {img_loc = -1;} 
		else if (pixel_x_coord < .666) {img_loc = 0;}
		else {img_loc = 1;}

		// Call the drive_bot fn and pass velocities to it
		// Request a stop when there's no white ball seen by the camera
	}

}

int main(int argc, char** argv) 
{
	// Initialize the process_image node and create a handle to it
	ros::init(argc, argv, "process_image");
	ros::NodeHandle n;

	// Define a client service capable of requesting services from command_robot
	clinet = n.ServiceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

	// Subscribe to /camera/rgb/raw_image topic to read the image data inside the process_image_callback
	// n.subscribe("/topic", msgs_in_queue, fn_to_call_on_msg_reception);
	ros::Subscriber sub1 = n.subscribe("/camera/rgb/raw_image", 10, process_image_callback);

	// Handle ROS communication events
	ros::spin();

	return 0;
}