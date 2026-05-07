/**
 * @file test.c(undone)
 * @author 林東頡
 * @brief 測試
 * @version 1.0.0
 * @date 2026-05-04
 */

#include<stdio.h>
#include "../include/CJI_List.h"

int main(){
	CLS_List list=CLS_CreateList(sizeof(int));

	//寫入測試
	int a=0,i;
	for(i=0;i<100;i++){
		CLS_Add(list,&a);
		a++;
	}

	//替換測試
	a=1000;
	CLS_Replace(list,50,&a);

	//讀取測試
	for(i=0;i<100;i++){
		printf("%d\n",*(int*)CLS_read(list,i));
	}

	return 0;
}