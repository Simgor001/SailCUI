#ifndef _SAILCUI_PAGE_H
#define _SAILCUI_PAGE_H
#include "SailCUI.h"

/*
 =================================================================
	ҳ���ࣺpage

	1. ÿһ��ҳ�涼�Ƕ�����ȵ�
	2. �л�ҳ��ʱ���������������
	3. ҳ���ṩȫ�����ԣ���ȡ��߽��ַ����ָ����ַ�
 =================================================================
*/

//��ʱ�ļ�������
#define _CUI_TMP_NAME_LEN 10

typedef struct _CUI_page
{
	FILE* fp;					//�������ʱ�ļ�

	CUI_err(*init)(void);			//��ʼ������

	uint8_t width;				//ҳ����
	wchar_t border_word;		//ȫ�ֱ߽��ַ�
	wchar_t line_word;			//ȫ�ַָ����ַ�

	uint8_t stdout_width;//��ǰ�����������Ŀ��

} *CUI_page;

//ȫ�ֵ�ǰ�ҳ��
extern CUI_page _CUI_dat_page;
//ȫ��ҳ��ջ
extern CUI_stack _CUI_dat_page_stack;
//ȫ��ҳ��ջ�ڵ�����
extern uint8_t _CUI_dat_page_stack_count;

//��ʼ��ҳ��
CUI_err _CUI_page_init();
//����ʼ��ҳ��
CUI_err _CUI_page_deinit();
//����ҳ��
CUI_err CUI_page_new(CUI_page* self, CUI_err(*init)(void), uint8_t width, wchar_t border_word, wchar_t line_word);
//����ҳ��
CUI_err CUI_page_del(CUI_page self);
//����ҳ��
CUI_err CUI_page_active(CUI_page self);
//������һ��
CUI_err CUI_page_return(CUI_page self);
#endif