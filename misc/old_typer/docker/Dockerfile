FROM ubuntu:20.04

RUN sed -i "s/http:\/\/archive.ubuntu.com/http:\/\/mirror.sjtu.edu.cn/g" /etc/apt/sources.list && \
    apt-get update && apt-get -y dist-upgrade && \
    apt-get install -y make lib32z1 xinetd python3

WORKDIR /ctf

COPY ./ctf.xinetd /etc/xinetd.d/ctf
COPY ./start.sh /start.sh
RUN echo "Blocked by ctf_xinetd" > /etc/banner_fail

COPY ./bin/ /ctf/

RUN chmod +x /start.sh
RUN chmod +x /ctf/main.py


CMD ["/start.sh"]

EXPOSE 9999
