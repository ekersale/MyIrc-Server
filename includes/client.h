/*
** client.h for myftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 19:29:59 2014 Elliot Kersale
** Last update Tue Apr 29 22:28:06 2014 Julien Thompson
*/

#ifndef			_CLIENT_H__
# define		_CLIENT_H__
/*
** INCLUDES
*/
#include		<ncurses/curses.h>
#include		<ncurses.h>
#include		<pthread.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		<string.h>
#include		<netdb.h>
#include		<stdio.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<sys/stat.h>
#include		<fcntl.h>
#include		<sys/ioctl.h>
/*
** DEFINE
*/
# define		TCP		"TCP"
# define		CEXIT		"exit\n"
# define		TITLE		"myIRC"
# define		CO_ERROR	"Usage : /server [ip] [port] || Server not found\n"
# define		EXIT		"/exit"
# define		SERVER		"/server"
# define		CO_SERVER	"Connect a server please\n"
# define		UNKNOW		"Anonymous"
# define		ERROR_SEND	"Error : send()\n"
/*
**
*/
typedef struct		s_txt
{
  char			buff[4096];
  int			y;
  struct s_txt		*prev;
  struct s_txt		*next;
}			t_txt;

typedef struct		s_lib
{
  WINDOW		*wb1;
  WINDOW		*wmsg;
  t_txt			*msg;
  WINDOW		*wb2;
  WINDOW		*win;
  t_txt			*in;
  int			x;
  int			y;
  pthread_mutex_t	mutex;
  int			s;
}			t_lib;
/*
** my_error.c
*/
int			error(char *);
/*
** client.c
*/
void			*do_actions(void *);
int			my_malloc(char **);
void			fdisset(t_lib *, char *, fd_set *);
int			init_ncurses(t_lib *);
/*
** connexion.c
*/
int			connect_client(char *, char *, int *);
void			connect_server(t_lib *, char *, int *);
/*
** thread.c
*/
void			lock_mutex(pthread_mutex_t *);
void			unlock_mutex(pthread_mutex_t *);
pthread_t		init_thread(t_lib *, void *(*) (void *));
void			join_thread(pthread_t *);
void			init_mutex(pthread_mutex_t *);
/*
** input_ncurses.c
*/
char			*get_input(t_lib *);
void			*routine_getinput(t_lib *);
void                    treat_input(t_lib *, char *);
/*
** ncurses.c
*/
int			count_lines(t_txt *);
int			get_win_size(int *, int *);
void			txt_to_win(WINDOW *, t_txt **);
void			refresh_all(t_lib *);
int			close_ncurses(t_lib *);
/*
** txt.c
*/
int			remove_txt(t_txt **);
int			add_txt(t_txt **, char *);
/*
**
*/
#endif		/*	_CLIENT_H__	*/
