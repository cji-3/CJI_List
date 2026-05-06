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
	CJIList_List list=CJIList_CreateList(sizeof(int));

	//寫入測試
	int a=0,i;
	for(i=0;i<100;i++){
		CJIList_Add(list,&a);
		a++;
	}

	//替換測試
	a=1000;
	CJIList_Replace(list,50,&a);

	//讀取測試
	for(i=0;i<100;i++){
		printf("%d\n",*(int*)CJIList_read(list,i));
	}

	return 0;
}