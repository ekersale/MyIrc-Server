/*
** connexion.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/client_src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 15:01:53 2014 Elliot Kersale
** Last update Tue Apr 29 22:00:49 2014 Elliot Kersale
*/

#include		"client.h"

int			connect_client(char *port, char *ip, int *sock)
{
  struct protoent	*proto;
  struct sockaddr_in	sin;
  int			s;
  int			por;
  int			cs;

  if (port == NULL || ip == NULL)
    return (EXIT_FAILURE);
  por = atoi(port);
  proto = getprotobyname(TCP);
  if ((s = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    return (error("socket()"));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(por);
  sin.sin_addr.s_addr = inet_addr(ip);
  if ((cs = connect(s, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
    return (error("connect()"));
  *sock = s;
  send(s, UNKNOW, strlen(UNKNOW), 0);
  return (EXIT_SUCCESS);
}

void			connect_server(t_lib *lib, char *str, int *max)
{
  strtok(str, " ");
  if (connect_client(strtok(NULL, "\n"),
		     strtok(NULL, " "), &lib->s) != EXIT_FAILURE)
    {
      *max = lib->s;
      return ;
    }
  add_txt(&lib->msg, CO_ERROR);
  return ;
}
