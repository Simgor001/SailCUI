#ifndef _SAILCUI_WIDGET_H
#define _SAILCUI_WIDGET_H
#include "SailCUI.h"

//а�����䣬��������Ĭ��ֵ
#define _CUI_inheript_opt(opt) opt;{\
			self.border_word = self.border_word?self.border_word:_CUI_dat_page->border_word;\
			self.line_word = self.line_word?self.line_word:_CUI_dat_page->line_word;\
			self.width = self.width?self.width:_CUI_dat_page->width; }


/*
	���-��ʾ�壺board
	��ʽ��
	# ---------------------------- #
	# -----------����------------- #
	# ---------------------------- #
*/

typedef struct _CUI_board
{
	uint8_t width;			//(��ѡ)���
	wchar_t border_word;	//(��ѡ)�߽��ַ�
	wchar_t line_word;		//(��ѡ)�ָ����ַ�

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
	uint8_t width;			//(��ѡ)���
	wchar_t border_word;	//(��ѡ)�߽��ַ�
	wchar_t line_word;		//(��ѡ)�ָ����ַ�
} CUI_line;


/*
	���-��ǩ��lable
	��ʽ��
	# lable                        #
*/

typedef struct _CUI_lable
{
	uint8_t width;			//(��ѡ)���
	wchar_t border_word;	//(��ѡ)�߽��ַ�
	wchar_t line_word;		//(��ѡ)�ָ����ַ�

	wchar_t* title; //����
	uint8_t len;    //���ⳤ��
} CUI_lable;


/*
	���-�˵��item
	��Ҫ��ϲ˵�menu�����б�listʹ��
*/

typedef struct _CUI_item
{
	wchar_t* title; //����
	/*
	����з��ţ��˵��ͷ��ط��ţ����û���ţ��ͷ�������
	*/
	char *sign;		//(��ѡ)���ţ�Ĭ��ʹ������
	uint8_t sign_len;    //(��ѡ)���ⳤ��

	void(*fun)();	//(��ѡ)ѡ��ʱִ�еĺ���
	uint8_t len;    //(��ѡ)���ⳤ��
} CUI_item;


/*
	���-�˵���menu
	��ʽ��
	# ---------------------------- #
*/
typedef struct _CUI_menu
{
	uint8_t width;			//(��ѡ)���
	wchar_t border_word;	//(��ѡ)�߽��ַ�
	wchar_t line_word;		//(��ѡ)�ָ����ַ�

	wchar_t* title;			//����
	uint8_t len;			//���ⳤ��

	CUI_item* items;		//ѡ������
	uint8_t items_qty;		//ѡ�����

	uint8_t line_max;			//һ�����Ŷ�����
	uint8_t cut_width_min;	//�ָ�����С���

} CUI_menu;

/*
	���-�б�list
	��ʽ��
	# ---------------------------- #
*/

typedef struct _CUI_list
{
	uint8_t width;			//(��ѡ)���
	wchar_t border_word;	//(��ѡ)�߽��ַ�
	wchar_t line_word;		//(��ѡ)�ָ����ַ�

	wchar_t* title; //����
	uint8_t len;    //���ⳤ��
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
