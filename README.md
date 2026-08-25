# C Variable-Length List Library — CLS
development and maintenance cji company changhua county taiwan province republic of china
Version: 1.1.0

## Links:
[Changelog](./doc/EN/CHANGELOG.md)
[License](./LICENSE.md)
[Bug Report](https://forms.gle/RYvRmd42WTKJG4gQA)

## author
- 林東頡 (cji)
- 賴洧霖 (weilinlai)

## Function List:
All functions are prefixed with `CLS_`.

Functions ending with `_P` are advanced functions (standing for "Power"), providing extended capabilities (please refer to `CLS.h` for details).

| Category | Function | Description | Parameters | _P |
| :--- | :--- | :--- | :--- | :--- |
| **Lifecycle** | `Create` | Creates a new list | Data byte width | Memory increment configuration |
| **Lifecycle** | `Free` | Frees the list and its memory | List | - |
| **Tail Operations** | `Psh` | Pushes data to the end | List, Data | - |
| **Tail Operations** | `Pop` | Pops the last element | List, Index | - |
| **Index Operations** | `Ins` | Inserts data at a specified index | List, Index, Data | - |
| **Index Operations** | `Del` | Deletes data at a specified index | List, Index | - |
| **Access Control** | `Get` | Retrieves the pointer of a specified index | List, Index | - |
| **Access Control** | `Set` | Overwrites the content of a specified index | List, Index, Data | - |
| **State Management**| `Len` | Retrieves the total number of elements | List | - |
| **State Management**| `Clear` | Clears all contents | List | - |
| **other**	   | `SetDeBug`	| set the debug messages to display| flag             | -

## Build and Usage Instructions:
1 execute c.bat or compile it yourself to generate the library in the bin and lib folders
2. Add `CLS.h` and the generated link libraries to your project, and configure the include paths and linker settings accordingly.
3. Include `CLS.h` in your source code, and use the functions prefixed with `CLS_` to operate the variable-length list.
4. Compile and run your program, ensuring that the libraries are correctly linked.
5. Utilize `CLS_` functions to create, manipulate, and free your variable-length lists, and enjoy flexible data structure management!

## Version Numbering Scheme
The format is `x.y.z` where:
- **x**: Major version number, incremented for significant changes or incompatible API modifications.
- **y**: Minor version number, incremented for new features that maintain backward compatibility.
- **z**: Patch number, incremented for bug fixes or minor changes.

---

# C語言可變長列表函式庫——CLS
開發與維護：CJI 公司 (中華民國台灣省彰化縣)
版本：1.1.0

## 連結：
[版本紀錄](./doc/ZH/CHANGELOG.md)
[授權文件](./LICENSE.md)
[BUG回報](https://forms.gle/RYvRmd42WTKJG4gQA)

## 作者：
- 林東頡 (cji)
- 賴洧霖 (weilinlai)

## 函式列表：
所有函式皆以`CLS_`開頭。

以`_P`結尾的函式為進階函式(power之意)，提供更多功能(自行自CLS.h中查看)。

| 分類 | 函式 | 說明 | 參數 | _P
|:---|:---|:---|:---|:---
| **生命週期** | `Create` 	| 建立列表　　　　　　| 數據位寬　　　　　| 記憶體擴充增量設定
| **生命週期** | `Free` 	| 釋放列表與記憶體　　| 列表　　　　　　　| -
| **末尾操作** | `Psh` 		| 壓入數據至末尾　　　| 列表、數據　　　　| -
| **末尾操作** | `Pop` 		| 彈出最後一項數據　　| 列表、索引　　　　| -
| **索引操作** | `Ins` 		| 在指定索引插入數據　| 列表、索引、數據　| -
| **索引操作** | `Del` 		| 刪除指定索引數據　　| 列表、索引　　　　| -
| **存取控制** | `Get` 		| 獲取指定索引的指標　| 列表、索引　　　　| -
| **存取控制** | `Set` 		| 覆蓋指定索引的內容　| 列表、索引、數據　| -
| **狀態管理** | `Len` 		| 獲取元素總數　　　　| 列表　　　　　　　| -
| **狀態管理** | `Clear` 	| 清空內容　　　　　　| 列表　　　　　　　| -
| **其他**	   | `SetDeBug`	| 設定要顯示的除錯訊息| 旗標             | -

## 建置與使用說明：
1. 執行c.bat或是自行編譯，生成連結庫於bin與lib資料夾中
2. 將CLS.h與連結庫加入專案中，包含路徑與連結器設定
3. 在程式中包含CLS.h，並使用CLS_開頭的函式來操作可變長列表
4. 編譯並執行程式，確保連結庫正確連結
5. 使用CLS_函式來創建、操作和釋放可變長列表，享受靈活的數據結構管理！

## 版本號命名方式
格式為`x.y.z` 其中：
- **x**：主版本號，當有重大變更或不相容的API修改時增加。
- **y**：次版本號，當有新增功能但保持向下兼容時增加。
- **z**：修訂號，當有錯誤修復或小改動時增加。