/*
** connexion.c for myirc in /home/kersal_e/Dropbox/myirc/irc_tmp/src_server
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 20:25:26 2014 Elliot Kersale
** Last update Tue Apr 29 21:19:49 2014 Elliot Kersale
*/

#include		"serveur.h"

int			init_serveur(t_serv *serv)
{
  if ((serv->s = socket(AF_INET, SOCK_STREAM, serv->proto->p_proto)) == -1)
    {
      perror("");
      return (EXIT_FAILURE);
    }
  if (get_bind(serv) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  start_serv();
  if (my_listen(&serv->s) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  serv->client_len = sizeof(serv->sin_client);
  return (EXIT_SUCCESS);
}

int			read_client(int sock, char *buffer)
{
  int			n;

  n = 0;
  if((n = recv(sock, buffer, 4096, 0)) < 0)
    {
      perror("recv()");
      n = 0;
    }
  buffer[n] = 0;
  return n;
}

void			write_msg(char *buffer, int sock)
{
  if (send(sock, buffer, strlen(buffer), 0) < 0)
    {
      perror("send()");
      return ;
    }
}
