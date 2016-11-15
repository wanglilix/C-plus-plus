//1生产者 1消费者 1缓冲区   
//使用二个事件，一个表示缓冲区空，一个表示缓冲区满。   
//再使用一个关键段来控制缓冲区的访问   
#include <stdio.h>   
#include <process.h>   
#include <windows.h>   
//设置控制台输出颜色   
BOOL SetConsoleColor(WORD wAttributes)  
{  
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  
	if (hConsole == INVALID_HANDLE_VALUE)  
		return FALSE;     
	return SetConsoleTextAttribute(hConsole, wAttributes);  
}  
const int END_PRODUCE_NUMBER = 10;   //生产产品个数   
int g_Buffer;                        //缓冲区   
//事件与关键段   
CRITICAL_SECTION g_cs;  
HANDLE g_hEventBufferEmpty, g_hEventBufferFull;  

unsigned int __stdcall ProducerThreadFunc(LPVOID PM)
{
	for(int i = 1; i <= END_PRODUCE_NUMBER; i ++)
	{
		WaitForSingleObject(g_hEventBufferEmpty,INFINITE);

		EnterCriticalSection(&g_cs);
		g_Buffer = i;
		printf("生产者往缓冲区放置%d个产品\n",i);
		LeaveCriticalSection(&g_cs);

		SetEvent(g_hEventBufferFull);	//发出缓冲区有产品信号
	}

	return 0;
}

unsigned int __stdcall ConsumerThreadFunc(LPVOID PM)
{
	volatile bool flag = true;
	while(flag)
	{
		WaitForSingleObject(g_hEventBufferFull,INFINITE);
		EnterCriticalSection(&g_cs);
		SetConsoleColor(FOREGROUND_RED);
		printf(" 消费者在缓冲区取走%d个产品\n",g_Buffer);
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		if(g_Buffer == END_PRODUCE_NUMBER)
			flag = false;
		LeaveCriticalSection(&g_cs);

		SetEvent(g_hEventBufferEmpty);//通知缓冲区空
	}

	return 0;
}

int main()
{
	printf("生产消费者简单问题：1生产者 1消费者 1缓冲区\n\n\n");
	InitializeCriticalSection(&g_cs);
	g_hEventBufferEmpty = CreateEvent(NULL,FALSE,TRUE,NULL);
	g_hEventBufferFull = CreateEvent(NULL,FALSE,FALSE,NULL);

	const int Thread_NUM = 2;
	HANDLE handleThread[Thread_NUM];
	handleThread[0] = (HANDLE)_beginthreadex(NULL,0,ProducerThreadFunc,NULL,0,NULL);
	handleThread[1] = (HANDLE)_beginthreadex(NULL,0,ConsumerThreadFunc,NULL,0,NULL);

	WaitForMultipleObjects(Thread_NUM,handleThread,TRUE,INFINITE);

	CloseHandle(handleThread[0]);
	CloseHandle(handleThread[1]);

	CloseHandle(g_hEventBufferEmpty);
	CloseHandle(g_hEventBufferFull);
	DeleteCriticalSection(&g_cs);
}