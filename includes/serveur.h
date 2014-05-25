/*
** serveur.h for myftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/sources
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 16:56:06 2014 Elliot Kersale
** Last update Tue Apr 29 22:38:16 2014 Julien Thompson
*/

#ifndef			_SERVEUR_H__
# define		_SERVEUR_H__
/*
** INCLUDES
*/
#include                <sys/types.h>
#include                <sys/socket.h>
#include                <unistd.h>
#include                <stdlib.h>
#include                <string.h>
#include                <netdb.h>
#include		<time.h>
#include		<stdio.h>
#include                <netinet/in.h>
#include                <arpa/inet.h>
#include		<signal.h>
#include		<sys/stat.h>
#include		<fcntl.h>

/*
** DEFINES
*/
# define		START_SERVER		"\r   \n\033[32mServer started the %s\n\033[0m"
# define		SDONE			"\r   \n\033[32mServer disconnection - Execution time : %.0f secondes\n\033[0m"
# define		INCORRECT_PORT		"Port %d is incorrect\n"
# define		FORBIDDEN_CHAR		"/\n\\"
# define		REPLACED_CHAR		"\t "
# define		REPLACING_CHAR		'_'
# define		ERROR_OCC		"An error has occurred\n"
# define		CHAN_LEFT		"Channel left\n"
# define		CHAN_JOIN		"Channel join\n"
# define		CHAN_AV			"Channel available :\n"
# define		CHAN_CO			"Channel [%s] user connected : \n"
# define		CO_CLI			"A client is connected\n"
# define		DECO_CLI		"%s disconnected\n"
# define		USER_NF			"User not found\n"
# define		NICK			"/nick"
# define		LIST			"/list"
# define		JOIN			"/join"
# define		PART			"/part"
# define		USERS			"/users"
# define		MSG			"/msg"
# define		TCP			"TCP"
# define		ERR_SET_NAME		"You didn't pass any name\n"
# define		NOW_KNOWN		"Your are now known as '%s'\n"
# define		DEFAULT_USER		"Anonymous"

/*
** STRUCTURES
*/
typedef	struct		s_serv
{
  struct protoent       *proto;
  struct sockaddr_in    sin_client;
  int                   client_len;
  int                   s;
  int                   port;
  int                   cs;
}			t_serv;

typedef	struct		s_user
{
  char			*name;
  int			socket;
  char			*chan;
  struct s_user		*next;
}			t_user;

typedef	struct		s_chan
{
  char			*name;
  struct s_chan		*next;
}			t_chan;
/*
** channel.c
*/
int			show_channel(t_user *, t_user *, char *, char *);
int			set_channel(t_user *, t_user *, char *, char *);
/*
** connexion.c
*/
int			init_serveur(t_serv *);
int			read_client(int, char *);
void			write_msg(char *, int);
/*
** cmd_users.c
*/
void			void_value(char *, char *);
int			show_users(t_user *, t_user *, char *, char *);
/*
** format_string.c
*/
int			is_in_base(char, char *);
void			insert_valid_char(char *, char *);
void			replace_char(char *);
char			*format_name(char *);
/*
** init_func.c
*/
int                     my_listen(int *);
int                     get_bind(t_serv *);
int                     check_port(int);
void                    start_serv();
int			my_error(char *);
/*
** select.c
*/
void			client_connexion(int *, int, fd_set *);
void			close_client(t_user *, t_user **);
void			reset_list(fd_set *, t_user *, t_serv *, int);
void			accept_connect(int *, t_serv *);
int			run_serveur(t_serv *);
/*
** send_msg.c
*/
void			who_s_send(t_user *, char *, t_user *, int);
int			send_msg(t_user *, t_user *, char *, int);
int			send_spe_msg(t_user *, t_user *, char *, char *);
/*
** send_recv.c
*/
int			send_rcv(t_user **, fd_set *);
/*
** server.c
*/
void			disconnect();
int			check_cmd(char *, t_user *, t_user *);
int			connect_serv(char *);
/*
** set_name.c
*/
void			put_name_list(t_user *, char *);
int			set_name(t_user *, t_user *, char *, char *);
/*
** users.c
*/
int			add_user(t_user **, char *, int, char *);
int			remove_user(t_user **, char *);
/*
**
*/
#endif		/*	_SERVEUR_H__   	*/
