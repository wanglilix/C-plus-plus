//1������ 1������ 1������   
//ʹ�ö����¼���һ����ʾ�������գ�һ����ʾ����������   
//��ʹ��һ���ؼ��������ƻ������ķ���   
#include <stdio.h>   
#include <process.h>   
#include <windows.h>   
//���ÿ���̨�����ɫ   
BOOL SetConsoleColor(WORD wAttributes)  
{  
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  
	if (hConsole == INVALID_HANDLE_VALUE)  
		return FALSE;     
	return SetConsoleTextAttribute(hConsole, wAttributes);  
}  
const int END_PRODUCE_NUMBER = 10;   //������Ʒ����   
int g_Buffer;                        //������   
//�¼���ؼ���   
CRITICAL_SECTION g_cs;  
HANDLE g_hEventBufferEmpty, g_hEventBufferFull;  

unsigned int __stdcall ProducerThreadFunc(LPVOID PM)
{
	for(int i = 1; i <= END_PRODUCE_NUMBER; i ++)
	{
		WaitForSingleObject(g_hEventBufferEmpty,INFINITE);

		EnterCriticalSection(&g_cs);
		g_Buffer = i;
		printf("������������������%d����Ʒ\n",i);
		LeaveCriticalSection(&g_cs);

		SetEvent(g_hEventBufferFull);	//�����������в�Ʒ�ź�
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
		printf(" �������ڻ�����ȡ��%d����Ʒ\n",g_Buffer);
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		if(g_Buffer == END_PRODUCE_NUMBER)
			flag = false;
		LeaveCriticalSection(&g_cs);

		SetEvent(g_hEventBufferEmpty);//֪ͨ��������
	}

	return 0;
}

int main()
{
	printf("���������߼����⣺1������ 1������ 1������\n\n\n");
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