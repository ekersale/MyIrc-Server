/*
** strnncpy.c for strnncpy in /home/kersale/Dropbox/myirc/PSU_2013_myirc/src_client
** 
** Made by Elliot Kersale
** Login   <kersale@ubuntu>
** 
** Started on  Wed Apr 16 18:21:36 2014 Elliot Kersale
** Last update Wed Apr 16 18:31:21 2014 Elliot Kersale
*/

#include		"my_irc.h"

char			*strnncpy(char *buff, int start, int end)
{
  char		*res;
  int		n;
  int		i;

  i = start;
  n = 0;
  if ((res = malloc(strlen(buff) * sizeof(char))) == NULL)
    return (NULL);
  while (i < end)
    {
      res[n] = buff[i];
      i++;
      n++;
    }
  res[n] = '\0';
  return (res);
}
