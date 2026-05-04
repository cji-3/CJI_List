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
	int a=10;
	CJIList_add(list,&a);
	printf("%p",list);

	return 0;
}