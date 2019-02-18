#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

// Include the ball_chaser "DriveToTarget" header file
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested velocities wheel
bool handle_drive_request(ball_chaser::DriveToTarget::Linear_x& lin_x, ball_chaser::DriveToTarget::Angular_z& ang_z)
{
	
	ROS_INFO("DriveToTarget request received - %1.2f, %1.2f", (float)lin_x.joint_1);

	// Publish linear and angular velocities to the wheels
	std_msgs::Float64 linear_x, angular_z; // define vars
	linear_x.data = 
	
}


int main(int argc, char** argv) 
{
	// Initialize a ROS node, then create a ROS NodeHandle object
	ros::init(argc, argv, "drive_bot");
	ros::NodeHandle n;

	// Inform ROS master  that we will be publishing a message of type geometry_msgs::Twist on the actuation topic with a publishing queue size of 10
	motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

	// TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
	ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);

	// TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
	/* og code:
	while (ros::ok()) {
		// Create a motor_command object of type geometry_msgs::Twist
		geometry_msgs::Twist motor_command;
		// Set wheel velocities, forward[.5, 0]
		motor_command.linear_x = 0.5;
		motor_command.angular_z = 0.0;
		// Publish angles to drive the robot
		motor_command_publisher.publish(motor_command);
	} */

	// TODO: Handle ROS communication events
	motor_command_publisher
	// ros::spin();

	return 0;
}
