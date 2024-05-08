NAME = pipex
BONUS = pipex_bonus

CC = cc
CFLAGS =  -g -fsanitize=address
RM = rm -fr
MKDIR = mkdir -p

LIBFT_DIR = lib/Libft
LIBFT = -L$(LIBFT_DIR) -lft

INC_DIR = inc
SRC_DIR = src/mandatory
OBJ_DIR = obj
SRC_BONUS_DIR = src/bonus
OBJ_BONUS_DIR = obj_bonus

HEADERS = -I $(INC_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRCS_BONUS = $(wildcard $(SRC_BONUS_DIR)/*.c)
OBJS_BONUS = $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/pipex.h
	@$(MKDIR) $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS)
	@make -s bonus -C $(LIBFT_DIR)
	@echo "Building $@..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$@ is ready!"

bonus: $(BONUS)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c $(INC_DIR)/pipex_bonus.h
	@$(MKDIR) $(OBJ_BONUS_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BONUS): $(OBJS_BONUS)
	@make -s bonus -C $(LIBFT_DIR)
	@echo "Building $@..."
	@$(CC) $(CFLAGS) -o $(BONUS) $(OBJS_BONUS) $(LIBFT)
	@echo "$@ is ready!"

clean:
	@echo "Cleaning object files..."
	@make -s clean -C $(LIBFT_DIR)
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Cleaning $(NAME)..."
	@make -s fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus