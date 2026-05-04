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
	size_t ItemByte;	/**< 數據位寬(位元組) */
	uint32_t ComByte;	/**< 總位元組數 */
	uint32_t UsedByte;	/**< 已使用之位元組數 */
	void* Address;		/**< 地址 */
	float Increment;	/**< 增量(正整數為增量(內部會加上無條件進位)，負數為倍率(內部會加上絕對值)) */
}_CJIList_List;

//創建list
CJIList_List CJIList_CreateList(size_t ItemByte){
	_CJIList_List* _return=(_CJIList_List*)malloc(sizeof(_CJIList_List));
	_return->ItemByte=ItemByte;
	_return->ComByte=ItemByte*1;
	_return->UsedByte=0;
	_return->Increment=CJILIST_DEFAULT_INCREMENT;
	_return->Address=(void*)malloc(ItemByte*1);

	return (CJIList_List)_return;
}

//(進階)創建list
CJIList_List CJIList_CreateList_Whole(size_t ItemByte,float Increment){
	_CJIList_List* _return=(_CJIList_List*)malloc(sizeof(_CJIList_List));
	_return->ItemByte=ItemByte;
	_return->ComByte=ItemByte*1;
	_return->UsedByte=0;
	_return->Increment=Increment;
	_return->Address=(void*)malloc(ItemByte*1);

	return (CJIList_List)_return;
}