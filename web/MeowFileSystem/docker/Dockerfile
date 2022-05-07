FROM maven:3.5.4-jdk-8-slim as builder
WORKDIR /src
ADD . .
RUN mvn clean package -DskipTests

FROM openjdk:8-jre-slim
WORKDIR /app
ENV DEBIAN_FRONTEND=noninteractive TIME_ZONE=Asia/Shanghai

COPY --from=builder /src/target/*.jar app.jar
COPY files /tmp/files/

RUN mv /tmp/files/flag.sh / && \
    mv /tmp/files/start.sh / && \
    chmod +x /flag.sh /start.sh && \
    sed -i "s|http://deb.debian.org/debian|http://mirror.sjtu.edu.cn/debian|g" /etc/apt/sources.list && \
    sed -i '/security/d' /etc/apt/sources.list && \
    # support ps, curl, cron
    apt-get update && apt-get install -y procps curl cron tzdata && \
    ln -snf /usr/share/zoneinfo/$TIME_ZONE /etc/localtime && echo $TIME_ZONE > /etc/timezone && \
    dpkg-reconfigure -f noninteractive tzdata && \
    apt-get clean && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/files

EXPOSE 8081
ENV FLAG="tjctf{RCE_15_S0_fun_haH4hA}"

ENTRYPOINT ["/start.sh"]