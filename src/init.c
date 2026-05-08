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

#define _CLS_DEBUG_MSG_	//開啟debug訊息(註解掉則關閉)
#define _CLS_DEBUG_MSG_COMMON_OFF	//關閉一般訊息
//#define _CLS_DEBUG_MSG_SIGN_OFF	//關閉重點訊息

/*debug*/
	#ifdef _CLS_DEBUG_MSG_
		#include<stdio.h>
		#include<string.h>
		#include<stdarg.h>
	#endif

	//debug訊息類型
	typedef enum{
		COMMON,	/**< 一般訊息(綠色文字) */
		SIGN,	/**< 重點訊息(藍色文字) */
		ERROR	/**< 錯誤訊息(紅色文字) */
	}CLS_Debug;

	//debug
	void debug(CLS_Debug mods,const char* str,...){
		//如果debug訊息被關閉則不輸出
		#ifndef _CLS_DEBUG_MSG_
			return;
		#endif

		//如果訊息類型被關閉則不輸出
		#ifdef _CLS_DEBUG_MSG_COMMON_OFF
			if(mods==COMMON) return;
		#endif
		#ifdef _CLS_DEBUG_MSG_SIGN_OFF
			if(mods==SIGN) return;
		#endif

		va_list a;
		va_start(a,str);

		printf("\x1b[33mCLS：");	//黃色

		if(mods==ERROR) printf("\x1b[31m");	//紅色
		else if(mods==SIGN) printf("\x1b[34m");	//藍色
		else printf("\x1b[32m");	//綠色
		vprintf(str,a);	//輸出訊息
		printf("\x1b[0m");	//重置顏色

		if(str[strlen(str)-1]!='\n') printf("\n");	//如果訊息最後沒有換行則補上換行

		va_end(a);
	}
/*end debug*/

/**
 * list結構
 */
typedef struct _CLS_List{
	size_t DataByte;	/**< 數據位寬(位元組) */
	size_t ComByte;		/**< 總位元組數 */
	size_t UsedByte;	/**< 已使用之位元組數 */
	void* Address;		/**< 地址 */
	float Increment;	/**< 增量(正整數為增量(內部會加上無條件進位)，負數為倍率(內部會加上絕對值)) */
}_CLS_List;

/*內部函式*/

//想增加a個元素是否需擴容
bool _IsExpansion(CLS_List list,size_t a){
	return list->UsedByte+list->DataByte*a > list->ComByte;
}

//新增元素到list
void _Write(CLS_List list,size_t index,void* data){
	size_t i;
	for(i=0;i<list->DataByte;i++) ((char*)list->Address)[index*list->DataByte + i]=((char*)data)[i];	//(char*)作為"字節(位元組)"使用
}

//list的長度(項)
size_t _ListLen(CLS_List list){
	return list->UsedByte/list->DataByte;
}

/*end 內部函式*/

//---

/*實現*/

//創建list
CLS_List CLS_CreateList(size_t DataByte){
	_CLS_List* _return=(_CLS_List*)malloc(sizeof(_CLS_List));
	_return->DataByte=DataByte;
	_return->ComByte=DataByte*CLS_DEFAULT_INIT_COM_INDEX;
	_return->UsedByte=0;
	_return->Increment=CLS_DEFAULT_INCREMENT;
	_return->Address=(void*)malloc(_return->ComByte);

	debug(COMMON,"CreateList success. list:%p",_return);
	return (CLS_List)_return;
}

//(進階)創建list
CLS_List CLS_CreateList_Whole(size_t DataByte,float Increment){
	_CLS_List* _return=(_CLS_List*)malloc(sizeof(_CLS_List));
	_return->DataByte=DataByte;
	_return->ComByte=DataByte*CLS_DEFAULT_INIT_COM_INDEX;
	_return->UsedByte=0;
	_return->Increment=Increment;
	_return->Address=(void*)malloc(_return->ComByte);

	debug(COMMON,"CreateList_Whole success. list:%p",_return);
	return (CLS_List)_return;
}

//新增元素到list(undone)
int CLS_Add(CLS_List list,void* data){
	if(!_IsExpansion(list,1)){	//不需要擴容
		_Write(list,_ListLen(list),data);
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
			_Write(list,_ListLen(list),data);
			list->UsedByte+=list->DataByte;

			debug(SIGN,"Add success and occur expansion. list:%p, OldComByte:%zu, NewUsedByte:%zu/%zu",list,list->ComByte,list->UsedByte,_Byte);

			return 0;
		}
		else return -1;	//失敗
	}
}

//在指定索引位置新增(插入)元素到list，後面的元素會自動往後(undone)
int CLS_AddIndex(CLS_List list,size_t index,void* data){

	size_t len = _ListLen(list);

	//index check
	if(index > len){
		debug(ERROR,"AddIndex error. AddIndex out of bounds. list:%p, index:%zu, len:%zu",list,index,len);
		return -1;
	}

	if(!_IsExpansion(list,1)){     // 不需要擴容
		for(size_t i=len; i>index; i--){
			_Write(list, i, (char*)list->Address + (i-1)*list->DataByte);		//有點沒效率，先這樣
		}
		_Write(list, index, data);
		list->UsedByte += list->DataByte;
		
		debug(COMMON,"AddIndex success. list:%p, index:%zu, UsedByte:%zu/%zu",list,index,list->UsedByte,list->ComByte);
		return 0;
	}
	else{	//需要擴容
		size_t _Byte;	//擴容後的總位元組數
		if(list->Increment>0) _Byte=list->ComByte + (size_t)list->Increment*list->DataByte;	//增量
		else if(list->Increment<0) _Byte=list->ComByte + (size_t)(list->Increment*-1 * (float)(list->ComByte) );	//倍率
		else _Byte=list->ComByte+8*list->DataByte;	//==0 則預設增量8 index

		for(size_t i=len; i>index; i--){
		_Write(list, i, (char*)list->Address + (i-1)*list->DataByte);	//同上
	}
		void* rp = realloc(list->Address,_Byte);
		
		if(rp !=NULL){	//成功
			list->Address=rp;
			list->ComByte=_Byte;
			_Write(list, index, data);
			list->UsedByte += list->DataByte;

			debug(SIGN,"AddIndex success and occur expansion. list:%p, UsedByte:%zu/%zu",list,list->UsedByte,list->ComByte);

			return 0;
		}
		else return -1;	
	}
	
}

//替換某元素(undone)
void CLS_Replace(CLS_List list,size_t index,void* data){
	_Write(list,index,data);
	debug(COMMON,"Replace success. list:%p, index:%zu",list,index);
}

//讀取list中的元素
void* CLS_read(CLS_List list,size_t index){
	if(index*list->DataByte < list->UsedByte){
		debug(COMMON,"Read success. list:%p, index:%zu",list,index);
		return list->Address + index*list->DataByte;
	}
	else{
		debug(ERROR,"Read error. Read out of bounds. list:%p, index:%zu, UsedIndex:%zu",list,index,list->UsedByte/list->DataByte);
		return NULL;
	}
}

//刪除list中的元素，後面的元素會自動往前(undone)
int CLS_Delete(CLS_List list,size_t index){
	size_t len = _ListLen(list);

	if(index < len){
		for(size_t i=index; i<len-1; i++){
			_Write(list, i, (char*)list->Address + (i+1)*list->DataByte);	//同上
		}
		list->UsedByte -= list->DataByte;

		debug(COMMON,"Delete success. list:%p, index:%zu, UsedByte:%zu/%zu",list,index,list->UsedByte,list->ComByte);
		return 0;
	}
	else{
		debug(ERROR,"Delete error. Delete out of bounds. list:%p, index:%zu, len:%zu",list,index,len);
		return -1;
	}
}

/*end 實現*/
