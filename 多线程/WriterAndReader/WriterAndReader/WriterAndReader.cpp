/*
//读者写者问题：一个写者，多个读者
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
//读者线程输出函数(变参函数的实现)   
void ReaderPrintf(char *pszFormat, ...)  
{  
	va_list   pArgList;  

	va_start(pArgList, pszFormat);  
	EnterCriticalSection(&g_cs);  
	vfprintf(stdout, pszFormat, pArgList);  
	LeaveCriticalSection(&g_cs);  
	va_end(pArgList);  
}  
//写者线程输出函数   
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
	WriterPrintf("作者等待写作中等待中....\n");
	WaitForSingleObject(g_csWriter,INFINITE);
	ResetEvent(g_csReader);

	WriterPrintf("作者写作中...\n");
	Sleep(100);
	WriterPrintf("作者完成写作...\n");

	SetEvent(g_csReader);

	return 0;
}

unsigned int __stdcall ReaderThreadFunc(LPVOID PM)
{
	ReaderPrintf("   编号为%d的读者进入等待...\n",GetCurrentThreadId());
	WaitForSingleObject(g_csReader,INFINITE);
	
	//正在读书读者个数增加
	EnterCriticalSection(&g_cs);
	Reader_Counter++;
	if(Reader_Counter == 1)
		ResetEvent(g_csWriter);
	LeaveCriticalSection(&g_cs);

	ReaderPrintf("   编号为%d的读者开始读书...\n",GetCurrentThreadId());

	Sleep(100);

	ReaderPrintf("   编号为%d的读者完成读书...\n",GetCurrentThreadId());

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


//函数说明
/*
第一个 InitializeSRWLock

函数功能：初始化读写锁

函数原型：VOID InitializeSRWLock(PSRWLOCK SRWLock);

函数说明：初始化（没有删除或销毁SRWLOCK的函数，系统会自动清理）


第二个 AcquireSRWLockExclusive

函数功能：写入者线程申请写资源。

函数原型：VOID AcquireSRWLockExclusive(PSRWLOCK SRWLock);


第三个 ReleaseSRWLockExclusive

函数功能：写入者线程写资源完毕，释放对资源的占用。

函数原型：VOID ReleaseSRWLockExclusive(PSRWLOCK SRWLock);


第四个 AcquireSRWLockShared

函数功能：读取者线程申请读资源。

函数原型：VOID AcquireSRWLockShared(PSRWLOCK SRWLock);


第五个 ReleaseSRWLockShared

函数功能：读取者线程结束读取资源，释放对资源的占用。

函数原型：VOID ReleaseSRWLockShared(PSRWLOCK SRWLock);


注意一个线程仅能锁定资源一次，不能多次锁定资源。


*/
//读者与写者问题继 读写锁SRWLock   
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
const int READER_NUM = 5;  //读者个数   
//关键段和事件   
CRITICAL_SECTION g_cs;  
SRWLOCK          g_srwLock;   
//读者线程输出函数(变参函数的实现)   
void ReaderPrintf(char *pszFormat, ...)  
{  
	va_list   pArgList;  
	va_start(pArgList, pszFormat);  
	EnterCriticalSection(&g_cs);  
	vfprintf(stdout, pszFormat, pArgList);  
	LeaveCriticalSection(&g_cs);  
	va_end(pArgList);  
}  
//读者线程函数   
unsigned int __stdcall ReaderThreadFun(PVOID pM)  
{  
	ReaderPrintf("     编号为%d的读者进入等待中...\n", GetCurrentThreadId());  
	//读者申请读取文件   
	AcquireSRWLockShared(&g_srwLock);  

	//读取文件   
	ReaderPrintf("编号为%d的读者开始读取文件...\n", GetCurrentThreadId());  
	Sleep(rand() % 100);  
	ReaderPrintf(" 编号为%d的读者结束读取文件\n", GetCurrentThreadId());  

	//读者结束读取文件   
	ReleaseSRWLockShared(&g_srwLock);  
	return 0;  
}  
//写者线程输出函数   
void WriterPrintf(char *pszStr)  
{  
	EnterCriticalSection(&g_cs);  
	SetConsoleColor(FOREGROUND_GREEN);  
	printf("     %s\n", pszStr);  
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
	LeaveCriticalSection(&g_cs);  
}  
//写者线程函数   
unsigned int __stdcall WriterThreadFun(PVOID pM)  
{  
	WriterPrintf("写者线程进入等待中...");  
	//写者申请写文件   
	AcquireSRWLockExclusive(&g_srwLock);  

	//写文件   
	WriterPrintf("  写者开始写文件.....");  
	Sleep(rand() % 100);  
	WriterPrintf("  写者结束写文件");  

	//标记写者结束写文件   
	ReleaseSRWLockExclusive(&g_srwLock);  
	return 0;  
}  
int main()  
{  
	printf("  读者写者问题继 读写锁SRWLock\n");  
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");  

	//初始化读写锁和关键段   
	InitializeCriticalSection(&g_cs);  
	InitializeSRWLock(&g_srwLock);  

	HANDLE hThread[READER_NUM + 1];  
	int i;  
	//先启动二个读者线程   
	for (i = 1; i <= 2; i++)  
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);  
	//启动写者线程   
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, WriterThreadFun, NULL, 0, NULL);  
	Sleep(50);  
	//最后启动其它读者结程   
	for ( ; i <= READER_NUM; i++)  
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ReaderThreadFun, NULL, 0, NULL);  
	WaitForMultipleObjects(READER_NUM + 1, hThread, TRUE, INFINITE);  
	for (i = 0; i < READER_NUM + 1; i++)  
		CloseHandle(hThread[i]);  

	//销毁关键段   
	DeleteCriticalSection(&g_cs);  
	return 0;  
}  
