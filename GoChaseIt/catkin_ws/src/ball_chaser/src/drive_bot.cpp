// new drive_bot
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <std_msgs/Float64.h>  //added as using Float64; is this already in geometry_msgs?
#include "ball_chaser/DriveToTarget.h"  //DriveToTarget is a service w/ linear_x, angular_z inputs and string msg_feedback output (from the .srv file created)

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODONE: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints


	// arm_mover ex: simple_arm::GoToPosition::Request& req, simple_arm::GoToPosition::Response& res
	// Request and Response are the above and below '---' bits from the DriveToTarget.srv file
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res) {
	// so now have req.linear_x, req.angular_z, res.msg_feedback defined

    // TODONE: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
    // Create a motor_command object of type geometry_msgs::Twist
    geometry_msgs::Twist motor_command;

    // Set wheel velocities, forward [0.5, 0.0]
    motor_command.linear.x = req.linear_x;
    motor_command.angular.z = req.angular_z;

	// needs to publish to wheel1 and wheel2, how do I figure out these topic names? gazebo file?
		// aka where are the list of available topics?

	// the publisher takes data type geometry_msgs::Twist
    // Publish angles to drive the robot
	motor_command_publisher.publish(motor_command);


	// ros::Duration(3).sleep();  //in case a wait cmd might be helfpul

	// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities
	res.msg_feedback = "DriveToTarget received, wheel speeds set: linear_x:" + std::to_string(req.linear_x) + ", angular_z: " + std::to_string(req.angular_z);
	ROS_INFO_STREAM(res.msg_feedback);

	return true; 
}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object to comm w/ ROS master
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
    ROS_INFO("ready to drive");

    // Handle ROS communication events
    ros::spin();

    return 0;
}