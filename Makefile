# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:46:45 by ademurge          #+#    #+#              #
#    Updated: 2023/05/19 15:55:29 by ademurge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	webserv

CC			=	c++
CPPFLAGS	=	-std=c++98
RM			=	rm -rf

OBJDIR		=	.obj

SRC_SERV	=	src/server/Server.cpp

SRC_SOCK		=	src/sockets/BindSocket.cpp \
					src/sockets/ConnectSocket.cpp \
					src/sockets/ListenSocket.cpp \
					src/sockets/Socket.cpp

SRC_REQUEST		=	src/request/Client.cpp \
					src/request/Response.cpp \
					src/request/Request.cpp \

SRC_MAIN	=		src/main.cpp

OBJ_SERV					=	$(addprefix $(OBJDIR)/, $(SRC_SERV:.cpp=.o))
OBJ_SOCK					=	$(addprefix $(OBJDIR)/, $(SRC_SOCK:.cpp=.o))
OBJ_REQUEST					=	$(addprefix $(OBJDIR)/, $(SRC_REQUEST:.cpp=.o))
OBJ_MAIN					=	$(addprefix $(OBJDIR)/, $(SRC_MAIN:.cpp=.o))

all:			$(NAME)

$(NAME):		$(OBJ_SERV) $(OBJ_REQUEST) $(OBJ_SOCK) $(OBJ_MAIN)
				$(CC) $(CPPFLAGS) $(OBJ_SERV) $(OBJ_REQUEST) $(OBJ_SOCK) $(OBJ_MAIN) -o $(NAME)

$(OBJDIR)/%.o:	%.cpp
				@mkdir -p $(dir $@)
				@$(CC) $(CPPFLAGS) -c $< -o $@
				@echo "Compiled $<"

clean:
				$(RM) $(OBJDIR) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY: all clean fclean re