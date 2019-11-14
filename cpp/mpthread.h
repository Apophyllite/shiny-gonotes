#ifndef MPTHREAD_H
#define MPTHREAD_H
#include<event.h>
#include<map>

using namespace std;
class Mpthread
{
	public:
		Mpthread(int sock_1);
		~Mpthread();

		int _sock_1;///socketpair1
		struct event_base* _base;//libevent
		map<int,struct event*> _event_map;//保存事件的map

};



#endif 
