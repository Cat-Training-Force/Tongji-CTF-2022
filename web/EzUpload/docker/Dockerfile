FROM php:7.2.2-apache
WORKDIR /var/www/html

COPY start.sh /start.sh
ADD src /var/www/html

RUN sed -i '$a\ServerName 127.0.0.1'  /etc/apache2/apache2.conf  && \
    chmod +x /start.sh && \
    chown -R www-data:www-data /var/www/html && \
    sed -i "s|http://deb.debian.org/debian|http://mirror.sjtu.edu.cn/debian|g" /etc/apt/sources.list && \
    sed -i '/security/d' /etc/apt/sources.list && \
    apt-get update && apt-get install -y zlib1g-dev && apt-get install -y libzip-dev && \
    docker-php-ext-install zip

EXPOSE 80
ENV FLAG="tjctf{Ju57_@_s1mpl3_Up104D}"

CMD ["/start.sh"]
