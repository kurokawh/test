// https://www.geekpage.jp/programming/linux-network/book/07/7-5.php

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int global_val = 0;

void *
thread_start_routine(void *data)
{
  int val = (int64_t)data;
  int i;

  printf("thread_start_routine : val=%d\n", val);
  for (i=0; i<10; i++) {
    global_val++;
    printf("thread_start_routine : i=%d, g=%d\n", i, global_val);

    sleep(1);
  }

  return NULL;
}

#define THREAD_NUM 10
int
main()
{
  int i;
  pthread_t th[THREAD_NUM];
  void *th_ret[THREAD_NUM];

  for (int j = 0; j < THREAD_NUM; j++) {
	  if (pthread_create(&th[j], NULL, thread_start_routine, (void *)100) != 0) {
		  perror("pthread_create");
		  return 1;
	  }
  }

  for (i=0; i<10; i++) {
    global_val++;
    printf("main : i=%d, g=%d\n", i, global_val);

    sleep(1);
  }

  for (int j = 0; j < THREAD_NUM; j++) {
	  int ret = pthread_join(th[j], &th_ret[j]);
	  printf("th_ret[%d]: %p: ret: %d\n", j, th_ret[j], ret);
	  if (ret != 0) {
		  perror("pthread_join");
		  return 1;
	  }
  }

  return 0;
}
