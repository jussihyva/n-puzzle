# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/04 11:34:07 by jkauppi           #+#    #+#              #
#    Updated: 2021/06/03 10:15:50 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libftprintf.a
LIBFT_FOLDER	=	../libft
LIBFT			=	libft.a

# Folders
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
FOLDERS			=	$(OBJ) $(SRC) $(INCLUDE)
INCLUDES		=	-I $(INCLUDE) -I $(LIBFT_FOLDER)

# Compiler and linking parameters
OS				=	$(shell uname -s)
CC				=	clang
C_FLAGS			=	-std=gnu17 -fPIE -g -Wall -Wextra -Werror $(INCLUDES)

# C (Source code) and H (Header) files
TARGET_NAME		=	../$(NAME)
SRC_C_FILES		=	ft_printf.c split_input_string.c create_converters.c \
					ft_lltoa_base.c ft_ulltoa_base.c param_type.c \
					width_and_prediction.c modify_character.c \
					modify_string.c modify_pointer.c modify_integer.c \
					modify_octal.c modify_hex.c modify_unsigned_integer.c \
					release_memory_2.c read_param.c modify_float.c \
					formatters.c ft_dtoa_base.c ft_numlen.c ft_round.c \
					set_substring_common_1.c set_substring_common_2.c \
					set_substring_zero.c \
					print_output_string.c ft_putlstr_fd.c release_memory_1.c
SRC_H_FILES		=	ft_printf.h

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

.PHONY: all
all: libraries $(TARGET_NAME)
	@echo "$(GREEN)Done!$(END)"

$(TARGET_NAME): ../%: % $(FOLDERS) $(C_FILES) $(O_FILES)
	cp $< $@

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile
	$(CC) -c -o $@ $< $(C_FLAGS)
	ar -rcs $(NAME) $@

$(FOLDERS):
	mkdir $@

$(C_FILES):
	touch $@

.PHONY: libraries
libraries:
	@make -C ${LIBFT_FOLDER}

.PHONY: clean
clean:
	@make -C ${LIBFT_FOLDER} clean
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	@make -C ${LIBFT_FOLDER} fclean
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
ifeq ($(OS), Darwin)
	norminette-beta $(SRC)/* $(INCLUDE)/*
else
	norminette $(SRC)/* $(INCLUDE)/*
endif
