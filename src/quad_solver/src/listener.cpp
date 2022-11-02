#include "ros/ros.h"
#include "solution/QuadSolve.h"

bool solve(solution::QuadSolve::Request &req, 
	   solution::QuadSolve::Response &res)
{
	ROS_INFO("request a= %f, b= %f, c= %f", req.a[0], req.a[1], req.a[2]);
	float a, b, c, d;
	a = req.a[0];
	b = req.a[1];
	c = req.a[2];
	d = b * b - 4 * a * c;
	if (d > 0) 
	{
		res.x.push_back(((-b) + sqrt(d)) / (2 * a));
		res.x.push_back(((-b) - sqrt(d)) / (2 * a));
		ROS_INFO("solution: x1= [%f], x2= [%f]", res.x[0], res.x[1]); 
	}
	if (d == 0) 
	{
		res.x.push_back((-b)/(2 * a));
		ROS_INFO("solution: x= [%f] ", res.x[0]); 
	}
	if (d < 0) 
	{
		ROS_INFO("solution: nothing"); 
	}
	return true;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "quad_solver_server");
  ros::NodeHandle n;
  
  ros::ServiceServer service = n.advertiseService("solve_quad_equation", solve);
  ROS_INFO("Ready to solve quadratic equation");
  ros::spin();
  return 0;
}
