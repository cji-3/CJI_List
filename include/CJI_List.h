#ifndef _CJI_LIST_H_
#define _CJI_LIST_H_

#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * list指標(CJIList_List)
 */
typedef struct _CJIList_List* CJIList_List;

/**
 * \brief 創建list
 * \param ItemByte 您的數據位寬(位元組) 如：sizeof(int)
 * \returns list結構之指標
 */
CJIList_List CJIList_CreateList(size_t ItemByte);

#ifdef __cplusplus
}
#endif

#endif