/*
** main.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/server_src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 19:20:45 2014 Elliot Kersale
** Last update Mon Mar 24 21:13:57 2014 Elliot Kersale
*/

#include		"serveur.h"

int			main(int ac, char **av)
{
  if (ac != 2)
    {
      fprintf(stderr, "Usage : ./serveur port\n");
      return (EXIT_FAILURE);
    }
  connect_serv(av[1]);
  return (EXIT_SUCCESS);
}
