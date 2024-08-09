# dependencies.mk

install_dependencies:
	@echo "Installing dependencies..."

	# Installing libmicrohttpd on Debian/Ubuntu
	@if [ ! -d "$(CacheDIR)/microhttpd" ]; then \
		mkdir /workspace/source/cache/microhttpd; \
		wget https://ftp.gnu.org/gnu/libmicrohttpd/libmicrohttpd-0.9.73.tar.gz; \
		tar -xzf libmicrohttpd-0.9.73.tar.gz; \
		cd libmicrohttpd-0.9.73; \
		./configure --prefix=/workspace/source/cache/microhttpd; \
		make && make install; \
		cd ..; \
	else \
		echo "libmicrohttpd already installed in $(CacheDIR)/libmicrohttpd"; \
	fi


	# Installing Unity on Debian/Ubuntu
	@if [ ! -d "$(CacheDIR)/Unity" ]; then \
		echo "Installing Unity..."; \
		curl -L https://github.com/ThrowTheSwitch/Unity/archive/master.zip -o unity.zip; \
		apt update && apt install unzip; \
		unzip unity.zip; \
		mkdir -p $(CacheDIR)/Unity/src; \
		cp -r Unity-master/src/* $(CacheDIR)/Unity/src/; \
		rm -rf Unity-master unity.zip; \
		echo "Unity installed in $(CacheDIR)/Unity"; \
	else \
		echo "Unity already installed in $(CacheDIR)/Unity"; \
	fi

	# Installing build-wrapper on Debian/Ubuntu
	@if [ ! -d "$(CacheDIR)/build-wrapper" ]; then \
		wget https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip; \
		apt update && apt install unzip; \
		unzip build-wrapper-linux-x86.zip -d $(CacheDIR)/build-wrapper; \
		rm build-wrapper-linux-x86.zip; \
	else \
		echo "Build-wrapper already installed in $(CacheDIR)/build-wrapper"; \
	fi
