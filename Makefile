# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 10:35:04 by ubuntu            #+#    #+#              #
#    Updated: 2021/06/15 12:10:05 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_FOLDERS		=	Docker n-puzzle

define DOCKER_NOT_INSTALLED_ERROR

	Docker is not installed:"

		1. For Hive MAC's:	Download 42toolbox (github) and run init_docker.sh
		2. For std linux env:	sudo apt-get install docker"

		
endef

.PHONY: all
all:
	@echo "1. Installation"	
	@echo "  make build"
	@echo ""
	@echo "2. Run N-Puzzle solver"
	@echo "  make run"

.PHONY: build
build: check_docker folders
	@echo "DONE"

.PHONY: run
run: build
	make -C n-puzzle run

.PHONY: folders
folders:
	for folder in $(PROJECT_FOLDERS) ; do \
	    make -C $$folder ; \
	done

.PHONY: clean
clean:
	for folder in $(PROJECT_FOLDERS) ; do \
	    make -C $$folder clean ; \
	done

.PHONY: fclean
fclean:
	for folder in $(PROJECT_FOLDERS) ; do \
		make -C $$folder fclean ; \
	done

.PHONY: re
re: all
	for folder in $(PROJECT_FOLDERS) ; do \
	    make -C $$folder re ; \
	done

.PHONY: norm
norm:
	for folder in $(PROJECT_FOLDERS) ; do \
	    make -C $$folder norm ; \
	done

.PHONY: check_docker
check_docker:
ifeq (, $(shell which docker))
	$(error $(DOCKER_NOT_INSTALLED_ERROR))
endif
