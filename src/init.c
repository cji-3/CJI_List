/**
 * @file CJI_init.c(undone)
 * @author 林東頡
 * @brief 實作
 * @version 1.0.0
 * @date 2026-05-04
 */

#include "../include/CJI_List.h"
#include<stdlib.h>

/**
 * list指標
 */
typedef struct _CJIList_List{
	size_t DataByte;	/**< 數據位寬(位元組) */
	uint32_t ComByte;	/**< 總位元組數 */
	uint32_t UsedByte;	/**< 已使用之位元組數 */
	void* Address;		/**< 地址 */
	float Increment;	/**< 增量(正整數為增量(內部會加上無條件進位)，負數為倍率(內部會加上絕對值)) */
}_CJIList_List;

//---

//創建list
CJIList_List CJIList_CreateList(size_t DataByte){
	_CJIList_List* _return=(_CJIList_List*)malloc(sizeof(_CJIList_List));
	_return->DataByte=DataByte;
	_return->ComByte=DataByte*CJILIST_DEFAULT_INIT_COM_INDEX;
	_return->UsedByte=0;
	_return->Increment=CJILIST_DEFAULT_INCREMENT;
	_return->Address=(void*)malloc(_return->ComByte);

	return (CJIList_List)_return;
}

//(進階)創建list
CJIList_List CJIList_CreateList_Whole(size_t DataByte,float Increment){
	_CJIList_List* _return=(_CJIList_List*)malloc(sizeof(_CJIList_List));
	_return->DataByte=DataByte;
	_return->ComByte=DataByte*CJILIST_DEFAULT_INIT_COM_INDEX;
	_return->UsedByte=0;
	_return->Increment=Increment;
	_return->Address=(void*)malloc(_return->ComByte);

	return (CJIList_List)_return;
}

//新增元素到list(undone待測試)
int CJIList_add(CJIList_List list,void* data){
	if(list->ComByte+list->DataByte >= list->UsedByte){	//不需要擴容
		int i;
		for(i=0;i<list->DataByte;i++) ((char*)list->Address)[list->UsedByte+i]=((char*)data)[i];
		list->UsedByte+=list->DataByte;

		return 0;
	}
	else{	//需要擴容
		size_t _Byte;	//擴容後的總位元組數
		if(list->Increment>0) _Byte=list->ComByte+(size_t)list->Increment*list->DataByte;	//增量
		else if(list->Increment<0) _Byte=list->ComByte/list->DataByte + (size_t)(list->Increment*-1 * (float)(list->ComByte/list->DataByte) );	//倍率
		else _Byte=list->ComByte+8*list->DataByte;	//==0 則預設增量8 index

		realloc(list->Address,_Byte);	//擴容

		if(list->Address!=NULL) return 0;	//成功
		else return -1;	//失敗
	}
}