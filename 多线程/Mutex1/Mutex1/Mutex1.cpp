#include <stdio.h>
#include <Windows.h>
#include <conio.h>

const char MUTEX_NAME[] = "Mutex_Windows";

int main()
{
	HANDLE hMutex = CreateMutex(NULL,TRUE,(LPCTSTR)MUTEX_NAME);
	printf("互斥量已经创建，现在按任意键触发互斥量\n");  
	getch();  
	exit(0);   
	ReleaseMutex(hMutex);  
	printf("互斥量已经触发\n");  
	CloseHandle(hMutex);  
	return 0;  
}