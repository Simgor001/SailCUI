#ifndef _SAILCUI_H
#define _SAILCUI_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

//�ܹ��漰��ҳ��ĸ��ÿһ��ҳ�涼�Ƕ�����ȵģ����������Ӧ����һ����ҳ��
//�л�ҳ��ʱ���������������
//ҳ���ṩȫ�ֿ������

//ȫ���ࣺCUI
#define CUI_cls() system("cls");
//�������
typedef enum
{
	CUI_err_ok,  //�޴���
	CUI_err_exit, //��Ҫ�˳�
	CUI_err_page    //�½�ҳ��ʧ��
} CUI_err;
typedef enum
{
	CUI_type_page,
	CUI_type_board
} CUI_type;

// CUI�������
extern CUI_err CUI_main(int argc, char const* argv[]);
// CUI�������ò���
extern CUI_err CUI_init();
//ˢ��
CUI_err CUI_flush();

//ҳ���ࣺpage
typedef struct _CUI_page
{
	struct _CUI_page* point; //����ָ��
	CUI_type type;           //�������

	CUI_err(*init)(); //��ʼ��

	uint8_t width; //ҳ����
	wchar_t border_word; //ȫ�ֱ߽��ַ�
	wchar_t line_word;   //ȫ�ַָ����ַ�

} *CUI_page;
extern CUI_page page;//��ǰ�page��ȫ�֣�

//����ҳ��
CUI_err CUI_page_new(CUI_page, CUI_err(*init)(), wchar_t border_word, wchar_t line_word);
//����ҳ��
void CUI_page_del(CUI_page self);
//����ҳ��
CUI_err CUI_page_active(CUI_page self);
//�˳�ҳ��
CUI_err CUI_page_close(CUI_page self);

/*
	���-��ʾ�壺board
	��ʽ��
	# ---------------------------- #
	# -----------����------------- #
	# ---------------------------- #
*/

typedef struct _CUI_board
{
	uint8_t width;    //ҳ����
	wchar_t border_word; //�߽��ַ�
	wchar_t line_word;   //�ָ����ַ�

	wchar_t* title; //����
	uint8_t len;    //���ⳤ��
} CUI_board;


/*
	���-�ָ��ߣ�line
	��ʽ��
	# ---------------------------- #
*/

typedef struct _CUI_line
{
	uint8_t width;    //���
	wchar_t border_word; //�߽��ַ�
	wchar_t line_word;   //�ָ����ַ�
} CUI_line;


/*
	���-��ǩ��lable
	��ʽ��
	# ---------------------------- #
*/

typedef struct _CUI_lable
{
	uint8_t width;    //���
	wchar_t border_word; //�߽��ַ�
	wchar_t line_word;   //�ָ����ַ�

	wchar_t* title; //����
	uint8_t len;    //���ⳤ��
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


//ȫ�ִ洢��
// CUI_page CUI_list_page;

#endif

