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
//_beginthreaddexԴ��
_MCRTIMP uintptr_t __cdecl _beginthreadex(  
	void *security,  
	unsigned stacksize,  
	unsigned (__CLR_OR_STD_CALL * initialcode) (void *),  
	void * argument,  
	unsigned createflag,  
	unsigned *thrdaddr  
	)  
{  
	_ptiddata ptd;          //pointer to per-thread data ��ע1   
	uintptr_t thdl;         //thread handle �߳̾��   
	unsigned long err = 0L; //Return from GetLastError()   
	unsigned dummyid;    //dummy returned thread ID �߳�ID��   

	// validation section ���initialcode�Ƿ�ΪNULL   
	_VALIDATE_RETURN(initialcode != NULL, EINVAL, 0);  

	//Initialize FlsGetValue function pointer   
	__set_flsgetvalue();  

	//Allocate and initialize a per-thread data structure for the to-be-created thread.   
	//�൱��newһ��_tiddata�ṹ��������_ptiddataָ�롣   
	if ( (ptd = (_ptiddata)_calloc_crt(1, sizeof(struct _tiddata))) == NULL )  
		goto error_return;  

	// Initialize the per-thread data   
	//��ʼ���̵߳�_tiddata�鼴CRT�������� ��ע2   
	_initptd(ptd, _getptd()->ptlocinfo);  

	//����_tiddata�ṹ�е��������ݣ��������_tiddata������߳���ϵ��һ���ˡ�   
	ptd->_initaddr = (void *) initialcode; //�̺߳�����ַ   
	ptd->_initarg = argument;              //������̲߳���   
	ptd->_thandle = (uintptr_t)(-1);  

#if defined (_M_CEE) || defined (MRTDLL)   
	if(!_getdomain(&(ptd->__initDomain))) //��ע3   
	{  
		goto error_return;  
	}  
#endif  // defined (_M_CEE) || defined (MRTDLL)   

	// Make sure non-NULL thrdaddr is passed to CreateThread   
	if ( thrdaddr == NULL )//�ж��Ƿ���Ҫ�����߳�ID��   
		thrdaddr = &dummyid;  

	// Create the new thread using the parameters supplied by the caller.   
	//_beginthreadex()���ջ��ǻ����CreateThread()����ϵͳ���봴���߳�   
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
	return(thdl); //�̴߳����ɹ�,�������̵߳ľ��.   

	//Error return   
error_return:  
	//Either ptd is NULL, or it points to the no-longer-necessary block   
	//calloc-ed for the _tiddata struct which should now be freed up.   
	//������_calloc_crt()�����_tiddata��   
	_free_crt(ptd);  
	// Map the error, if necessary.   
	// Note: this routine returns 0 for failure, just like the Win32   
	// API CreateThread, but _beginthread() returns -1 for failure.   
	//У���������(���Ե���GetLastError()�õ��������)   
	if ( err != 0L )  
		_dosmaperr(err);  
	return( (uintptr_t)0 ); //����ֵΪNULL��Ч���   
} */

/*
//unsigned int (__stdcall *)(void *)
 unsigned int __stdcall ThreadFunc(LPVOID pm)
{
	cout<<"IDΪ"<<GetCurrentThreadId()<<"���߳����Hello World!"<<endl;
	return 0;
}

int main()
{
	cout<<"����������߳�"<<endl;
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
		cout<<"��"<<thread_Num<<"���û���¼����¼����ǣ�"<<m_count<<endl;
	}
	return 0;
}*/


long g_nNum;  
unsigned int __stdcall Fun(void *pPM);  
const int THREAD_NUM = 10;  
//�ؼ��α�������   
CRITICAL_SECTION g_csThreadCode;
//CRITICAL_SECTION g_csThreadParameter;
HANDLE g_csThreadHandle;
int main()  
{  
	printf("     �����߳�ͬ�� �ؼ���\n");  
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");  

	//�ؼ��γ�ʼ��   
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
		//EnterCriticalSection(&g_csThreadParameter);//�������߳���Źؼ����� 
 		//while(g_csThreadParameter.RecursionCount > 1)
 		//	Sleep(0);
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Fun, &i, 0, NULL); 
		WaitForSingleObject(g_csThreadHandle, INFINITE);	//�ȴ�������������
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
	//LeaveCriticalSection(&g_csThreadParameter);//�뿪���߳���Źؼ����� 
	//SetEvent(g_csThreadHandle);//����
	//ReleaseMutex(g_csThreadHandle);//������������
	ReleaseSemaphore(g_csThreadHandle,1,NULL);

	
	//��⣺�����߳�1�������߳�i++������������һ�����̺߳��൱������ִ����һ��Fun(void* pPM)��
	//��ʱ��ǰһ�����߳̿��ܻ�δ�������̻߳��������Ӷ��������̺߳Ŵ�����߳����Сȫ����Դ��
	//���̺߳�С�����߳������ȫ����Դ��������nThreadNum�Ǿֲ���������g_nNumΪȫ�ֱ�����
	//�����ζ�ź������߳̿����ȷ���ȫ���ٽ���Դ
	Sleep(50);//some work should to do   

	EnterCriticalSection(&g_csThreadCode);//��������̻߳�������   
	g_nNum++;  
	Sleep(0);//some work should to do   
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum); 
	LeaveCriticalSection(&g_csThreadCode);//�뿪�����̻߳�������   
	//��SetEvent����������൱�ڵȵ�ǰ����߳�����������������һ���̣߳�
	//�൱��forѭ�������߳�ʧȥ�˲���������
	//SetEvent(g_csThreadHandle);
	return 0;  
}

/*
//ʹ��PluseEvent()����   
#include <stdio.h>   
#include <conio.h>   
#include <process.h>   
#include <windows.h>   
HANDLE  g_hThreadEvent;  
//���߳�   
unsigned int __stdcall FastThreadFun(void *pPM)  
{  
	Sleep(10); //���������֤���̵߳��õȴ������Ĵ�����һ���������   
	printf("%s ����\n", (PSTR)pPM);  
	WaitForSingleObject(g_hThreadEvent, INFINITE);  
	printf("%s �ȵ��¼������� ˳������\n", (PSTR)pPM);  
	return 0;  
}  
//���߳�   
unsigned int __stdcall SlowThreadFun(void *pPM)  
{  
	Sleep(100);  
	printf("%s ����\n", (PSTR)pPM);  
	//������PulseEvent()�ǣ����̻߳�û�ȵ�WaitForSingleObject
	WaitForSingleObject(g_hThreadEvent, INFINITE);
	printf("%s �ȵ��¼������� ˳������\n", (PSTR)pPM);  
	return 0;  
}  
int main()  
{  
	printf("  ʹ��PluseEvent()����\n");  
	printf(" -- by MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");  

	BOOL bManualReset = TRUE;  
	//�����¼� �ڶ��������ֶ���λTRUE���Զ���λFALSE   
	g_hThreadEvent = CreateEvent(NULL, bManualReset, FALSE, NULL);  
	if (bManualReset == TRUE)  
		printf("��ǰʹ���ֶ���λ�¼�\n");  
	else  
		printf("��ǰʹ���Զ���λ�¼�\n");  

	char szFastThreadName[5][30] = {"���߳�1000", "���߳�1001", "���߳�1002", "���߳�1003", "���߳�1004"};  
	char szSlowThreadName[2][30] = {"���߳�196", "���߳�197"};  

	int i;  
	for (i = 0; i < 5; i++)  
		_beginthreadex(NULL, 0, FastThreadFun, szFastThreadName[i], 0, NULL);  
	for (i = 0; i < 2; i++)  
		_beginthreadex(NULL, 0, SlowThreadFun, szSlowThreadName[i], 0, NULL);  

	Sleep(50); //��֤���߳��Ѿ�ȫ������
	//���sleep��ʱ��Σ�����PulseEventʱ���̻߳�δWaitForSingleObject�����sleepʱ�䳤�����̵߳�
	//sleepʱ�䣬�����߳�Ҳ���Գɹ�����
	printf("�������̴߳���һ���¼����� - PulseEvent()\n");  
	PulseEvent(g_hThreadEvent);//����PulseEvent()���൱��ͬʱ�����������   
	//SetEvent(g_hThreadEvent);   
	//ResetEvent(g_hThreadEvent);   

	Sleep(3000);   
	printf("ʱ�䵽�����߳̽�������\n");  
	CloseHandle(g_hThreadEvent);  
	return 0;  
}*/

