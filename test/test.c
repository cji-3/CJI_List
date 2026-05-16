/**
 * @file test.c(undone)
 * @author 林東頡
 * @brief 測試
 * @version 1.0.0
 * @date 2026-05-04
 */

#include<stdio.h>
#include<stdlib.h>
#include "../include/CLS.h"

int main(){
	CLS_List list=CLS_Create(sizeof(int));

	//寫入測試
	int a=0,i;
	for(i=0;i<100;i++){
		CLS_Psh(list,&a);
		a++;
	}

	//替換測試
	a=1000;
	CLS_Set(list,80,&a);

	//插入測試
	a=250;
	CLS_Ins(list,90,&a);//在90插入

	//刪除測試
	CLS_Del(list,51);

	//讀取測試
	for(i=0;i<100;i++){
		printf("%d\n",*(int*)CLS_Get(list,i));
	}
	printf("END=%d\n",*(int*)CLS_Pop(list));

	//銷毀
	CLS_Free(list);
	
	
	#ifdef _WIN32
		system("pause");
	#endif

	return 0;
}