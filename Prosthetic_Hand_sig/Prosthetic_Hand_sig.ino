#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

std_msgs::String OurGraspState;
ros::Publisher GraspState("state", &OurGraspState);

char CloseState[19] = "The hand is closed";
char OpenState[17] = "The hand is open";

const int closeSig = 8;
const int openSig = 7;

void CloseHand( const std_msgs::Empty& toggle_msg)
{
  
  digitalWrite(closeSig, HIGH);
  delay(3000);
  digitalWrite(closeSig, LOW);
  OurGraspState.data = CloseState;
  
}

void OpenHand( const std_msgs::Empty& toggle_msg)
{
  
  digitalWrite(openSig, HIGH);
  delay(3000);
  digitalWrite(openSig, LOW);
  
}

ros::Subscriber<std_msgs::Empty> CLOSE_HAND("close", &CloseHand);
ros::Subscriber<std_msgs::Empty> OPEN_HAND("open", &OpenHand);

void setup() 
{

  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  nh.initNode();
  nh.subscribe(CLOSE_HAND);
  nh.subscribe(OPEN_HAND);
  nh.advertise(GraspState);

}

void loop() 
{

  GraspState.publish( &OurGraspState );
  nh.spinOnce();
  delay(1);
  
}
