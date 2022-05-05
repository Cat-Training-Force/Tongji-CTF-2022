FROM lunasec/tomcat-9.0.59-jdk11

ENV DEBIAN_FRONTEND=noninteractive

COPY ./start.sh /tmp/.may_be_y0u_d0n7_kn0w/start.sh
ADD src/ /usr/local/tomcat/webapps/
RUN chmod +x /tmp/.may_be_y0u_d0n7_kn0w/start.sh

EXPOSE 8080
ENTRYPOINT [ "/tmp/.may_be_y0u_d0n7_kn0w/start.sh" ]
