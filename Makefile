# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/04/15 13:30:49 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Input parameters
ifdef L
	LOGING_LEVEL	=	$(L)
else
	LOGING_LEVEL	=	3
endif

ifdef A
	ALGORITHM	=	$(A)
else
	ALGORITHM	=	dfs_1
endif

# Application specific parameters
NAME			=	n_puzzle
NAMES			=	$(NAME)

# Folders
LIB				=	lib
BIN				=	bin
DATA			=	data
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
FOLDERS			=	$(LIB) $(BIN) $(DATA) $(OBJ) $(SRC) $(INCLUDE)
INCLUDES		=	-I $(INCLUDE) -I $(LIB)

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-g -Wall -Wextra -Werror $(INCLUDES)
LD_FLAGS		=	-std=gnu17 \
					-Llib \
					-lft_addons -lftprintf -lft -lm \
					-lssl -lcrypto

# C (Source code) and H (Header) files
SRC_C_FILES		=	loging_parameters.c arg_parser.c puzzle_map_1.c \
					puzzle_map_2.c memory.c input.c \
					initialize_puzzle_1.c initialize_puzzle_2.c \
					puzzle_print.c statistics_1.c statistics_2.c \
					influxdb_1.c tile.c \
					dfs.c dfs_rand.c dfs_deeping.c dfs_deeping_mem.c \
					puzzle_status.c bfs.c bfs_1.c
SRC_H_FILES		=	n_puzzle.h

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))
APP_FILES		=	$(addprefix $(BIN)/, $(NAMES))

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

SELF_SIGNED_CRT	=	./tls-selfsigned.crt
SELF_SIGNED_KEY	=	./tls-selfsigned.key

.PHONY: all
all: $(SELF_SIGNED_CRT) $(FOLDERS) $(H_FILES) $(C_FILES) libraries $(APP_FILES)
	@echo "$(GREEN)Done!$(END)"

$(APP_FILES): $(BIN)/%: $(SRC)/%.c $(H_FILES) $(O_FILES) Makefile
	$(CC) -o $@ $< $(O_FILES) $(LD_FLAGS) $(C_FLAGS)

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile
	$(CC) -c -o $@ $< $(C_FLAGS)

$(FOLDERS):
	mkdir $@

$(C_FILES):
	touch $@

$(H_FILES):
	touch $@

.PHONY: libraries
libraries:
	@make -C ${LIB}

.PHONY: libraries_re
libraries_re:
	@make -C ${LIB} re

.PHONY: libraries_norm
libraries_norm:
	-@make -C ${LIB} norm

.PHONY: run
run: all
	cat data/3_3_01.map | valgrind -s --tool=memcheck \
	--leak-check=full --show-leak-kinds=all $(BIN)/$(NAME) -L $(LOGING_LEVEL) \
	-A $(ALGORITHM)

.PHONY: run_loop
run_loop: all
	while [ 1 -eq 1 ] ; do ./bin/PuzzleGenerator.py -s 3 | ./bin/n_puzzle -L 2 -rA dfs_1 | ./bin/n-puzzle_gui.py ; done

.PHONY: test
test: all
	-./$(NAME) data/maps/Error/Invalid_param_01
	-./$(NAME) data/maps/Error/Invalid_param_02

$(SELF_SIGNED_CRT):
	echo "FI\nUusimaa\n" | \
	openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout $(SELF_SIGNED_KEY) \
	-out $(SELF_SIGNED_CRT) \
	-days 365 \
	-subj "/C=FI/ST=Uusimaa/L=Espoo/O=/OU=/CN="
	chmod 644 $(SELF_SIGNED_CRT)
	chmod +r $(SELF_SIGNED_KEY)

print_key:
	openssl x509 -in $(SELF_SIGNED_CRT) -text -noout

.PHONY: clean
clean:
	@make -C ${LIB} clean
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	@make -C ${LIB} fclean
	rm -f $(BIN)/$(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm: libraries_norm
	norminette $(SRC)/* $(INCLUDE)/*
