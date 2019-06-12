// New code
#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, ang_z) 
{
	ROS_INFO_STREAM("Moving towards white ball");
	// request service
	ball_chaser::DriveToTarget srv;

	// pass velocities to service
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	// call the drive_bot service and pass the requested velocities
		// the if statement calls the service and if that service errors out (returns False) then the if fn is true (!False) and runs the error msg
	if(!client.call(srv))
			ROS_ERROR("Failed to call service drive_bot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
	int pixel = -1;
	int pixel_x_coord = -1;
	int white_pixel = 255;
	// Loop through each pixel in the image and check if there's a bright white one; pixel's are stored in a single array, assign first white pixel to int pixel 
		// this logic is fairly rudimentary, assumes only the white ball can be white in this world; takes first white pixel as the point location of the ball :(
	for (int i=0; i < img.height * img.step; i++) {
		if(img.data[i] == white_pixel) {
			pixel = img.data[i];
			break;
		}
	}

	if (pixel >= 0) {
		// img.data[] is step*rows big
		// want to back out the x coordinate
		// img.data[i] % width = x_coord [0-indexed]
		pixel_x_coord = float(pixel % img.width) / float(img.height);  // int division rounds down
		/* based on where the white ball is in the image, turn a direction
		turning is based on the angular z velocity, >0 is to the left, <0 to the right
		When the white ball is down the middle, don't turn. 
			There's a risk of continuously circling the ball w/ this logic
		linear_x and angular_z are FLoat64 types
		*/
		if (pixel_x_coord < .333) {drive_robot(0.5, 0.3);} 
		else if (pixel_x_coord < .666) {drive_robot(0.5, 0.0);}
		else if (pixel_x_coord == -1) {drive_robot(0.5, -0.3);} 
		else 						{drive_robot(0.0, 0.0);}
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