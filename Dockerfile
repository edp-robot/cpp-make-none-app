FROM ubuntu:24.10

# Copy library
COPY ../cache/microhttpd /var/lib/microhttpd
# Copy Application
COPY target/http-server /usr/share/http-server

CMD ["sh", "-c", "LD_LIBRARY_PATH=/var/lib/microhttpd/lib /usr/share/app"]
