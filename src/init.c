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
}_CJIList_List;

CJIList_List CJIList_CreateList(size_t ItemByte){
	_CJIList_List* _return=(_CJIList_List*)malloc(sizeof(_CJIList_List));
	_return->ItemByte=ItemByte;
	_return->ComByte=ItemByte*1;
	_return->UsedByte=0;
	_return->Address=(void*)malloc(ItemByte*1);

	return (CJIList_List)_return;
}