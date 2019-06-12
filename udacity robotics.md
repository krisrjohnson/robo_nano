udacity robotics

mobile robotics, in navigation, and in machine learning

coursera chicago specialization
	follows this free pdf book: "Modern Robotics:  Mechanics, Planning, and Control" (Lynch and Park, Cambridge University Press 2017).
	https://www.coursera.org/learn/modernrobotics-course1?specialization=modernrobotics

Lubuntu workspace notes:
Store all your files in the /home/workspace directory so you can still access them after rebooting Ubuntu. Any file stored outside of /home/workspace/ directory will be deleted after rebooting!!!
Disablee GPU!  - To disable the GPU, return to the classroom and next to the remaining GPU time, hit DISABLE. 
Keep an eye out for the little red indicator next to MENU in the lower left corner. This indicates that there is new content or an update provided with the Udacity Workspace.
Reset Data - In order to add this new content to your workspace, you must complete the RESET DATA step. Be sure to download and backup any work you've done before executing this step, as all of your work will be overwritten with a new classroom instance.

for VM, lesson 6: Getting Started, Sub-lesson 3


Gazebo’s four main features including Dynamics Simulation, Advanced 3D Graphics, Plugins, and Model Database
On launch in terminal
	>> $ sudo apt-get update && sudo apt-get upgrade -y 
	>> $ gazebo
	#  If Gazebo does not fully load after about one minute, try closing it by pressing Ctrl+C while the Gazebo terminal is active

1. Gazebo Server - gzserver
2. Gazebo Client - gzclient
3. World Files - simulation.world files - lighting, environment, sensors, etc - >> $ gazebo <yourworld>.world
	The world file is formatted using the Simulation Description Format or SDF for short. It's a markup format - open and close tags
4. Model Files - SDF file of exactly one robot, can be loaded directly by .world file using:
	<include>
  		<uri>model://model_file_name</uri>
	</include>
5. Environment Variables - basically PATH and communiques b/t gzserver and gzclient. Ex: GAZEBO_MODEL_PATH: List of directories where Gazebo looks to populate a model file.
6. Plugins - To interact with a world, model, or sensor in Gazebo, you can write plugins. These plugins can be either loaded from the command line or added to your SDF world file

	mouse highly recommended, lol
	click+shift rotates view
	right mouse zoom in and out or middle mouse wheel

Ideal day setup:
pre 9 am wakeup: procure bfast, coffee, cup of water, brush teeth
workday: 9-12: robotics (robotics) # rec'd 15 hrs a week!
noon-1: procure lunch, back e-cises
1-2: go for a walk
2-3.5: machine learning/fast.ai
3.5-5: workout
5.5-7: fast.ai
7-9: procure dinner
9-11: VGs

>> $ sudo apt-get update && sudo apt-get upgrade -y  #run any updates missing
>> $ touch myworld.world  #create blank myworld.world file
>> $ gedit myworld.world  #to edit world,robot files from terminal


octobot:
	extruded octagon 
	mohawk (reverse sharks fin)
	eight moveable arm joints? No real reason
	