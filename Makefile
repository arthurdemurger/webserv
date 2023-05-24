# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:46:45 by ademurge          #+#    #+#              #
#    Updated: 2023/05/19 17:03:57 by ademurge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
BLACK		= $(shell tput -Txterm setaf 0)
RED			= $(shell tput -Txterm setaf 1)
GREEN		= $(shell tput -Txterm setaf 2)
YELLOW		= $(shell tput -Txterm setaf 3)
LIGHTPURPLE = $(shell tput -Txterm setaf 4)
PURPLE		= $(shell tput -Txterm setaf 5)
BLUE		= $(shell tput -Txterm setaf 6)
WHITE		= $(shell tput -Txterm setaf 7)
RESET		= $(shell tput -Txterm sgr0)

# Name of the executable
NAME		=	webserv

# Flags
CC			=	c++

CPPFLAGS	=	-std=c++98

RM			=	rm -rf

# Files
OBJDIR		=	.obj

SRC_SERV	=	src/server/Server.cpp

SRC_SOCK	=	src/sockets/BindSocket.cpp \
				src/sockets/ConnectSocket.cpp \
				src/sockets/ListenSocket.cpp \
				src/sockets/Socket.cpp

SRC_REQUEST =	src/request/Client.cpp \
				src/request/Response.cpp \
				src/request/Request.cpp

SRC_MAIN	=	src/main.cpp

OBJ_SERV	=	$(addprefix $(OBJDIR)/, $(SRC_SERV:.cpp=.o))
OBJ_SOCK	=	$(addprefix $(OBJDIR)/, $(SRC_SOCK:.cpp=.o))
OBJ_REQUEST	=	$(addprefix $(OBJDIR)/, $(SRC_REQUEST:.cpp=.o))
OBJ_MAIN	=	$(addprefix $(OBJDIR)/, $(SRC_MAIN:.cpp=.o))

# Progress counter
TOTAL_FILES		=	$(words $(SRC_SERV) $(SRC_SOCK) $(SRC_REQUEST) $(SRC_MAIN))
CURRENT_FILE	=	0
PERCENTAGE		=	0

define PRINT_PROGRESS
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE)*100/$(TOTAL_FILES)))))
	@awk 'BEGIN { printf "$(BLUE)... [%d%%] Compiling $<...", $(PERCENTAGE); \
		for (i = 0; i < $(PERCENTAGE); i++) \
			printf "\r"; \
		printf "\r"; \
		if ($(PERCENTAGE) == 100) { \
				printf("\033[K$(BLUE)... cpp files compiled.$(RESET)\n");	}}'
endef

# Rules
all: $(NAME)

$(NAME): $(OBJ_SERV) $(OBJ_REQUEST) $(OBJ_SOCK) $(OBJ_MAIN)
	@$(CC) $(CPPFLAGS) $(OBJ_SERV) $(OBJ_REQUEST) $(OBJ_SOCK) $(OBJ_MAIN) -o $(NAME)
	@echo "$(GREEN)... executable compiled$(RESET)"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(PRINT_PROGRESS)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@echo "$(RED)... object files removed$(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED)... executable removed$(RESET)"

re:	fclean $(NAME)

.PHONY: all clean fclean re'
