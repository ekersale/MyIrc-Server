/*
** main.c for myftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 14:27:19 2014 Elliot Kersale
** Last update Tue Apr 29 21:32:51 2014 Elliot Kersale
*/

#include		"serveur.h"

time_t			start;

void			disconnect()
{
  time_t		end;

  time(&end);
  fprintf(stdout, SDONE, difftime(end, start));
  fflush(stdout);
  exit(EXIT_SUCCESS);
}

int			check_cmd(char *buff, t_user *list, t_user *tmp)
{
  char			*token;
  int			i;

  i = 0;
  while (buff[i] == ' ')
    i++;
  if (buff[i] != '/')
    return (EXIT_FAILURE);
  token = strtok(buff, " \n");
  if (token != NULL)
    {
      if (strcmp(token, NICK) == 0)
	return (set_name(list, tmp, strtok(NULL, " \n"), NULL));
      if (strcmp(token, LIST) == 0)
	return (show_channel(list, tmp, strtok(NULL, " \n"), NULL));
      if (strcmp(token, JOIN) == 0)
	return (set_channel(list, tmp, strtok(NULL, " \n"), NULL));
      if (strcmp(token, PART) == 0)
	return (set_channel(list, tmp, NULL, NULL));
      if (strcmp(token, USERS) == 0)
	return (show_users(list, tmp, NULL, NULL));
      if (strcmp(token, MSG) == 0)
	return (send_spe_msg(list, tmp, strtok(NULL, "\0"), strtok(NULL, " \n")));
    }
  return (EXIT_FAILURE);
}

int			connect_serv(char *port)
{
  t_serv		serv;

  time(&start);
  signal(SIGINT, disconnect);
  serv.port = atoi(port);
  serv.proto = getprotobyname(TCP);
  if (check_port(serv.port) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (init_serveur(&serv) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  run_serveur(&serv);
  return (EXIT_SUCCESS);
}
