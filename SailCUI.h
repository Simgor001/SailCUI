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

//ȫ���ࣺCUI

//����
#define CUI_cls() fflush(stdin);system("cls");

int CUI_wprintf(const wchar_t * fmt, ...);
int CUI_wscanf_s(const wchar_t * fmt, ...);

wint_t CUI_putwchar(const wchar_t _Character);
wint_t CUI_getwchar(void);
wint_t CUI_input(const wchar_t* str);
size_t CUI_strwlen(const wchar_t* str);


/*
 =================================================================
	ȫ��-�����ࣺCUI_err

	��ΪCUI����󲿷ֺ����Ļ����࣬�ṩ�����롢��ȫ���ȹ��ܡ�
	���ж��ڴ������CUI�⺯������Ҫ��������Ҫ��
		1. ����ֵ��CUI_err����Ҫʱ���������������Ƿ��������ء�
		2. CUI_check_error()��������ں����������ǰ����������ִ����
			����������У������ڴ������Խ�硣
		3. ��������ʱ���������CUI_err_code(err)������errΪCUI_err��ö��ֵ��
		4. ��������Ҫ����ʱ������ѡ��CUI_err_code_info(err,info)��infoΪ������Ϣ��
 =================================================================
*/

//������
#define CUI_check_error() if(_CUI_dat_err)return CUI_err_err;
//���ָ���Ƿ�Ϊ��
#define CUI_check_null(p,err,info) if(p == NULL) return CUI_err_code_info(err, info)
//���ش���
#define CUI_err_code(err) err?_CUI_err_error(err,__FILE__,__LINE__,""):CUI_err_ok
//���ش������趨��ʾ��Ϣ
#define CUI_err_code_info(err,info) err?_CUI_err_error(err,__FILE__,__LINE__,info):CUI_err_ok

//������
typedef enum
{
	CUI_err_ok,			//�޴���
	CUI_err_err,		//��Ҫ�˳�
	CUI_err_stack,
	CUI_err_page,		//�½�ҳ��ʧ��
	CUI_err_page_fp,	//Ϊҳ�������ʱ�ļ�ʧ��
	CUI_err_menu_item,	
	CUI_err_menu
} CUI_err;

//ȫ�ִ�����
extern CUI_err _CUI_dat_err;
//ִ�б���
CUI_err _CUI_err_error(CUI_err err, char* file, int  line, char* info);


/*
 =================================================================
	ȫ��-ջ��CUI_stack
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


// CUI�������
extern CUI_err CUI_main(int argc, char const* argv[]);
// CUI�������ò���
extern CUI_err CUI_init(void);
//ˢ��
CUI_err CUI_flush(void);

#include "SailCUI_page.h"
#include "SailCUI_widget.h"
#endif

