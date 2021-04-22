# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 10:35:04 by ubuntu            #+#    #+#              #
#    Updated: 2021/04/22 18:09:24 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_FOLDERS		=	Docker n-puzzle

.PHONY: all
all: folders

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
