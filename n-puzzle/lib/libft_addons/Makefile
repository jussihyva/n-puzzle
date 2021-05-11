# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/05/11 10:13:55 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS				=	$(shell uname -s)
ifeq ($(OS), Darwin)
	D_ATTRIBUTES	=	-D DARWIN
	MAC_INCLUDES	=	-I /Users/jkauppi/.brew/Cellar/openssl@1.1/1.1.1g/include
endif

NAME			=	libft_addons.a

# Folders
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
FOLDERS			=	$(OBJ) $(SRC) $(INCLUDE)
INCLUDES		=	-I $(INCLUDE) -I ../libft -I ../libft_printf/include \
					$(MAC_INCLUDES)

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-std=gnu17 -g -Wall -Wextra -Werror $(INCLUDES)
LD_FLAGS		=	$(D_ATTRIBUTES)

# C (Source code) and H (Header) files
TARGET_NAME		=	../$(NAME)
SRC_C_FILES		=	ft_radian.c ft_max_int.c ft_min_int.c \
					ft_mod_int.c ft_mod_double.c \
					ft_matrix_x_vector_double.c \
					ft_max_double.c ft_min_double.c ft_isdigit_base.c \
					ft_strtoi.c ft_login_event_1.c ft_login_event_2.c \
					ft_login_event_3.c ft_login_event_4.c ft_login_event_5.c \
					ft_openssl_init_ctx.c ft_openssl_init_client.c \
					ft_openssl_init.c ft_openssl_connect.c \
					ft_openssl_rel_conn.c ft_stack_push.c ft_stack_pop.c \
					ft_enqueue.c ft_dequeue.c ft_is_queue_empty.c \
					ft_queue_init.c \
					ft_bt_instert.c ft_bt_print.c ft_bt_find.c ft_bt_remove.c \
					ft_prio_enqueue.c ft_prio_dequeue.c
SRC_H_FILES		=	libft_addons.h

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
all: $(TARGET_NAME)
	@echo "$(GREEN)Done!$(END)"

$(TARGET_NAME): ../%: % $(FOLDERS) $(H_FILES) $(C_FILES) $(O_FILES)
	cp $< $@

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile
	$(CC) -c -o $@ $< $(C_FLAGS) $(LD_FLAGS)
	ar -rcs $(NAME) $@

$(FOLDERS):
	mkdir $@

$(C_FILES):
	touch $@

$(H_FILES):
	touch $@

.PHONY: clean
clean:
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
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
