FROM ubuntu:24.10

# Copy library
COPY lib/ /var/lib/microhttpd/lib
# Copy Application
COPY target/app /usr/share/app

CMD ["sh", "-c", "LD_LIBRARY_PATH=/var/lib/microhttpd/lib /usr/share/app"]
