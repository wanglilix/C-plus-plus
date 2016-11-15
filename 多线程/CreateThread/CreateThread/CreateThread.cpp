#include <iostream>
#include <Windows.h>
#include <process.h>
#include <stdio.h>

using namespace std;

/*void ThreadFunc()
{
	cout<<"My First Thread!"<<endl;
	
}

int main()
{
	DWORD ThreadID;
	cout<<"Create Thread!"<<endl;
	HANDLE handle = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFunc,
		NULL,
		0,
		&ThreadID);
	WaitForSingleObject(handle,INFINITE);
	cout<<"Create Thread Successfull, and ThreadID is: "<<ThreadID<<endl;

	return 0;
}*/

/*
//_beginthreaddex源码
_MCRTIMP uintptr_t __cdecl _beginthreadex(  
	void *security,  
	unsigned stacksize,  
	unsigned (__CLR_OR_STD_CALL * initialcode) (void *),  
	void * argument,  
	unsigned createflag,  
	unsigned *thrdaddr  
	)  
{  
	_ptiddata ptd;          //pointer to per-thread data 见注1   
	uintptr_t thdl;         //thread handle 线程句柄   
	unsigned long err = 0L; //Return from GetLastError()   
	unsigned dummyid;    //dummy returned thread ID 线程ID号   

	// validation section 检查initialcode是否为NULL   
	_VALIDATE_RETURN(initialcode != NULL, EINVAL, 0);  

	//Initialize FlsGetValue function pointer   
	__set_flsgetvalue();  

	//Allocate and initialize a per-thread data structure for the to-be-created thread.   
	//相当于new一个_tiddata结构，并赋给_ptiddata指针。   
	if ( (ptd = (_ptiddata)_calloc_crt(1, sizeof(struct _tiddata))) == NULL )  
		goto error_return;  

	// Initialize the per-thread data   
	//初始化线程的_tiddata块即CRT数据区域 见注2   
	_initptd(ptd, _getptd()->ptlocinfo);  

	//设置_tiddata结构中的其它数据，这样这块_tiddata块就与线程联系在一起了。   
	ptd->_initaddr = (void *) initialcode; //线程函数地址   
	ptd->_initarg = argument;              //传入的线程参数   
	ptd->_thandle = (uintptr_t)(-1);  

#if defined (_M_CEE) || defined (MRTDLL)   
	if(!_getdomain(&(ptd->__initDomain))) //见注3   
	{  
		goto error_return;  
	}  
#endif  // defined (_M_CEE) || defined (MRTDLL)   

	// Make sure non-NULL thrdaddr is passed to CreateThread   
	if ( thrdaddr == NULL )//判断是否需要返回线程ID号   
		thrdaddr = &dummyid;  

	// Create the new thread using the parameters supplied by the caller.   
	//_beginthreadex()最终还是会调用CreateThread()来向系统申请创建线程   
	if ( (thdl = (uintptr_t)CreateThread(  
		(LPSECURITY_ATTRIBUTES)security,  
		stacksize,  
		_threadstartex,  
		(LPVOID)ptd,  
		createflag,  
		(LPDWORD)thrdaddr))  
		== (uintptr_t)0 )  
	{  
		err = GetLastError();  
		goto error_return;  
	}  

	//Good return   
	return(thdl); //线程创建成功,返回新线程的句柄.   

	//Error return   
error_return:  
	//Either ptd is NULL, or it points to the no-longer-necessary block   
	//calloc-ed for the _tiddata struct which should now be freed up.   
	//回收由_calloc_crt()申请的_tiddata块   
	_free_crt(ptd);  
	// Map the error, if necessary.   
	// Note: this routine returns 0 for failure, just like the Win32   
	// API CreateThread, but _beginthread() returns -1 for failure.   
	//校正错误代号(可以调用GetLastError()得到错误代号)   
	if ( err != 0L )  
		_dosmaperr(err);  
	return( (uintptr_t)0 ); //返回值为NULL的效句柄   
} */

/*
//unsigned int (__stdcall *)(void *)
 unsigned int __stdcall ThreadFunc(LPVOID pm)
{
	cout<<"ID为"<<GetCurrentThreadId()<<"的线程输出Hello World!"<<endl;
	return 0;
}

int main()
{
	cout<<"创建多个子线程"<<endl;
	HANDLE ThreadHandle[6];
	for (int i = 0; i < 6; i ++)
	{
		ThreadHandle[i] = (HANDLE)_beginthreadex(NULL,
			0,
			ThreadFunc,
			NULL,
			0,
			NULL);
		WaitForSingleObject(ThreadHandle[i], INFINITE);
	}

	return 0;
}*/

/*volatile long m_count;
unsigned int __stdcall ThreadFunc(LPVOID PM);
const DWORD thread_Num = 100;

unsigned int __stdcall ThreadFunc(LPVOID PM)
{
	Sleep(100);
	InterlockedIncrement((PLONG)&m_count);
	Sleep(50);

	return 0;
}

int main()
{
	int num = 20;
	while (num--)
	{
		m_count = 0;
		HANDLE handle[thread_Num];
		for(int i = 0; i < thread_Num; i ++)
			handle[i] = (HANDLE)_beginthreadex(NULL,0,ThreadFunc,NULL,0,NULL);
		WaitForMultipleObjects(thread_Num,handle,TRUE,INFINITE);
		cout<<"有"<<thread_Num<<"个用户登录，记录结果是："<<m_count<<endl;
	}
	return 0;
}*/


long g_nNum;  
unsigned int __stdcall Fun(void *pPM);  
const int THREAD_NUM = 10;  
//关键段变量声明   
CRITICAL_SECTION g_csThreadCode;
//CRITICAL_SECTION g_csThreadParameter;
HANDLE g_csThreadHandle;
int main()  
{  
	printf("     经典线程同步 关键段\n");  
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");  

	//关键段初始化   
	//InitializeCriticalSection(&g_csThreadParameter);
	//g_csThreadHandle = CreateEvent(NULL,FALSE,FALSE,NULL);//Event
	//g_csThreadHandle = CreateMutex(NULL,FALSE,NULL);
	g_csThreadHandle = CreateSemaphore(NULL,0,1,NULL);
	InitializeCriticalSection(&g_csThreadCode);  

	HANDLE  handle[THREAD_NUM];   
	g_nNum = 0;   
	int i = 0;  
	while (i < THREAD_NUM)   
	{  
		//EnterCriticalSection(&g_csThreadParameter);//进入子线程序号关键区域 
 		//while(g_csThreadParameter.RecursionCount > 1)
 		//	Sleep(0);
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL); 
		WaitForSingleObject(g_csThreadHandle, INFINITE);	//等待触发——加锁
		++i;  
	}  
	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);  

	DeleteCriticalSection(&g_csThreadCode);  
	//DeleteCriticalSection(&g_csThreadParameter); 
	CloseHandle(g_csThreadHandle);
	for(int i = 0; i < THREAD_NUM; i ++)
		CloseHandle(handle[i]);
	return 0;  
}  
unsigned int __stdcall Fun(void *pPM)  
{  
	int nThreadNum = *(int *)pPM;   
	//LeaveCriticalSection(&g_csThreadParameter);//离开子线程序号关键区域 
	//SetEvent(g_csThreadHandle);//触发
	//ReleaseMutex(g_csThreadHandle);//触发——解锁
	ReleaseSemaphore(g_csThreadHandle,1,NULL);

	
	//理解：当子线程1触发主线程i++，并创建另外一个子线程后，相当于另外执行了一次Fun(void* pPM)，
	//这时候前一个子线程可能还未进入子线程互斥区，从而导致了线程号大的子线程输出小全局资源，
	//而线程号小的子线程输出大全局资源，（这里nThreadNum是局部变量，而g_nNum为全局变量）
	//这就意味着后建立的线程可能先访问全局临界资源
	Sleep(50);//some work should to do   

	EnterCriticalSection(&g_csThreadCode);//进入各子线程互斥区域   
	g_nNum++;  
	Sleep(0);//some work should to do   
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum); 
	LeaveCriticalSection(&g_csThreadCode);//离开各子线程互斥区域   
	//将SetEvent放在这里，就相当于等到前面的线程运行完了再运行下一个线程，
	//相当于for循环，多线程失去了并发的优势
	//SetEvent(g_csThreadHandle);
	return 0;  
}

/*
//使用PluseEvent()函数   
#include <stdio.h>   
#include <conio.h>   
#include <process.h>   
#include <windows.h>   
HANDLE  g_hThreadEvent;  
//快线程   
unsigned int __stdcall FastThreadFun(void *pPM)  
{  
	Sleep(10); //用这个来保证各线程调用等待函数的次序有一定的随机性   
	printf("%s 启动\n", (PSTR)pPM);  
	WaitForSingleObject(g_hThreadEvent, INFINITE);  
	printf("%s 等到事件被触发 顺利结束\n", (PSTR)pPM);  
	return 0;  
}  
//慢线程   
unsigned int __stdcall SlowThreadFun(void *pPM)  
{  
	Sleep(100);  
	printf("%s 启动\n", (PSTR)pPM);  
	//当调用PulseEvent()是，慢线程还没等到WaitForSingleObject
	WaitForSingleObject(g_hThreadEvent, INFINITE);
	printf("%s 等到事件被触发 顺利结束\n", (PSTR)pPM);  
	return 0;  
}  
int main()  
{  
	printf("  使用PluseEvent()函数\n");  
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");  

	BOOL bManualReset = TRUE;  
	//创建事件 第二个参数手动置位TRUE，自动置位FALSE   
	g_hThreadEvent = CreateEvent(NULL, bManualReset, FALSE, NULL);  
	if (bManualReset == TRUE)  
		printf("当前使用手动置位事件\n");  
	else  
		printf("当前使用自动置位事件\n");  

	char szFastThreadName[5][30] = {"快线程1000", "快线程1001", "快线程1002", "快线程1003", "快线程1004"};  
	char szSlowThreadName[2][30] = {"慢线程196", "慢线程197"};  

	int i;  
	for (i = 0; i < 5; i++)  
		_beginthreadex(NULL, 0, FastThreadFun, szFastThreadName[i], 0, NULL);  
	for (i = 0; i < 2; i++)  
		_beginthreadex(NULL, 0, SlowThreadFun, szSlowThreadName[i], 0, NULL);  

	Sleep(50); //保证快线程已经全部启动
	//如果sleep的时间段，则在PulseEvent时慢线程还未WaitForSingleObject，如果sleep时间长于慢线程的
	//sleep时间，则慢线程也可以成功触发
	printf("现在主线程触发一个事件脉冲 - PulseEvent()\n");  
	PulseEvent(g_hThreadEvent);//调用PulseEvent()就相当于同时调用下面二句   
	//SetEvent(g_hThreadEvent);   
	//ResetEvent(g_hThreadEvent);   

	Sleep(3000);   
	printf("时间到，主线程结束运行\n");  
	CloseHandle(g_hThreadEvent);  
	return 0;  
}*/

