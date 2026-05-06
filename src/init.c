/**
 * @file CJI_init.c(undone)
 * @author 林東頡
 * @brief 實作
 * @version 1.0.0
 * @date 2026-05-04
 */

#include "../include/CJI_List.h"
#include<stdlib.h>
#include<stdbool.h>

#define _CJILIST_DEBUG_MSG_	//開啟debug訊息(註解掉則關閉)

/*debug*/
	#ifdef _CJILIST_DEBUG_MSG_
		#include<stdio.h>
		#include<string.h>
		#include<stdarg.h>

		//debug訊息類型
		typedef enum{
			COMMON,	/**< 一般訊息(綠色文字) */
			SIGN,	/**< 重點訊息(藍色文字) */
			ERROR	/**< 錯誤訊息(紅色文字) */
		}CJI_Debug;
	#endif

	//debug
	void debug(CJI_Debug mods,const char* str,...){
		#ifdef _CJILIST_DEBUG_MSG_
			va_list a;
			va_start(a,str);

			printf("\x1b[33mCJI_List：");	//黃色

			if(mods==ERROR) printf("\x1b[31m");	//紅色
			else if(mods==SIGN) printf("\x1b[34m");	//藍色
			else printf("\x1b[32m");	//綠色
			vprintf(str,a);	//輸出訊息
			printf("\x1b[0m");	//重置顏色

			if(str[strlen(str)-1]!='\n') printf("\n");	//如果訊息最後沒有換行則補上換行

			va_end(a);
		#endif
	}
/*end debug*/

/**
 * list結構
 */
typedef struct _CJIList_List{
	size_t DataByte;	/**< 數據位寬(位元組) */
	size_t ComByte;		/**< 總位元組數 */
	size_t UsedByte;	/**< 已使用之位元組數 */
	void* Address;		/**< 地址 */
	float Increment;	/**< 增量(正整數為增量(內部會加上無條件進位)，負數為倍率(內部會加上絕對值)) */
}_CJIList_List;

/*內部函式*/

//想增加a個元素是否需擴容
bool _IsExpansion(CJIList_List list,size_t a){
	return list->UsedByte+list->DataByte*a > list->ComByte;
}

//新增元素到list
void _Add(CJIList_List list,void* data){
	size_t i;
	for(i=0;i<list->DataByte;i++) ((char*)list->Address)[list->UsedByte+i]=((char*)data)[i];	//(char*)作為"字節(位元組)"使用
}

/*end 內部函式*/

//---

/*實現*/

//創建list
CJIList_List CJIList_CreateList(size_t DataByte){
	_CJIList_List* _return=(_CJIList_List*)malloc(sizeof(_CJIList_List));
	_return->DataByte=DataByte;
	_return->ComByte=DataByte*CJILIST_DEFAULT_INIT_COM_INDEX;
	_return->UsedByte=0;
	_return->Increment=CJILIST_DEFAULT_INCREMENT;
	_return->Address=(void*)malloc(_return->ComByte);

	debug(COMMON,"CreateList success. list:%p",_return);
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

	debug(COMMON,"CreateList_Whole success. list:%p",_return);
	return (CJIList_List)_return;
}

//新增元素到list(undone)
int CJIList_Add(CJIList_List list,void* data){
	if(!_IsExpansion(list,1)){	//不需要擴容
		_Add(list,data);
		list->UsedByte+=list->DataByte;

		debug(COMMON,"Add success. list:%p, UsedByte:%zu/%zu",list,list->UsedByte,list->ComByte);
		return 0;
	}
	else{	//需要擴容
		size_t _Byte;	//擴容後的總位元組數
		if(list->Increment>0) _Byte=list->ComByte + (size_t)list->Increment*list->DataByte;	//增量
		else if(list->Increment<0) _Byte=list->ComByte + (size_t)(list->Increment*-1 * (float)(list->ComByte) );	//倍率
		else _Byte=list->ComByte+8*list->DataByte;	//==0 則預設增量8 index

		void* rp=realloc(list->Address,_Byte);	//擴容

		if(rp!=NULL){	//成功
			list->Address=rp;
			list->ComByte=_Byte;
			_Add(list,data);
			list->UsedByte+=list->DataByte;

			debug(SIGN,"Add success and occur expansion. list:%p, OldComByte:%zu, NewUsedByte:%zu/%zu",list,list->ComByte,list->UsedByte,_Byte);

			return 0;
		}
		else return -1;	//失敗
	}
}

//在指定索引位置新增(插入)元素到list，後面的元素會自動往後(undone)
int CJIList_AddIndex(CJIList_List list,size_t index,void* data){

}

//替換某元素(undone)
void* CJIList_read(CJIList_List list,size_t index){

}

//讀取list中的元素
void* CJIList_read(CJIList_List list,size_t index){
	if(index*list->DataByte < list->ComByte) return list->Address + index*list->DataByte;
	else return NULL;
}

/*end 實現*/