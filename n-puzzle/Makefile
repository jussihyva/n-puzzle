# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/06/02 14:13:53 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Input parameters

ifdef M
	MAX_MOVES		=	-i $(M)
else
	MAX_MOVES		=
endif

ifdef G
	PUZZLE_GUI		=	| ./bin/n-puzzle_gui.py
else
	PUZZLE_GUI		=	>/dev/null
endif

ifdef S
	PUZZLE_SIZE		=	$(S)
else
	PUZZLE_SIZE		=	3
endif

ifdef D
	PRINT_DELAY		=	$(D)
else
	PRINT_DELAY		=	0
endif

ifdef F
	MAP_FILE		=	$(F)
else
	MAP_FILE		=	data/3_3_05.map
endif

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

OS				=	$(shell uname -s)
ifeq ($(OS), Darwin)
	D_ATTRIBUTES	=	-D DARWIN
	MAC_INCLUDES	=	-I /Users/jkauppi/.brew/Cellar/openssl@1.1/1.1.1k/include
	MAC_LD_FLAGS	=	-L/Users/jkauppi/.brew/Cellar/openssl@1.1/1.1.1k/lib
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
TEST			=	test
FOLDERS			=	$(LIB) $(BIN) $(DATA) $(OBJ) $(SRC) $(INCLUDE) $(TEST)
INCLUDES		=	-I $(INCLUDE) -I $(LIB)

# C (Source code) and H (Header) files
SRC_C_FILES		=	loging_parameters.c arg_parser.c puzzle_map_1.c \
					puzzle_map_2.c release_puzzle.c input_1.c input_2.c \
					initialize_puzzle_1.c initialize_puzzle_2.c \
					puzzle_print.c statistics_1.c statistics_2.c \
					statistics_3.c statistics_4.c \
					influxdb_1.c tile.c \
					dfs.c dfs_rand.c dfs_deeping.c dfs_deeping_mem.c \
					puzzle_status_1.c puzzle_status_2.c bfs.c bfs_1.c \
					alg_toop.c alg_toop_1.c \
					open_set.c \
					alg_a_star.c distance_taxicab.c \
					alg_ida_star.c
SRC_H_FILES		=	n_puzzle.h
LOCAL_LIBS		=	libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS		=	libssl.a libcrypto.a libm.a
LOCAL_LIB_FILES	=	$(addprefix $(LIB)/, $(LOCAL_LIBS))
LIB_FILES		=	$(addprefix -l , $(patsubst lib%.a, %, $(LOCAL_LIBS)))
LIB_FILES		+=	$(addprefix -l , $(patsubst lib%.a, %, $(GLOBAL_LIBS)))

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))
APP_FILES		=	$(addprefix $(BIN)/, $(NAMES))

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-g -Wall -Wextra -Werror $(INCLUDES) $(MAC_INCLUDES)
LD_FLAGS		=	-std=gnu17 $(MAC_LD_FLAGS) \
					-L$(LIB) $(LIB_FILES) \
					$(D_ATTRIBUTES)

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

SELF_SIGNED_CRT	=	/var/tmp/tls-selfsigned.crt
SELF_SIGNED_KEY	=	/var/tmp/tls-selfsigned.key

.PHONY: all
all: $(SELF_SIGNED_CRT) $(FOLDERS) $(H_FILES) $(C_FILES) libraries $(APP_FILES)
	@echo "$(LOCAL_LIB_FILES)"
	@echo "$(GREEN)Done!$(END)"

$(APP_FILES): $(BIN)/%: $(SRC)/%.c $(H_FILES) $(O_FILES)
	$(CC) -o $@ $< $(O_FILES) $(LD_FLAGS) $(C_FLAGS)

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile $(LOCAL_LIB_FILES)
	$(CC) -c -o $@ $< $(C_FLAGS) $(D_ATTRIBUTES)

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
ifeq ($(OS), Darwin)
	cat $(MAP_FILE) | $(BIN)/$(NAME) -L $(LOGING_LEVEL) \
	-A $(ALGORITHM) -D $(PRINT_DELAY)
else
	cat $(MAP_FILE) | valgrind -s --tool=memcheck \
	--leak-check=full --show-leak-kinds=all $(BIN)/$(NAME) -L $(LOGING_LEVEL) \
	-A $(ALGORITHM) -D $(PRINT_DELAY)
endif

.PHONY: run_loop
run_loop: all
ifeq ($(OS), Darwin)
	while [ 1 -eq 1 ] ; do python ./bin/PuzzleGenerator.py ${MAX_MOVES} -s $(PUZZLE_SIZE) \
		| $(BIN)/$(NAME) -L $(LOGING_LEVEL) -rA $(ALGORITHM) -D $(PRINT_DELAY) \
		$(PUZZLE_GUI) ; \
		done
else
	while [ 1 -eq 1 ] ; do ./bin/PuzzleGenerator.py ${MAX_MOVES} -s $(PUZZLE_SIZE) \
		| $(BIN)/$(NAME) -L $(LOGING_LEVEL) -rA $(ALGORITHM) -D $(PRINT_DELAY) \
		$(PUZZLE_GUI) ; done
endif
.PHONY: run_test
run_test: all
	while [ 1 -eq 1 ] ; \
	do \
		python3 test/n-puzzle_test.py ; \
	done

$(SELF_SIGNED_CRT):
	openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout $(SELF_SIGNED_KEY) \
	-out $(SELF_SIGNED_CRT) \
	-days 365 \
	-subj "/C=FI/ST=Uusimaa/L=Espoo/O=/OU=Hive/CN=n-puzzle"
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
ifeq ($(OS), Darwin)
	norminette-beta $(SRC)/* $(INCLUDE)/*
else
	norminette $(SRC)/* $(INCLUDE)/*
endif
