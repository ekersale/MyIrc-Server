##
## Makefile for epikong in /home/kersal_e/rush-epikong
## 
## Made by Elliot Kersale
## Login   <kersal_e@epitech.net>
## 
## Started on  Fri Mar  7 20:47:19 2014 Elliot Kersale
## Last update Tue Apr 29 22:07:13 2014 Elliot Kersale
##


CLIENT_NAME	=	client

CLIENT_SRCS	=	./src_client/client.c		\
			./src_client/ncurses.c		\
			./src_client/thread.c		\
			./src_client/my_error.c		\
			./src_client/txt.c		\
			./src_client/connexion.c	\
			./src_client/main.c		\
			./src_client/input_ncurses.c

CFLAGS		=	-Wall -W -Werror -Iincludes

LDFLAGS		=	-lncurses -lpthread

CLIENT_OBJS	=	$(CLIENT_SRCS:.c=.o) 

$(CLIENT_NAME)	:	$(CLIENT_OBJS)
			$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS) $(LDFLAGS)

SERV_NAME	=	server

SERV_SRCS	=	./src_server/main.c		\
			./src_server/serveur.c		\
			./src_server/init_func.c	\
			./src_server/user.c		\
			./src_server/format_name.c	\
			./src_server/select.c		\
			./src_server/set_name.c		\
			./src_server/send_msg.c		\
			./src_server/cmd_users.c	\
			./src_server/channel.c		\
			./src_server/connexion.c	\
			./src_server/send_recv.c

SERV_OBJS	=	$(SERV_SRCS:.c=.o)

$(SERV_NAME)	:	$(SERV_OBJS)
			$(CC) $(SERV_OBJS) -o $(SERV_NAME)

CC		=	gcc

RM		=	rm -rf

all		:	$(SERV_NAME) $(CLIENT_NAME)

clean		:
			$(RM) $(CLIENT_OBJS)
			$(RM) $(SERV_OBJS)

fclean		:	clean
			$(RM) $(SERV_NAME)
			$(RM) $(CLIENT_NAME)

re		:	fclean all
