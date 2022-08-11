#ifndef _SAILCUI_WIDGET_H
#define _SAILCUI_WIDGET_H
#include "SailCUI.h"

//邪恶的语句，用于设置默认值
#define _CUI_inheript_opt(opt) opt;{\
			self.border_word = self.border_word?self.border_word:_CUI_dat_page->border_word;\
			self.line_word = self.line_word?self.line_word:_CUI_dat_page->line_word;\
			self.width = self.width?self.width:_CUI_dat_page->width; }


/*
	组件-告示板：board
	样式：
	# ---------------------------- #
	# -----------标题------------- #
	# ---------------------------- #
*/

typedef struct _CUI_board
{
	uint8_t width;			//(可选)宽度
	wchar_t border_word;	//(可选)边界字符
	wchar_t line_word;		//(可选)分割线字符

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
	uint8_t width;			//(可选)宽度
	wchar_t border_word;	//(可选)边界字符
	wchar_t line_word;		//(可选)分割线字符
} CUI_line;


/*
	组件-标签：lable
	样式：
	# lable                        #
*/

typedef struct _CUI_lable
{
	uint8_t width;			//(可选)宽度
	wchar_t border_word;	//(可选)边界字符
	wchar_t line_word;		//(可选)分割线字符

	wchar_t* title; //标题
	uint8_t len;    //标题长度
} CUI_lable;


/*
	组件-菜单项：item
	需要配合菜单menu或者列表list使用
*/

typedef struct _CUI_item
{
	wchar_t* title; //标题
	/*
	如果有符号，菜单就返回符号，如果没符号，就返回索引
	*/
	char *sign;		//(可选)符号，默认使用索引
	uint8_t sign_len;    //(可选)标题长度

	void(*fun)();	//(可选)选中时执行的函数
	uint8_t len;    //(可选)标题长度
} CUI_item;


/*
	组件-菜单：menu
	样式：
	# ---------------------------- #
*/
typedef struct _CUI_menu
{
	uint8_t width;			//(可选)宽度
	wchar_t border_word;	//(可选)边界字符
	wchar_t line_word;		//(可选)分割线字符

	wchar_t* title;			//标题
	uint8_t len;			//标题长度

	CUI_item* items;		//选项数组
	uint8_t items_qty;		//选项个数

	uint8_t line_max;			//一行最多放多少项
	uint8_t cut_width_min;	//分隔符最小宽度

} CUI_menu;

/*
	组件-列表：list
	样式：
	# ---------------------------- #
*/

typedef struct _CUI_list
{
	uint8_t width;			//(可选)宽度
	wchar_t border_word;	//(可选)边界字符
	wchar_t line_word;		//(可选)分割线字符

	wchar_t* title; //标题
	uint8_t len;    //标题长度
} CUI_list;


typedef union _CUI_widget
{
	CUI_board board;
	CUI_line line;
	CUI_lable lable;
	CUI_menu menu;

}CUI_option;

CUI_err CUI_widget_init(CUI_option* opt);

CUI_err CUI_widget_board(CUI_option opt);
CUI_err CUI_widget_line(CUI_option opt);
CUI_err CUI_widget_lable(CUI_option opt);

CUI_err CUI_widget_menu(CUI_option opt);
CUI_err CUI_widget_menu_item(CUI_option* opt, CUI_item itm);

#endif
