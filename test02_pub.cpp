#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h" 
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
/* 
  发布方：订阅乌龟位姿信息，转换成相对世界坐标系的坐标关系并发布 
 */

std::string turtle_name;  

void doPose(const turtlesim::Pose::ConstPtr& pose){
  static tf2_ros::TransformBroadcaster pub;
  geometry_msgs::TransformStamped ts;
  ts.header.frame_id = "world";
  ts.header.stamp=ros::Time::now();
  ts.child_frame_id = turtle_name; 
  ts.transform.translation.x = pose->x;
  ts.transform.translation.y = pose->y;
  ts.transform.translation.z = 0.0;
  tf2::Quaternion qtn;
  qtn.setRPY(0,0,pose->theta);
  ts.transform.rotation.x = qtn.getX();
  ts.transform.rotation.y = qtn.getY();
  ts.transform.rotation.z = qtn.getZ();
  ts.transform.rotation.w = qtn.getW();
  pub.sendTransform(ts);
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"pub");
    ros::NodeHandle nh;
    if(argc!=2){
        ROS_ERROR("请输入1个参数");
    }
    else{
        turtle_name=argv[1];
    }
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>(turtle_name+"/pose",1000,doPose);  
    ros::spin();
    return 0;
}
