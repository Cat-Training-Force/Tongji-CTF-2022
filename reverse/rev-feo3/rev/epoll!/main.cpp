#include <sys/epoll.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>

struct data
{
    unsigned int inst;
    unsigned int val;
};

unsigned int insts[] { 786370755, 3698336235, 3234970230, 3116397930, 3127415895, 2504997030, 1334154210, 2199801645 };
long long res[] { 3372509286, 759210638, -150304712, -1224475102, -3372509286, -759210638, 150304712, 1224475102 };
long long buffer[] { 0, 0, 0, 0, 0, 0, 0, 0 };

int main()
{
    int pos = 0;
    int cnt = 8;
    char input[33];
    read(0, input, 31);
    srand(time(NULL));
    int port = rand() & 0xffff;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int wfd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    fcntl(wfd, F_SETFL, fcntl(wfd, F_GETFL, 0) | O_NONBLOCK);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(fd, 20);
    int epollfd = epoll_create1(0);
    struct epoll_event ev, events[32];
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    connect(wfd, (struct sockaddr *)&addr, sizeof(addr));
    ev.events = EPOLLOUT;
    ev.data.fd = wfd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, wfd, &ev);
    while (cnt)
    {
        int nfds = epoll_wait(epollfd, events, 32, -1);
        for (int n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == fd)
            {
                int rfd = accept(events[n].data.fd, nullptr, 0);
                fcntl(rfd, F_SETFL, fcntl(rfd, F_GETFL, 0) | O_NONBLOCK);
                ev.events = EPOLLIN;
                ev.data.fd = rfd;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, rfd, &ev);
                epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, nullptr);
            }
            else if (events[n].data.fd == wfd)
            {
                data d;
                d.inst = insts[pos];
                d.val = ((int*)input)[pos];
                write(events[n].data.fd, &d, sizeof(d));
                pos++;
                if (pos == 8)
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, wfd, nullptr);
            }
            else
            {
                data d;
                read(events[n].data.fd, &d, sizeof(d));
                if (d.inst == 0)
                {
                    cnt--;
                    continue;
                }
                long long v = d.val;
                if (d.inst & 8)
                    v = -v;
                buffer[d.inst & 7] += v;
                d.inst >>= 4;
                write(wfd, &d, sizeof(d));
            }
        }
    }
    if (memcmp(buffer, res, sizeof(res)) == 0)
        write(1, "OK\n", 3);
    else
        write(1, "FAIL\n", 5);
    return 0;
}