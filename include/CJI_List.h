/**
 * @file CJI_List.h(undone)
 * @author 林東頡
 * @brief 標頭
 * @version 1.0.0
 * @date 2026-05-04
 */

#ifndef _CJI_LIST_H_
#define _CJI_LIST_H_

#include<stdint.h>

//預設增量(你可以更改此值，或在創建list時使用CJIList_CreateList_Whole()來設定增量)
#define CJILIST_DEFAULT_INCREMENT -1	//-1為最優解(應該)

//設定C函數定義，使使用C++時也是如此
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
 *
 * \version 1.0.0
 */
CJIList_List CJIList_CreateList(size_t ItemByte);

/**
 * \brief (進階)創建list
 * \param ItemByte 您的數據位寬(位元組) 如：sizeof(int)
 * \param Increment 增量(正整數為增量(內部會加上無條件進位)，負數為倍率(內部會加上絕對值))
 * \returns list結構之指標
 *
 * \version 1.0.0
 */
CJIList_List CJIList_CreateList_Whole(size_t ItemByte,float Increment);

//設定C函數定義，使使用C++時也是如此
#ifdef __cplusplus
}
#endif

#endif