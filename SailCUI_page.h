#ifndef _SAILCUI_PAGE_H
#define _SAILCUI_PAGE_H
#include "SailCUI.h"

/*
 =================================================================
	页面类：page

	1. 每一个页面都是独立宽度的
	2. 切换页面时，会进行清屏操作
	3. 页面提供全局属性：宽度、边界字符、分割线字符
 =================================================================
*/

//临时文件名长度
#define _CUI_TMP_NAME_LEN 10

typedef struct _CUI_page
{
	FILE* fp;					//输出流临时文件

	CUI_err(*init)(void);			//初始化函数

	uint8_t width;				//页面宽度
	wchar_t border_word;		//全局边界字符
	wchar_t line_word;			//全局分割线字符

	uint8_t stdout_width;//当前输出行已输出的宽度

} *CUI_page;

//全局当前活动页面
extern CUI_page _CUI_dat_page;
//全局页面栈
extern CUI_stack _CUI_dat_page_stack;
//全局页面栈节点数量
extern uint8_t _CUI_dat_page_stack_count;

//初始化页面
CUI_err _CUI_page_init();
//反初始化页面
CUI_err _CUI_page_deinit();
//创建页面
CUI_err CUI_page_new(CUI_page* self, CUI_err(*init)(void), uint8_t width, wchar_t border_word, wchar_t line_word);
//销毁页面
CUI_err CUI_page_del(CUI_page self);
//激活页面
CUI_err CUI_page_active(CUI_page self);
//返回上一级
CUI_err CUI_page_return(CUI_page self);
#endif