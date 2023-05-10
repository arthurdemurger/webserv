# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 11:46:45 by ademurge          #+#    #+#              #
#    Updated: 2023/05/10 15:37:59 by ademurge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	webserv

CC			=	c++
CPPFLAGS	=	-std=c++98
RM			=	rm -rf

OBJDIR		=	.obj

SRC			=	src/sockets/BindSocket.cpp \
				src/sockets/ConnectSocket.cpp \
				src/sockets/ListenSocket.cpp \
				src/sockets/Socket.cpp \
				src/server/Server.cpp \
				src/main.cpp

OBJ			=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o:	%.cpp
				@mkdir -p $(dir $@)
				@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJDIR) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY: all clean fclean re