#include"ros/ros.h"
#include"turtlesim/Spawn.h"
/*
   ���ܣ�����һ���ڹ� 
*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"spawn_test");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");  //订阅spawn服务节点
    turtlesim::Spawn spawn;  //����spawn���� 
    spawn.request.x =1.0;
    spawn.request.y =4.0;
    spawn.request.theta =1.57;
    spawn.request.name ="turtle2";  //����λ����Ϣ������ 
    ros::service::waitForService("/spawn");  //�ȴ���Ӧ 
    bool flag = client.call(spawn);  //flag��������Ӧ��� 
    if(flag){
        ROS_INFO("build success, name:%s",spawn.response.name.c_str());
    }
    else{
        ROS_INFO("build fail");
    }
    ros::spinOnce();  //�ص� 
    return 0;
}
