#include<stdio.h>
#include "../include/CJI_List.h"

int main(){
	CJIList_List list=CJIList_CreateList(sizeof(int));

	printf("%p",list);

	return 0;
}