FROM ubuntu:20.04

# This disable interactive mode for apt-get commands
ARG APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE=1
ENV DEBIAN_FRONTEND noninteractive
# Initial functionality for Ubuntu
RUN echo 'root:docker!' | chpasswd
RUN apt-get update -y
RUN apt-get install -y wget
RUN apt-get install -y gnupg2
RUN apt-get update -y
RUN apt-get install -y apt-utils

### Oblivious DEPS
RUN	apt-get upgrade -y
RUN	apt-get install -y autoconf ; \
	apt-get install -y automake ; \
	apt-get install -y build-essential ; \
	apt-get install -y clang ; \
	apt-get install -y iproute2 ; \
	apt-get install -y libcurl4-openssl-dev ;\
	apt-get install -y libssl-dev ; \
	apt-get install -y python ; \
	apt-get install -y python3-pip
RUN	apt-get install -y ssh ; \
	apt-get install -y sudo ; \
	apt-get install -y telnet ; \
	apt-get install -y valgrind

# User Setup
ARG USER=user
ARG HOME=/home/${USER}
ARG UID=1000
ARG GID=1000
ARG PW=docker
RUN useradd -m ${USER} --uid=${UID} && echo "${USER}:${PW}" | chpasswd
RUN usermod -a -G sudo ${USER}
USER ${USER}
WORKDIR ${HOME}
RUN ssh-keygen -b 2048 -q -N "" -f ${HOME}/.ssh/id_rsa

# Python3 default
USER root
WORKDIR /root
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 1
RUN python -m pip install pynput

# Set timezone
USER root
WORKDIR /root
RUN apt-get install -y tzdata
RUN ln -snf /usr/share/zoneinfo/Europe/Helsinki /etc/localtime
RUN dpkg-reconfigure tzdata

# Final upgrade
USER root
WORKDIR /root
RUN apt-get update -y
RUN apt-get upgrade -y

# Additional python modules
RUN	apt-get install -y python3-tk
RUN pip3 install Pillow
