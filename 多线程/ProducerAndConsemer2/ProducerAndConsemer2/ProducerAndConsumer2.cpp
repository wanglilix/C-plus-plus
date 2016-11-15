//�����������������⣺һ�������ߣ�����������

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

//���������һ��������Ҫ�������ź����Ϳ���ʹ�����ߺ������߷��ʻ�����������ɳ�ͻ��
//���ﻥ���������û��������������ɫ����
CRITICAL_SECTION g_csParamer;
const int END_PRODUCE_NUM = 10;
const int BuffSize = 4;
int g_csProdecer,g_csConsumer;
int g_csBuffer[BuffSize];
bool _bIsEnd;//��������ɱ�־

unsigned int __stdcall ProduceThreadFunc(LPVOID PM)
{
	for(int i = 1; i <= 10; i ++)
	{
		WaitForSingleObject(g_csBufferEmpty,INFINITE);

		EnterCriticalSection(&g_csParamer);
		g_csBuffer[g_csProdecer] = i;
		printf("�������򻺳��%d��Ͷ����%d����Ʒ\n",g_csProdecer,i);
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
		if (g_csBuffer[g_csConsumer] == END_PRODUCE_NUM)//������־   
		{  
			//֪ͨ��������������������(������־) 
			//�����õ��������ݵ��߳�Ϊ�˲����ú������߳�������
			//����ReleaseSemaphore(g_hSemaphoreBufferFull, 1, NULL)֪ͨ������߳�
			ReleaseSemaphore(g_csBufferFull, 1, NULL);
			if(!_bIsEnd)
			{
				SetConsoleColor(FOREGROUND_GREEN);
				printf("  ID��Ϊ%d�����ߴӻ����%d��ȡ��%d����Ʒ\n",GetCurrentThreadId(),
					g_csConsumer,g_csBuffer[g_csConsumer]);
				SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			_bIsEnd = true;
			LeaveCriticalSection(&g_csParamer);  
			break;  
		}  
		
		SetConsoleColor(FOREGROUND_GREEN);
		printf("  ID��Ϊ%d�����ߴӻ����%d��ȡ��%d����Ʒ\n",GetCurrentThreadId(),
			g_csConsumer,g_csBuffer[g_csConsumer]);
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		g_csConsumer = (g_csConsumer + 1) % BuffSize;
		LeaveCriticalSection(&g_csParamer);

		Sleep(50);
		ReleaseSemaphore(g_csBufferEmpty,1,NULL);		
	}
	SetConsoleColor(FOREGROUND_GREEN);  
	printf("���Ϊ%d���������յ�֪ͨ���߳̽�������\n", GetCurrentThreadId());  
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