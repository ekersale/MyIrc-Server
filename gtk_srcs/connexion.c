/*
** connexion.c for myirc in /home/kersal_e/projet_actuels/PSU_2013_myirc/src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Apr 14 11:11:25 2014 Elliot Kersale
** Last update Wed Apr 23 16:42:50 2014 Elliot Kersale
*/

#include		"my_irc.h"

void			write_histo(char *s)
{
  FILE			*histo;

  if ((histo = fopen(".histo", "a+")) != NULL)
    {
      fwrite(s, 1, strlen(s), histo);
      fclose(histo);
    }
  return ;
}

int                     connect_client(char *ip, int *sock)
{
  struct protoent       *proto;
  struct sockaddr_in    sin;
  int                   s;
  int			cs;

  proto = getprotobyname("TCP");
  if ((s = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    {
      perror("");
      return (EXIT_FAILURE);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(2001);
  sin.sin_addr.s_addr = inet_addr(ip);
  if ((cs = connect(s, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      perror("");
      return (-1);
    }
  *sock = s;
  return (0);
}
