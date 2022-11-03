#include <opencv2/opencv.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <atomic>
#include <filesystem>
#include <thread>
#include <cstdio>
#include <cstdint>


class simple_udp{
    int sock;
    struct sockaddr_in addr;

public:
    simple_udp(std::string address, int port){
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(address.c_str());
        addr.sin_port = htons(port);        
    }
    void udp_send(std::string word){
        sendto(sock, word.c_str(), word.length(), 0, (struct sockaddr *)&addr, sizeof(addr));
    }

    void udp_bind(){
        bind(sock, (const struct sockaddr *)&addr, sizeof(addr));

    }
    std::string udp_recv(){
        #define BUFFER_MAX 400
        char buf[BUFFER_MAX];
        memset(buf, 0, sizeof(buf));
        recv(sock, buf, sizeof(buf), 0);
        return std::string(buf);
    }
    void udp_recv(char *buf, int size){
        memset(buf, 0, size);
        recv(sock, buf, size, 0);
    }

    ~simple_udp(){
        close(sock);
    }
};


constexpr int FORK_NUM = 6;


simple_udp udp0("192.168.1.x",3478);        // udp mode set

uint8_t end_flag_;
uint8_t msg_;

void ThreadA()
{
    //int32_t input = 0;
    while(end_flag_){
        int input;
        printf("数字を入力してください\n");
        printf("0...スレッドBにメッセージを送信します\n");
        printf("1...プロセスを終了します\n");
        std::cin >> input;
    //    scanf("%d", &input);

        switch(input){
            case 0:
                msg_ = 1;
                break;
            case 1:
                end_flag_ = 0;
                break;
            default :
                printf("０か１を入力してください\n");
                break;
        }
    }
    printf("スレッドA終了\n");
}

void ThreadB()
{
    while(end_flag_){
        if(msg_){
            printf("スレッドAからメッセージを受信しました\n");
            msg_ = 0;
        }
    }
    printf("スレッドB終了\n");
}

int main()
{
    msg_ = 0;
    end_flag_ = 1;

    std::thread th_a(ThreadA);
    std::thread th_b(ThreadB);

    th_a.join();
    th_b.join();

    return 0;

/*  simple child pprocess creation
    pid_t c_pid = fork();
    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (c_pid > 0) {     // parent process
        std::cout << "parent process num ; " << getpid() << "; "<< c_pid << std::endl;
        wait(nullptr);
    } else {                    // child process
        std::cout << "child process num ; " << getpid() << "; "<< c_pid << std::endl;
        exit(EXIT_SUCCESS);
    }
*/

//    udp0.udp_send("command");

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