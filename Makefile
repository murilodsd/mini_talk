CC=cc
CCFLAGS=-Wall -Wextra -Werror -g
NAME_SERVER=server
NAME_CLIENT=client
#NAME_BONUS=
SRC_PATH=src/
SRCS_NAMES_SERVER=server.c 
SRCS=$(addprefix $(SRC_PATH), $(SRCS_NAMES_SERVER))
SRCS_NAMES_CLIENT=client.c signals_utils.c
SRCS=$(addprefix $(SRC_PATH), $(SRCS_NAMES_CLIENT))
#SRCS_NAMES_BONUS= 
#SRCS_BONUS=$(addprefix $(SRC_PATH), $(SRCS_NAMES))
OBJ_PATH=build/
OBJS_NAMES_SERVER=$(SRCS_NAMES_SERVER:.c=.o)
OBJS_SERVER=$(addprefix $(OBJ_PATH), $(OBJS_NAMES_SERVER))
OBJS_NAMES_CLIENT=$(SRCS_NAMES_CLIENT:.c=.o)
OBJS_CLIENT=$(addprefix $(OBJ_PATH), $(OBJS_NAMES_CLIENT))
#OBJS_NAMES_BONUS=$(SRCS_NAMES_BONUS:.c=.o)
#OBJS_BONUS=$(addprefix $(OBJ_PATH), $(OBJS_NAMES_BONUS))
LIB_STATIC_NAME = libft.a
LIB_PATH=lib/
LIBS_FLAGS=-l$(patsubst lib%.a, %, $(LIB_STATIC_NAME)) -L$(LIB_PATH)
LIB_STATIC = $(addprefix $(LIB_PATH) , $(INCLUDE_PATH))
INCLUDE_PATH=./include/ ./lib/*/include/
INCLUDE_FLAG=$(addprefix -I , $(INCLUDE_PATH))

RM=rm -f

all: libs $(NAME_SERVER) $(NAME_CLIENT) 

$(NAME_SERVER): $(OBJS_SERVER) $(LIB_STATIC)
	$(CC) $(CCFLAGS) $(OBJS_SERVER) $(INCLUDE_FLAG) $(LIBS_FLAGS) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIB_STATIC)
	$(CC) $(CCFLAGS) $(OBJS_CLIENT) $(INCLUDE_FLAG) $(LIBS_FLAGS) -o $(NAME_CLIENT)

libs:
	make all -C lib/libft

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	make all -C lib/libft
	$(CC) $(CCFLAGS) $(OBJS_BONUS) $(INCLUDE_FLAG) $(LIBS_FLAGS) -o $(NAME_BONUS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDE_FLAG)

clean:
	make clean -C lib/libft
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_BONUS)

fclean: clean
	make fclean -C lib/libft
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_BONUS)

re: fclean all bonus

norm:
	norminette -R CheckDefine $(INCLUDE_PATH)*.h
	norminette -R CheckForbiddenSourceHeader $(SRC_PATH)*.c

.PHONY=all bonus clean fclean re norm libs
