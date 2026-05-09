# C語言可變長列表函式庫

版本：1.0.0

---

# 函式列表：

所有函式皆以`CLS_`開頭

以`_P`結尾的函式為進階函式(power之意)，提供更多功能

函式							| 說明
--------------------------------|-----------
Create(DataByte)				| 創建list
Create_P(DataByte,Increment)	| 創建list(進階)

---

- AddLast(list,data)  在後面加入元素

- AddIndex(list,index,data)  在指定索引位置新增(插入)

- Replace(list,index,data)  替換某元素

- ReadIndex(list,index)  讀取list中的元素

- DelIndex(list,index)  刪除list中的元素