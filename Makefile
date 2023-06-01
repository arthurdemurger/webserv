# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdony <hdony@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:46:45 by ademurge          #+#    #+#              #
#    Updated: 2023/05/30 13:53:57 by hdony            ###   ########.fr        #
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

SRC			=	src/server/Server.cpp \
				src/server/Socket.cpp \
				src/server/Config.cpp \
				src/server/Utils.cpp \
				src/server/client/Client.cpp \
				src/server/client/Request.cpp \
				src/server/Location.cpp \
				src/server/client/Response.cpp \
				src/parser/Parser.cpp \
				src/Launcher.cpp \
				src/main.cpp

OBJ	=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

# Progress counter
TOTAL_FILES		=	$(words $(SRC))
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

$(NAME): $(OBJ)
	@$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)
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
