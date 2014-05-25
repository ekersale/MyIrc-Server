/*
** init_func.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/sources
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 17:14:46 2014 Elliot Kersale
** Last update Tue Apr 29 21:24:02 2014 Elliot Kersale
*/

#include		"serveur.h"

int			my_error(char *s)
{
  perror(s);
  return (EXIT_FAILURE);
}

void                    start_serv()
{
  time_t                date;

  time(&date);
  fprintf(stdout, START_SERVER, ctime(&date));
  fflush(stdout);
  return ;
}

int                     check_port(int port)
{
  if (port <= 1024 || port >= 49151)
    {
      fprintf(stderr, INCORRECT_PORT, port);
      fflush(stdout);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int                     get_bind(t_serv *serv)
{
  struct sockaddr_in    sin;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(serv->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if ((bind(serv->s, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      perror("");
      close(serv->s);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int                     my_listen(int *s)
{
  if (listen(*s, 3) == -1)
    return (my_error(""));
  return (EXIT_SUCCESS);
}
