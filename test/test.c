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

	int a=20;
	CJIList_Add(list,&a);
	a=10;
	CJIList_Add(list,&a);
	a=100;
	CJIList_Add(list,&a);

	printf("%d\n",*(int*)CJIList_read(list,0));
	printf("%d\n",*(int*)CJIList_read(list,1));
	printf("%d\n",*(int*)CJIList_read(list,2));

	return 0;
}