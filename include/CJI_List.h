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

//預設增量(你可以更改此值(建議在你的.c中修改而在非這裡修改)，或在創建list時使用CJIList_CreateList_Whole()來為list個別設定增量)
#define CJILIST_DEFAULT_INCREMENT (float)(-2)	//-2為最優解(應該)

//預設的list初始總索引數(你可以更改此值(建議在你的.c中修改而在非這裡修改)
#define CJILIST_DEFAULT_INIT_COM_INDEX 8	//8

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
 * \param DataByte 您的數據位寬(位元組) 如：sizeof(int)
 * \returns list結構之指標
 *
 * \version 1.0.0
 */
CJIList_List CJIList_CreateList(size_t DataByte);

/**
 * \brief (進階)創建list
 * \param DataByte 您的數據位寬(位元組) 如：sizeof(int)
 * \param Increment 增量(正整數為增量(內部會加上無條件捨去)，負數為倍率(內部會加上絕對值))
 * \returns list結構之指標，失敗(NULL)
 *
 * \version 1.0.0
 */
CJIList_List CJIList_CreateList_Whole(size_t DataByte,float Increment);

/**
 * \brief 新增元素到list
 * \param list list結構之指標
 * \param data 要新增的數據指標
 * \returns 成功?
 *
 * \version 1.0.0
 */
int CJIList_Add(CJIList_List list,void* data);

/**
 * \brief 在指定索引位置新增(插入)元素到list，後面的元素會自動往後
 * \param list list結構之指標
 * \param index 索引
 * \param data 要新增的數據指標
 * \returns 成功?
 *
 * \version 1.0.0
 */
int CJIList_AddIndex(CJIList_List list,size_t index,void* data);

/**
 * \brief 替換某元素
 * \param list list結構之指標
 * \param index 索引
 * \param data 要換成的數據指標
 *
 * \version 1.0.0
 */
void CJIList_Replace(CJIList_List list,size_t index,void* data);

/**
 * \brief 讀取list中的元素
 * \param list list結構之指標
 * \param index 索引
 * \returns 成功(元素指標)，失敗(NULL)
 *
 * \version 1.0.0
 */
void* CJIList_read(CJIList_List list,size_t index);

//設定C函數定義，使使用C++時也是如此
#ifdef __cplusplus
}
#endif

#endif