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
	char share_mem_ptr_2[15]={0};
	int share_mem_id;
	int tick;
	if ((share_mem_id=shmget(SHARE_MEM_KEY,0,SHARE_MEM_MODE)) < 0){
		perror("shmget failed");
		return -1;
	}
	if ((share_mem_ptr=shmat(share_mem_id,0,0)) == (void *)-1){
		perror("shmat failed");
		shmctl(share_mem_id,IPC_RMID,0);
		return -1;
	}
	for(tick=0;tick<15;tick++){
		strncpy(share_mem_ptr_2,share_mem_ptr,10);
		printf("%s\n",share_mem_ptr_2);
		sleep(1);
	}
	strncpy(share_mem_ptr_2,share_mem_ptr,10);
	printf("%s\n",share_mem_ptr_2);
	shmdt(share_mem_ptr);
	return 0;
}
