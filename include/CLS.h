/**
 * @file CLS.h(undone)
 * @author 林東頡
 * @brief 標頭
 * @version 1.0.0
 * @date 2026-05-04
 */

#ifndef _CLS_H_
#define _CLS_H_

#include<stdint.h>
#include<stddef.h>

//預設增量(你可以更改此值(建議在你的.c中修改而在非這裡修改)，或在創建list時使用CLS_CreateList_Whole()來為list個別設定增量)
#define CLS_DEFAULT_INCREMENT (float)(-2)	//-2為最優解(應該)

//預設的list初始總索引數(你可以更改此值(建議在你的.c中修改而在非這裡修改)
#define CLS_DEFAULT_INIT_COM_INDEX 8	//8

//設定C函數定義，使使用C++時也是如此
#ifdef __cplusplus
extern "C" {
#endif

/**
 * list指標(CLS_List)
 */
typedef struct _CLS_List CLS_List;

/**
 * \brief 創建list
 * \param DataByte 您的數據位寬(位元組) 如：sizeof(int)
 * \returns list結構之指標
 *
 * \version 1.0.0
 */
CLS_List* CLS_Create(size_t DataByte);

/**
 * \brief (進階)創建list
 * \param DataByte 您的數據位寬(位元組) 如：sizeof(int)
 * \param Increment 增量(正整數為增量(內部會加上無條件捨去)，負數為倍率(內部會加上絕對值))
 * \returns list結構之指標，失敗(NULL)
 *
 * \version 1.0.0
 */
CLS_List* CLS_Create_P(size_t DataByte,float Increment);

/**
 * \brief 銷毀list(釋放記憶體)
 * \param list list結構之指標
 *
 * \version 1.0.0
 */
void CLS_Free(CLS_List** list);

/**
 * \brief 新增元素到list
 * \param list list結構之指標
 * \param data 要新增的數據指標
 * \returns 成功?
 *
 * \version 1.0.0
 */
int CLS_Psh(CLS_List* list,void* data);

/**
 * \brief 取得最後一項元素
 * \param list list結構之指標
 * \returns 成功(元素指標)，失敗(NULL)
 *
 * \version 1.0.0
 */
void* CLS_Pop(CLS_List* list);

/**
 * \brief 在指定索引位置新增(插入)元素到list，後面的元素會自動往後
 * \param list list結構之指標
 * \param index 索引
 * \param data 要新增的數據指標
 * \returns 成功?
 *
 * \version 1.0.0
 */
int CLS_Ins(CLS_List* list,size_t index,void* data);

/**
 * \brief 刪除list中的元素
 * \param list list結構之指標
 * \param index 索引
 * \returns 成功(0)，失敗(-1)
 *
 * \version 1.0.0
 */
int CLS_Del(CLS_List* list,size_t index);

/**
 * \brief 讀取list中的元素
 * \param list list結構之指標
 * \param index 索引
 * \returns 成功(元素指標)，失敗(NULL)
 *
 * \version 1.0.0
 */
void* CLS_Get(CLS_List* list,size_t index);

/**
 * \brief 替換某元素
 * \param list list結構之指標
 * \param index 索引
 * \param data 要換成的數據指標
 *
 * \version 1.0.0
 */
void CLS_Set(CLS_List* list,size_t index,void* data);

/**
 * \brief 取得列表長度(總索引數)
 * \param list list結構之指
 * \returns 總索引數
 *
 * \version 1.0.0
 */
size_t CLS_Len(CLS_List* list);

/**
 * \brief 清除列表(刪除所有元素，列表將為空，沒有任何索引)
 * \param list list結構之指標
 *
 * \version 1.0.0
 */
void CLS_Clear(CLS_List* list);

//設定C函數定義，使使用C++時也是如此
#ifdef __cplusplus
}
#endif

#endif