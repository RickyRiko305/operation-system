#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<errno.h>
#define buff_size 10
typedef int bool;
//void chkerror()
//{
//	if(errno)
//	{
//		printf("Error %d\n",errno);
//		exit(0);
//	}
//}
typedef struct{
	char q[buff_size];
	int st,en;
} data;
char pop(data *link_list)
{
	char ans = link_list->q[link_list->st];
	link_list->st = (link_list->st+1)%buff_size;
	return ans;
}
bool empty(data *link_list)
{
	return link_list->st == link_list->en;
}
int main()
{
	key_t key = ftok("1.c",53);
	//chkerror();
	int shmid = shmget(key,sizeof(data),0777|IPC_CREAT);
	//chkerror();
	data *link_list = (data*) shmat(shmid,NULL,SHM_RND);
	//chkerror();
	for(int i=0;i<1000;i++)
	{
		// printf("%d\n",i);
		while(empty(link_list));//WAIT
		printf("%c",pop(link_list));
	}
	printf("\n");
	shmdt(link_list);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
