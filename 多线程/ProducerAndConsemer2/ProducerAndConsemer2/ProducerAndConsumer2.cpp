//生产者与消费者问题：一个生产者，两个消费者

#include <stdio.h>
#include <Windows.h>
#include <process.h>

BOOL SetConsoleColor(WORD bwAttributes)
{
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hand == INVALID_HANDLE_VALUE)
		return FALSE;
	return SetConsoleTextAttribute(hand,bwAttributes);
}

HANDLE g_csBufferEmpty,g_csBufferFull;

//这个条件不一定必须需要，两个信号量就可以使生产者和消费者访问缓冲区不会造成冲突，
//这里互斥量的作用基本在于输出的颜色设置
CRITICAL_SECTION g_csParamer;
const int END_PRODUCE_NUM = 10;
const int BuffSize = 4;
int g_csProdecer,g_csConsumer;
int g_csBuffer[BuffSize];
bool _bIsEnd;//生产者完成标志

unsigned int __stdcall ProduceThreadFunc(LPVOID PM)
{
	for(int i = 1; i <= 10; i ++)
	{
		WaitForSingleObject(g_csBufferEmpty,INFINITE);

		EnterCriticalSection(&g_csParamer);
		g_csBuffer[g_csProdecer] = i;
		printf("生产者向缓冲池%d里投放了%d个产品\n",g_csProdecer,i);
		g_csProdecer = (g_csProdecer + 1) % BuffSize;
		LeaveCriticalSection(&g_csParamer);

		ReleaseSemaphore(g_csBufferFull,1,NULL);
	}	
	return 0;
}

unsigned int __stdcall ConsumerThreadFunc(LPVOID PM)
{
	while(!_bIsEnd)
	{
		WaitForSingleObject(g_csBufferFull,INFINITE);
		EnterCriticalSection(&g_csParamer);
		if (g_csBuffer[g_csConsumer] == END_PRODUCE_NUM)//结束标志   
		{  
			//通知其它消费者有新数据了(结束标志) 
			//其中拿到最后的数据的线程为了不致让后来的线程阻塞，
			//调用ReleaseSemaphore(g_hSemaphoreBufferFull, 1, NULL)通知后面的线程
			ReleaseSemaphore(g_csBufferFull, 1, NULL);
			if(!_bIsEnd)
			{
				SetConsoleColor(FOREGROUND_GREEN);
				printf("  ID号为%d消费者从缓冲池%d里取出%d个产品\n",GetCurrentThreadId(),
					g_csConsumer,g_csBuffer[g_csConsumer]);
				SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			_bIsEnd = true;
			LeaveCriticalSection(&g_csParamer);  
			break;  
		}  
		
		SetConsoleColor(FOREGROUND_GREEN);
		printf("  ID号为%d消费者从缓冲池%d里取出%d个产品\n",GetCurrentThreadId(),
			g_csConsumer,g_csBuffer[g_csConsumer]);
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		g_csConsumer = (g_csConsumer + 1) % BuffSize;
		LeaveCriticalSection(&g_csParamer);

		Sleep(50);
		ReleaseSemaphore(g_csBufferEmpty,1,NULL);		
	}
	SetConsoleColor(FOREGROUND_GREEN);  
	printf("编号为%d的消费者收到通知，线程结束运行\n", GetCurrentThreadId());  
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
	return 0;  
}

int main()
{
	InitializeCriticalSection(&g_csParamer);
	g_csBufferEmpty = CreateSemaphore(NULL,4,4,NULL);
	g_csBufferFull = CreateSemaphore(NULL,0,4,NULL);
	memset(g_csBuffer,0,sizeof(g_csBuffer));
	g_csProdecer = 0;
	g_csConsumer = 0;
	const int ThreadSize = 3;
	HANDLE Thread[ThreadSize];
	_bIsEnd = false;
	
	Thread[0] = (HANDLE)_beginthreadex(NULL,0,ProduceThreadFunc,NULL,0,NULL);
	Thread[1] = (HANDLE)_beginthreadex(NULL,0,ConsumerThreadFunc,NULL,0,NULL);
	Thread[2] = (HANDLE)_beginthreadex(NULL,0,ConsumerThreadFunc,NULL,0,NULL);

	WaitForMultipleObjects(ThreadSize,Thread,TRUE,INFINITE);

	CloseHandle(Thread[0]);
	CloseHandle(Thread[1]);
	CloseHandle(Thread[2]);

	CloseHandle(g_csBufferEmpty);
	CloseHandle(g_csBufferFull);
	DeleteCriticalSection(&g_csParamer);

	return 0;
}