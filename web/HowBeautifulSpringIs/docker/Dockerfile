FROM lunasec/tomcat-9.0.59-jdk11

ENV DEBIAN_FRONTEND=noninteractive

COPY files /tmp/files/
ADD src/ /usr/local/tomcat/webapps/
RUN mv /tmp/files/flag.sh / && \
    mv /tmp/files/start.sh / && \
    chmod +x /flag.sh /start.sh && \
    useradd ctf -m && \
    chown -R root:root /usr/local/tomcat/webapps/ && \
    chmod -R 777 /usr/local/tomcat/webapps/ && \
    # sed -i "s|http://deb.debian.org/debian|http://mirror.sjtu.edu.cn/debian|g" /etc/apt/sources.list && \
	# sed -i '/security/d' /etc/apt/sources.list && \
    # apt-get update && \
    # apt-get install libaio1 libnuma1 psmisc libmecab2 libatomic1 libncurses6 libsasl2-2 perl -y && \
    # DEBIAN_FRONTEND=noninteractive dpkg -i /tmp/files/mysql-common_5.7.29-1debian10_amd64.deb && \
    # DEBIAN_FRONTEND=noninteractive dpkg -i /tmp/files/mysql-community-client_5.7.29-1debian10_amd64.deb && \
    # DEBIAN_FRONTEND=noninteractive dpkg -i /tmp/files/mysql-client_5.7.29-1debian10_amd64.deb && \
    # DEBIAN_FRONTEND=noninteractive dpkg -i /tmp/files/mysql-community-server_5.7.29-1debian10_amd64.deb && \
    # DEBIAN_FRONTEND=noninteractive dpkg -i /tmp/files/mysql-server_5.7.29-1debian10_amd64.deb && \
    rm -rf /tmp/files && \
    rm -rf /var/lib/apt/lists/*

EXPOSE 8080
ENV FLAG="tjctf{W0w_y0u_F1nd_m3ow's_Dr3@m_iN_SpR1n9}"

ENTRYPOINT [ "/start.sh" ]
