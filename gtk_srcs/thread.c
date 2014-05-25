#include	<pthread.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"common.h"

void		lock_mutex(pthread_mutex_t *mutex)
{
  pthread_mutex_lock(mutex);
}

void		unlock_mutex(pthread_mutex_t *mutex)
{
  pthread_mutex_unlock(mutex);
}

pthread_t	init_thread(t_share *shared, void *(*routine) (void *))
{
  pthread_t	thread;

  if (pthread_create(&thread, NULL, routine, shared) < 0)
    {
      perror("thread init");
      return (0);
    }
  return (thread);
}

int             cancel_thread(pthread_t *thread)
{
  return (pthread_cancel(*thread));
}


void		join_thread(pthread_t *thread)
{
  pthread_join(*thread, NULL);
}

void		init_mutex(pthread_mutex_t *mutex)
{
  pthread_mutex_init(mutex, NULL);  
}
