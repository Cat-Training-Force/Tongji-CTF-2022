FROM ubuntu:20.04

COPY start.sh /start.sh
ADD src /var/www/html

RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list &&\
    sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list &&\
    apt-get update &&\
    apt-get install -y apache2 php5 libapache2-mod-php5 php5-mysql php5-curl php5-gd \ 
    php5-idn php-pear php5-imagick php5-imap php5-mcrypt php5-memcache php5-ming php5-ps php5-pspell php5-recode \
    php5-snmp php5-sqlite php5-tidy php5-xmlrpc php5-xsl php5-mcrypt mysql-server vim curl  &&\
    rm /var/www/html/index.html  &&\
    chmod +x /start.sh

EXPOSE 80
ENV FLAG="tjctf{Ju57_@_s1mpl3_Up104D}"

CMD ["/start.sh"]

