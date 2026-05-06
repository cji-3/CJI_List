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

	int a=0,i;
	for(i=0;i<100;i++){
		CJIList_Add(list,&a);
		a++;
	}

	for(i=0;i<100;i++){
		printf("%d\n",*(int*)CJIList_read(list,i));
	}

	return 0;
}