# c_plus_video

purpose : to control the tello by c++ scripts

required lib : opencv

source files

- video.cpp : send tello command from the command.txt file and receive the tello status
- ctello_stream.cpp : storing the video stream and sending commands from the command file(command.txt)

command.txt file describes the tello control command sequence.

link to the tello sdk icnluding command list
https://dl-cdn.ryzerobotics.com/downloads/tello/20180910/Tello%20SDK%20Documentation%20EN_1.3.pdf

output video file is located on the same directory of the exe file.
