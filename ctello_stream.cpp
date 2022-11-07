//  CTello is a C++ library to interact with the DJI Ryze Tello Drone
//  Copyright (C) 2020 Carlos Perez-Lopez
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>
//
//  You can contact the author via carlospzlz@gmail.com

#include <unistd.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <sys/wait.h>
#include <string.h>
#include <filesystem>
#include <thread>
#include <fstream>
#include "simple_udp.h"

const char* const TELLO_STREAM_URL{"udp://0.0.0.0:11111"};
simple_udp udp0("192.168.10.1",8889);
simple_udp udp1("0.0.0.0",8890);

using cv::CAP_FFMPEG;
using cv::imshow;
using cv::VideoCapture;
using cv::waitKey;


void command_th(){
    std::ifstream r_file;
    std::string file = "../command.txt";
    r_file.open(file, std::ios::in);
    std::string r_l_buffer;

    while(std::getline(r_file, r_l_buffer)){
        std::cout << r_l_buffer << std::endl;

        udp0.udp_send(r_l_buffer);
        sleep(5);

        udp1.udp_bind();
        std::string rdata=udp1.udp_recv();
        std::cout << rdata << std::endl;
    }
    return;
}

int main()
{
    udp0.udp_send("command");
    sleep(1);
    udp0.udp_send("streamon");

    VideoCapture capture{TELLO_STREAM_URL, CAP_FFMPEG};

    int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    int width  = (int)capture.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = (int)capture.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = capture.get(cv::CAP_PROP_FPS);
    cv::VideoWriter writer; 
    writer.open("o_Video.mp4", fourcc, fps, cv::Size(width, height));

    std::thread cmd_th(command_th);
    
    while (true)
    {
        cv::Mat frame;
        capture >> frame;
        if (!frame.empty())
        {
            imshow("CTello Stream", frame);
            writer << frame;
        }
        if (waitKey(1) == 27)
        {
            break;
        }
    }

    cmd_th.join();
}
