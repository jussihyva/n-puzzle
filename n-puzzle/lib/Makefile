# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 10:35:04 by ubuntu            #+#    #+#              #
#    Updated: 2021/04/21 11:37:13 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

A_FILES				=	libft/libft.a libft_printf/libftprintf.a \
						libft_addons/libft_addons.a
H_FILES				=	libft/libft.h libft_printf/include/ft_printf.h \
						libft_addons/include/libft_addons.h
LIB_FOLDERS			=	$(dir $(A_FILES))

.PHONY: all
all: h_files $(A_FILES) libraries

$(A_FILES):
	ar -rcs $@ Makefile
	ar -d $@ Makefile

.PHONY: h_files
h_files: $(H_FILES)
	@cp -f $^ ./

.PHONY: libraries
libraries:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder ; \
	done

.PHONY: clean
clean:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder clean ; \
	done
	rm -f $(notdir $(H_FILES))
	rm -f $(notdir $(A_FILES))

.PHONY: fclean
fclean:
	for folder in $(LIB_FOLDERS) ; do \
		make -C $$folder fclean ; \
	done
	rm -f $(notdir $(H_FILES))
	rm -f $(notdir $(A_FILES))

.PHONY: re
re: all
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder re ; \
	done

.PHONY: norm
norm:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder norm ; \
	done
