FROM alpine

RUN adduser -D -u 2000 -h /var/run/tinyproxy -s /sbin/nologin tinyproxy tinyproxy

RUN apk --no-cache add -t build-dependencies \
    make \
    automake \
    autoconf \
    g++ \
    asciidoc \
    git

WORKDIR /tmp/tinyproxy

COPY . .

RUN ./autogen.sh
RUN ./configure --enable-transparent --prefix=""
RUN make
RUN make install
RUN mkdir -p /var/log/tinyproxy
RUN chown tinyproxy:tinyproxy /var/log/tinyproxy
RUN cd /
RUN rm -rf /tmp/tinyproxy
RUN apk del build-dependencies


CMD "tinyproxy -d"
