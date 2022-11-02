#include "ros/ros.h"
#include "solution/QuadSolve.h"
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "quad_solver_client");
  ros::NodeHandle n;
  
  ros::ServiceClient client = n.serviceClient<solution::QuadSolve>("solve_quad_equation");
  solution::QuadSolve srv;
  
  while(ros::ok()){
  	std::vector <float> a = {0,0,0};
  	std::cout<<"input odds quadratic equation: ";
  	for (int i = 0; i < 3; i++){
  		std::cin>> a[i];
  	}
  
  	srv.request.a = a;
  
  	if (client.call(srv)){
  		if (srv.response.x.size() == 2){
  			std::cout << "solution: x1= " << srv.response.x[0] << " x2= " << srv.response.x[1] << std::endl;
		}
		if (srv.response.x.size() == 1){
  			std::cout << "solution: x= " << srv.response.x[0] << std::endl;
		}
		if (srv.response.x.size() == 0){
  			std::cout << "There aren't solutions" << std::endl;
		}
  	}
  	else{
  		std::cout << "Failed to call service QuadSolve" << std::endl;
  		return 1;
  	}
 }
  return 0;
}
