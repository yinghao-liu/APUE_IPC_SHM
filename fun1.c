/*
 * Copyright (C) 2016 francis_hao 
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/shm.h>
#define SHARE_MEM_KEY	0x00ffff00
#define SHARE_MEM_MODE	0600
int main(void)
{	
	char *share_mem_ptr;
	int share_mem_id;
	int tick;
	if ((share_mem_id=shmget(SHARE_MEM_KEY,1024,(SHARE_MEM_MODE | IPC_CREAT | IPC_EXCL))) < 0){
		perror("shmget failed");
		return -1;
	}
	if ((share_mem_ptr=shmat(share_mem_id,0,0)) == (void *)-1){
		perror("shmat failed");
		shmctl(share_mem_id,IPC_RMID,0);
		return -1;
	}
	for(tick=0;tick<20;tick++){
		strncpy(share_mem_ptr,"--------",10);
		sleep(1);
		strncpy(share_mem_ptr,"++++++++",10);
		sleep(1);
	}
	strncpy(share_mem_ptr,"hello world!",10);
	sleep(3);
	shmdt(share_mem_ptr);
	shmctl(share_mem_id,IPC_RMID,0);
	return 0;
}
