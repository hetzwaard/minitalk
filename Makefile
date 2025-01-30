# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mahkilic <mahkilic@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2025/01/26 08:08:59 by mahkilic      #+#    #+#                  #
#    Updated: 2025/01/26 08:21:28 by mahkilic      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Sources & Directories
CLIENT = src/client/client.c
CLIBON = src/client/client_bonus.c
SERVER = src/server/server.c
SERBON = src/server/server_bonus.c
OBJECT = objects
INCLUD = include
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

# Names
CLIENT_NAME = client
SERVER_NAME = server
CLIBON_NAME = client_bonus
SERBON_NAME = server_bonus

# Colors for output
GREEN		=	\033[0;32m
ORANGE	=	\033[38;5;214m
GRAY		=	\033[0;90m

# Rules
all: $(LIBFT) $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT) $(LIBFT)
	@$(CC) $(CFLAGS) $(CLIENT) -I$(INCLUD) -L$(LIBFTDIR) -lft -o $(CLIENT_NAME)
	@echo "$(GREEN)$(CLIENT_NAME) has been created."

$(SERVER_NAME): $(SERVER) $(LIBFT)
	@$(CC) $(CFLAGS) $(SERVER) -I$(INCLUD) -L$(LIBFTDIR) -lft -o $(SERVER_NAME)
	@echo "$(GREEN)$(SERVER_NAME) has been created."
	
$(LIBFT):
	@make -C $(LIBFTDIR)

bonus: $(LIBFT) $(CLIBON_NAME) $(SERBON_NAME)

$(CLIBON_NAME): $(CLIBON) $(LIBFT)
	@$(CC) $(CFLAGS) $(CLIBON) -I$(INCLUD) -L$(LIBFTDIR) -lft -o $(CLIBON_NAME)
	@echo "$(GREEN)$(CLIBON_NAME) has been created."

$(SERBON_NAME): $(SERBON) $(LIBFT)
	@$(CC) $(CFLAGS) $(SERBON) -I$(INCLUD) -L$(LIBFTDIR) -lft -o $(SERBON_NAME)
	@echo "$(GREEN)$(SERBON_NAME) has been created."

clean:
	@rm -rf $(LIBFTDIR)/*.o
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -rf $(LIBFT)
	@rm -rf $(CLIENT_NAME)
	@rm -rf $(CLIBON_NAME)
	@rm -rf $(SERVER_NAME)
	@rm -rf $(SERBON_NAME)
	@echo "$(ORANGE)All targets have been removed."

re: fclean all

.PHONY: all clean fclean re