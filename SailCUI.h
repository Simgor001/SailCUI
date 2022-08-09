#ifndef _SAILCUI_H
#define _SAILCUI_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

//架构涉及到页面的概念，每一个页面都是独立宽度的，所有组件都应该有一个父页面
//切换页面时，会进行清屏操作
//页面提供全局宽度属性

//全局类：CUI
#define CUI_cls() system("cls");
//错误代码
typedef enum
{
	CUI_err_ok,  //无错误
	CUI_err_exit, //需要退出
	CUI_err_page    //新建页面失败
} CUI_err;
typedef enum
{
	CUI_type_page,
	CUI_type_board
} CUI_type;

// CUI程序入口
extern CUI_err CUI_main(int argc, char const* argv[]);
// CUI程序配置部分
extern CUI_err CUI_init();
//刷新
CUI_err CUI_flush();

//页面类：page
typedef struct _CUI_page
{
	struct _CUI_page* point; //自身指针
	CUI_type type;           //组件类型

	CUI_err(*init)(); //初始化

	uint8_t width; //页面宽度
	wchar_t border_word; //全局边界字符
	wchar_t line_word;   //全局分割线字符

} *CUI_page;
extern CUI_page page;//当前活动page（全局）

//创建页面
CUI_err CUI_page_new(CUI_page, CUI_err(*init)(), wchar_t border_word, wchar_t line_word);
//销毁页面
void CUI_page_del(CUI_page self);
//激活页面
CUI_err CUI_page_active(CUI_page self);
//退出页面
CUI_err CUI_page_close(CUI_page self);

/*
	组件-告示板：board
	样式：
	# ---------------------------- #
	# -----------标题------------- #
	# ---------------------------- #
*/

typedef struct _CUI_board
{
	uint8_t width;    //页面宽度
	wchar_t border_word; //边界字符
	wchar_t line_word;   //分割线字符

	wchar_t* title; //标题
	uint8_t len;    //标题长度
} CUI_board;


/*
	组件-分割线：line
	样式：
	# ---------------------------- #
*/

typedef struct _CUI_line
{
	uint8_t width;    //宽度
	wchar_t border_word; //边界字符
	wchar_t line_word;   //分割线字符
} CUI_line;


/*
	组件-标签：lable
	样式：
	# ---------------------------- #
*/

typedef struct _CUI_lable
{
	uint8_t width;    //宽度
	wchar_t border_word; //边界字符
	wchar_t line_word;   //分割线字符

	wchar_t* title; //标题
	uint8_t len;    //标题长度
} CUI_lable;



typedef union _CUI_widget
{
	CUI_page page;
	CUI_board board;
	CUI_line line;
	CUI_lable lable;

}CUI_option;

CUI_err CUI_widget_init(CUI_option* opt);
CUI_err CUI_widget_board(CUI_option opt);
CUI_err CUI_widget_line(CUI_option opt);
CUI_err CUI_widget_lable(CUI_option opt);


//全局存储类
// CUI_page CUI_list_page;

#endif

