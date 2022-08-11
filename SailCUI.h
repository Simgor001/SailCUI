#ifndef _SAILCUI_H
#define _SAILCUI_H
#define _CUI_DAT_VISION "1.0.0"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

//全局类：CUI

//清屏
#define CUI_cls() fflush(stdin);system("cls");

int CUI_wprintf(const wchar_t * fmt, ...);
int CUI_wscanf_s(const wchar_t * fmt, ...);

wint_t CUI_putwchar(const wchar_t _Character);
wint_t CUI_getwchar(void);
wint_t CUI_input(const wchar_t* str);
size_t CUI_strwlen(const wchar_t* str);


/*
 =================================================================
	全局-错误类：CUI_err

	作为CUI库绝大部分函数的基本类，提供错误码、安全检查等功能。
	所有对内存操作的CUI库函数，需要满足以下要求：
		1. 返回值是CUI_err，必要时，函数后继续检查是否正常返回。
		2. CUI_check_error()必须调用在函数定义的最前方，避免出现错误后，
			程序继续运行，导致内存溢出或越界。
		3. 函数返回时，必须调用CUI_err_code(err)，参数err为CUI_err的枚举值。
		4. 当程序需要报错时，可以选用CUI_err_code_info(err,info)，info为报错信息。
 =================================================================
*/

//检查错误
#define CUI_check_error() if(_CUI_dat_err)return CUI_err_err;
//检查指针是否为空
#define CUI_check_null(p,err,info) if(p == NULL) return CUI_err_code_info(err, info)
//返回错误
#define CUI_err_code(err) err?_CUI_err_error(err,__FILE__,__LINE__,""):CUI_err_ok
//返回错误，且设定提示信息
#define CUI_err_code_info(err,info) err?_CUI_err_error(err,__FILE__,__LINE__,info):CUI_err_ok

//错误码
typedef enum
{
	CUI_err_ok,			//无错误
	CUI_err_err,		//需要退出
	CUI_err_stack,
	CUI_err_page,		//新建页面失败
	CUI_err_page_fp,	//为页面分配临时文件失败
	CUI_err_menu_item,	
	CUI_err_menu
} CUI_err;

//全局错误码
extern CUI_err _CUI_dat_err;
//执行报错
CUI_err _CUI_err_error(CUI_err err, char* file, int  line, char* info);


/*
 =================================================================
	全局-栈：CUI_stack
 =================================================================
*/
typedef struct _CUI_stack
{
	void* node;
	struct _CUI_stack* p;
	uint8_t index;
}*CUI_stack;

CUI_err CUI_stack_new(CUI_stack* stack);
CUI_err CUI_stack_push(CUI_stack* stack);
CUI_err CUI_stack_pop(CUI_stack* stack);


// CUI程序入口
extern CUI_err CUI_main(int argc, char const* argv[]);
// CUI程序配置部分
extern CUI_err CUI_init(void);
//刷新
CUI_err CUI_flush(void);

#include "SailCUI_page.h"
#include "SailCUI_widget.h"
#endif

