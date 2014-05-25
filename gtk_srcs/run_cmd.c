/*
** run_cmd.c for run_cmd in /home/kersale/Dropbox/myirc/PSU_2013_myirc/src_client
** 
** Made by Elliot Kersale
** Login   <kersale@ubuntu>
** 
** Started on  Wed Apr 16 18:22:16 2014 Elliot Kersale
** Last update Sun Apr 27 18:29:35 2014 Elliot Kersale
*/

#include		"my_irc.h"
#include		"format_string.h"

void                    write_msg(char *buffer, int cs)
{
  if (send(cs, buffer, strlen(buffer), 0) < 0)
    {
      display_failure("Error on connexion\n");
      return ;
    }
}

int                     read_server(char *buffer, int cs)
{
  int                   n;

  n = 0;
  if((n = recv(cs, buffer, 4096, 0)) < 0)
    {
      perror("recv()");
      n = 0;
    }
  buffer[n] = 0;
  return n;
}
