/*
//����д�����⣺һ��д�ߣ��������
#include <Windows.h>
#include <process.h>
#include <stdio.h>


CRITICAL_SECTION g_cs,g_csPrintf;
HANDLE g_csWriter,g_csReader;
const int READER_NUM = 5;
int Reader_Counter;

void SetConsoleColor(WORD wAttributes)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if(handle == NULL)
		return;
	SetConsoleTextAttribute(handle,wAttributes);
}
//�����߳��������(��κ�����ʵ��)   
void ReaderPrintf(char *pszFormat, ...)  
{  
	va_list   pArgList;  

	va_start(pArgList, pszFormat);  
	EnterCriticalSection(&g_cs);  
	vfprintf(stdout, pszFormat, pArgList);  
	LeaveCriticalSection(&g_cs);  
	va_end(pArgList);  
}  
//д���߳��������   
void WriterPrintf(char *pszStr)  
{  
	EnterCriticalSection(&g_csPrintf);  
	SetConsoleColor(FOREGROUND_GREEN);  
	printf("%s\n", pszStr);  
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
	LeaveCriticalSection(&g_csPrintf);  
}  

unsigned int __stdcall WriterThreadFunc(LPVOID PM)
{
	WriterPrintf("���ߵȴ�д���еȴ���....\n");
	WaitForSingleObject(g_csWriter,INFINITE);
	ResetEvent(g_csReader);

	WriterPrintf("����д����...\n");
	Sleep(100);
	WriterPrintf("�������д��...\n");

	SetEvent(g_csReader);

	return 0;
}

unsigned int __stdcall ReaderThreadFunc(LPVOID PM)
{
	ReaderPrintf("   ���Ϊ%d�Ķ��߽���ȴ�...\n",GetCurrentThreadId());
	WaitForSingleObject(g_csReader,INFINITE);
	
	//���ڶ�����߸�������
	EnterCriticalSection(&g_cs);
	Reader_Counter++;
	if(Reader_Counter == 1)
		ResetEvent(g_csWriter);
	LeaveCriticalSection(&g_cs);

	ReaderPrintf("   ���Ϊ%d�Ķ��߿�ʼ����...\n",GetCurrentThreadId());

	Sleep(100);

	ReaderPrintf("   ���Ϊ%d�Ķ�����ɶ���...\n",GetCurrentThreadId());

	EnterCriticalSection(&g_cs);
	Reader_Counter--;
	if(Reader_Counter == 0)
		SetEvent(g_csWriter);
	LeaveCriticalSection(&g_cs);

	return 0;
}

int main()
{
	Reader_Counter = 0;
	InitializeCriticalSection(&g_cs);
	InitializeCriticalSection(&g_csPrintf);
	g_csWriter = CreateEvent(NULL,TRUE,TRUE,NULL);
	g_csReader = CreateEvent(NULL,TRUE,FALSE,NULL);

	HANDLE handle[READER_NUM + 1];
	for(int i = 1; i <= 2; i ++)
		handle[i] = (HANDLE)_beginthreadex(NULL,0,ReaderThreadFunc,NULL,0,NULL);
	handle[0] = (HANDLE)_beginthreadex(NULL,0,WriterThreadFunc,NULL,0,NULL);
	Sleep(100);//some work to do
	for(int i = 3; i <= READER_NUM; i ++)
		handle[i] = (HANDLE)_beginthreadex(NULL,0,ReaderThreadFunc,NULL,0,NULL);
	WaitForMultipleObjects(READER_NUM+1,handle,TRUE,INFINITE);

	for(int i = 0; i < READER_NUM + 1; i ++)
		CloseHandle(handle[i]);
	CloseHandle(g_csReader);
	CloseHandle(g_csWriter);

	DeleteCriticalSection(&g_cs);
	DeleteCriticalSection(&g_csPrintf);

	return 0;
}*/


//����˵��
/*
��һ�� InitializeSRWLock

�������ܣ���ʼ����д��

����ԭ�ͣ�VOID InitializeSRWLock(PSRWLOCK SRWLock);

����˵������ʼ����û��ɾ��������SRWLOCK�ĺ�����ϵͳ���Զ�����


�ڶ��� AcquireSRWLockExclusive

�������ܣ�д�����߳�����д��Դ��

����ԭ�ͣ�VOID AcquireSRWLockExclusive(PSRWLOCK SRWLock);


������ ReleaseSRWLockExclusive

�������ܣ�д�����߳�д��Դ��ϣ��ͷŶ���Դ��ռ�á�

����ԭ�ͣ�VOID ReleaseSRWLockExclusive(PSRWLOCK SRWLock);


���ĸ� AcquireSRWLockShared

�������ܣ���ȡ���߳��������Դ��

����ԭ�ͣ�VOID AcquireSRWLockShared(PSRWLOCK SRWLock);


����� ReleaseSRWLockShared

�������ܣ���ȡ���߳̽�����ȡ��Դ���ͷŶ���Դ��ռ�á�

����ԭ�ͣ�VOID ReleaseSRWLockShared(PSRWLOCK SRWLock);


ע��һ���߳̽���������Դһ�Σ����ܶ��������Դ��


*/
//������д������� ��д��SRWLock   
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
const int READER_NUM = 5;  //���߸���   
//�ؼ��κ��¼�   
CRITICAL_SECTION g_cs;  
SRWLOCK          g_srwLock;   
//�����߳��������(��κ�����ʵ��)   
void ReaderPrintf(char *pszFormat, ...)  
{  
	va_list   pArgList;  
	va_start(pArgList, pszFormat);  
	EnterCriticalSection(&g_cs);  
	vfprintf(stdout, pszFormat, pArgList);  
	LeaveCriticalSection(&g_cs);  
	va_end(pArgList);  
}  
//�����̺߳���   
unsigned int __stdcall ReaderThreadFun(PVOID pM)  
{  
	ReaderPrintf("     ���Ϊ%d�Ķ��߽���ȴ���...\n", GetCurrentThreadId());  
	//���������ȡ�ļ�   
	AcquireSRWLockShared(&g_srwLock);  

	//��ȡ�ļ�   
	ReaderPrintf("���Ϊ%d�Ķ��߿�ʼ��ȡ�ļ�...\n", GetCurrentThreadId());  
	Sleep(rand() % 100);  
	ReaderPrintf(" ���Ϊ%d�Ķ��߽�����ȡ�ļ�\n", GetCurrentThreadId());  

	//���߽�����ȡ�ļ�   
	ReleaseSRWLockShared(&g_srwLock);  
	return 0;  
}  
//д���߳��������   
void WriterPrintf(char *pszStr)  
{  
	EnterCriticalSection(&g_cs);  
	SetConsoleColor(FOREGROUND_GREEN);  
	printf("     %s\n", pszStr);  
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
	LeaveCriticalSection(&g_cs);  
}  
//д���̺߳���   
unsigned int __stdcall WriterThreadFun(PVOID pM)  
{  
	WriterPrintf("д���߳̽���ȴ���...");  
	//д������д�ļ�   
	AcquireSRWLockExclusive(&g_srwLock);  

	//д�ļ�   
	WriterPrintf("  д�߿�ʼд�ļ�.....");  
	Sleep(rand() % 100);  
	WriterPrintf("  д�߽���д�ļ�");  

	//���д�߽���д�ļ�   
	ReleaseSRWLockExclusive(&g_srwLock);  
	return 0;  
}  
int main()  
{  
	printf("  ����д������� ��д��SRWLock\n");  
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");  

	//��ʼ����д���͹ؼ���   
	InitializeCriticalSection(&g_cs);  
	InitializeSRWLock(&g_srwLock);  

	HANDLE hThread[READER_NUM + 1];  
	int i;  
	//���������������߳�   
	for (i = 1; i <= 2; i++)  
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);  
	//����д���߳�   
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, WriterThreadFun, NULL, 0, NULL);  
	Sleep(50);  
	//��������������߽��   
	for ( ; i <= READER_NUM; i++)  
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);  
	WaitForMultipleObjects(READER_NUM + 1, hThread, TRUE, INFINITE);  
	for (i = 0; i < READER_NUM + 1; i++)  
		CloseHandle(hThread[i]);  

	//���ٹؼ���   
	DeleteCriticalSection(&g_cs);  
	return 0;  
}  
