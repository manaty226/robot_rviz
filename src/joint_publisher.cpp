#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <string>
#include <math.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "joint_publisher");
  ros::NodeHandle nh;
  ros::Publisher joint_pub = nh.advertise<nav_msgs::Odometry>("odom", 10);
  tf::TransformBroadcaster odom_broadcaster;

  ros::Rate loop_rate(5);
  int count = 0;
  geometry_msgs::TransformStamped odom;
  double x = 0.0;
  double th = 0.0;
  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(0.0);
  while (ros::ok())
  { 
    x += 0.01;
    th += 0.1;
    odom.header.stamp = ros::Time::now();
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_footprint";
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    odom.transform.translation.x = x;
    odom.transform.translation.y = 0.0;
    odom.transform.translation.z = 0.0;    //set the position

    odom.transform.rotation = odom_quat;

    odom_broadcaster.sendTransform(odom);
    count++;

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
