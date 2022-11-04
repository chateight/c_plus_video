#include <opencv2/opencv.hpp>
#include <sys/wait.h>
#include <string.h>
#include <filesystem>
#include <thread>
#include <fstream>
#include "simple_udp.h"


simple_udp udp0("192.168.10.1",8889);        // connect to the tello
simple_udp udp1("0.0.0.0",8890);

void  Rcv_th()
{
    udp1.udp_bind();
    std::string rdata=udp1.udp_recv();
    std::cout << rdata << std::endl;
    std::cout << "thread terminate" << std::endl;
}


int main()
{
    std::ifstream r_file;
    std::string file = "../command.txt";
    r_file.open(file, std::ios::in);
    std::string r_l_buffer;

    while(std::getline(r_file, r_l_buffer)){
        std::cout << r_l_buffer << std::endl;

        udp0.udp_send(r_l_buffer);

        std::thread th_a(Rcv_th);
        th_a.join();
    }

    return 0;

/*
// processing video
    cv::Mat img = cv::imread("sample.jpeg");
    if(img.empty()) {
        return -1;
    }
    cv::namedWindow("test", cv::WINDOW_AUTOSIZE);
    cv::imshow("test", img);
    cv::waitKey(0);
    cv::destroyWindow("test");
    return 0;
*/
}