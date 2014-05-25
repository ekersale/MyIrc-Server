/*
** my_error.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/client_src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 15:06:36 2014 Elliot Kersale
** Last update Fri Apr 11 15:23:39 2014 Elliot Kersale
*/

#include		"client.h"

int			error(char *s)
{
  perror(s);
  return (EXIT_FAILURE);
}
