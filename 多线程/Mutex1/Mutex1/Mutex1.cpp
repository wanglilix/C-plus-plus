#include <stdio.h>
#include <Windows.h>
#include <conio.h>

const char MUTEX_NAME[] = "Mutex_Windows";

int main()
{
	HANDLE hMutex = CreateMutex(NULL,TRUE,(LPCTSTR)MUTEX_NAME);
	printf("�������Ѿ����������ڰ����������������\n");  
	getch();  
	exit(0);   
	ReleaseMutex(hMutex);  
	printf("�������Ѿ�����\n");  
	CloseHandle(hMutex);  
	return 0;  
}