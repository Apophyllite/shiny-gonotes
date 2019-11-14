#include<pthread.h>
#include<event.h>
#include"mpthread.h"
#include<iostream>
#include<vector>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;


void cli_cb(int fd,short event,void* arg)
{
	//recv   ->buff
	std::cout << " cli event happened! " << std::endl;
	
	//buff->contral     
	char buff[1024] = {0};
	
	if(0 < recv(fd,buff,99,0))
	{
		cout<<" get message from cli: "<<buff<<endl;
		if(-1 == send(fd,"ok",3,0))
		{
			cerr<<"send fail;errno:"<<errno<<endl;
			return;
		}
	}
}

void sock_1_cb(int fd,short event,void *arg)
{
	Mpthread* mthis = (Mpthread*)arg;	

	//recv   cli_fd
	char buff[1024];
	if (-1 == read(fd,buff,1024)) {
		cerr<<"sock_1 read cli_fd failed!"<<endl;
		return;
	}
	int i = 0;
	for(; i < 1024; i++) {
		if ( buff[i] == '#' ) break;	
	}
	char n_buff[i];
	for(int j = 0; j < i; j++) n_buff[j] = buff[j];
	int cli_fd = atoi(n_buff);
	
	//将cli_fd加入libevent  -》cli_cb()
	struct event* cli_event = event_new(mthis->_base,cli_fd,EV_READ|EV_PERSIST,cli_cb,(void *)mthis);

	event_add(cli_event,NULL);
	event_base_dispatch(mthis->_base);

	//将事件加入到_event_map
	mthis->_event_map[cli_fd] = cli_event;

	sprintf(buff,"%lu#",mthis->_event_map.size());
	write(fd,buff,1024);
	return;
}


void *pth_run(void *arg)
{
	Mpthread* mthis = (Mpthread*)arg;

	//.h定义 struct event_base* _base;//libevent
	mthis->_base = event_base_new();
	
	//将sock_1 加入到libevnet  ->sock_1_cb(  ,mthis, )
	struct event* sock_1_event = event_new (mthis->_base,mthis->_sock_1,EV_READ|EV_PERSIST,sock_1_cb,(void *)mthis); 

	event_add(sock_1_event,NULL);

	event_base_dispatch(mthis->_base);
	return NULL;
}

Mpthread::Mpthread(int sock_1)
{
	_sock_1 = sock_1;

	//启动子线程
}
