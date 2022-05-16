FROM php:7.2.2-apache
WORKDIR /var/www/html

COPY start.sh /start.sh
ADD src /var/www/html

RUN sed -i '$a\ServerName 127.0.0.1'  /etc/apache2/apache2.conf  && \
    chmod +x /start.sh && \
    chown -R www-data:www-data /var/www/html 

EXPOSE 80
ENV FLAG="tjctf{b39f3947-b8c3-4d4f-9a26-6ca80986b9c2}"

CMD ["/start.sh"]
