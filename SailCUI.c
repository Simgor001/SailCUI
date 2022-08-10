#include "SailCUI.h"

//ȫ�ֵ�ǰ�ҳ��
CUI_page _CUI_dat_page = { 0 };
//ȫ��ҳ��ջ
CUI_stack _CUI_dat_page_stack;
//ȫ��ҳ��ջ�ڵ�����
uint8_t _CUI_dat_page_stack_count = 0;

//ȫ�ִ�����
CUI_err _CUI_dat_err;

int main(int argc, char const* argv[])
{
	setlocale(LC_ALL, "chs");
	//printf("CUI����������...");
	_CUI_page_init();
	CUI_cls();
	CUI_main(argc, argv);
	// while (CUI_flush() != CUI_err_exit)
	//     ;
	_CUI_page_deinit();
	system("pause");
	return 0;
}

int CUI_wprintf(const wchar_t const* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	int count = vwprintf(fmt, ap);
	va_end(ap);

	va_start(ap, fmt);
	vfwprintf(_CUI_dat_page->fp, fmt, ap);
	va_end(ap);
	return count;
}

int CUI_wscanf_s(const wchar_t const* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	int count = vwscanf_s(fmt,ap);
	va_end(ap);

	va_start(ap, fmt);
	vfwprintf(_CUI_dat_page->fp, fmt, ap);
	fputwc(L'\n', _CUI_dat_page->fp);
	va_end(ap);
	return count;
}
wint_t CUI_putwchar(wchar_t _Character)
{
	putwchar(_Character);
	return fputwc(_Character, _CUI_dat_page->fp);
}


CUI_err CUI_flush()
{
	CUI_check_error();
	return CUI_err_code(CUI_err_err);
}

CUI_err _CUI_err_error(CUI_err err, char* file, int  line, char* info)
{
	CUI_cls();
	printf("---------------------------------\n");
	printf("����������һЩ���⣬��Ϣ���£�\n\n");
	printf("CUI��汾��\t%s\n�������ڣ�\t%s\n", _CUI_DAT_VISION, __DATE__);
	printf("�����룺\t%d\n", err);
	printf("---------------------------------\n");
	_CUI_dat_err = err;

	printf("���ļ� \"%s\" �У�\n�� %d ���������%s%s\n\n", file, line, *info ? "��" : "��", info);
	printf("�밴������˳�...\n");
	return err;
}

CUI_err CUI_stack_new(CUI_stack* stack)
{
	CUI_check_error();

	CUI_stack tmp = (CUI_stack)malloc(sizeof(CUI_stack));
	CUI_check_null(tmp, CUI_err_stack, "�½�stackʱ��Ϊstack�����ڴ�ʧ�ܣ�");

	tmp->node = NULL;
	tmp->p = NULL;
	tmp->index = 0;

	*stack = tmp;

	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_stack_push(CUI_stack* stack)
{
	CUI_check_error();

	CUI_check_null(stack, CUI_err_stack, "�������NULL������ջ������");

	CUI_stack tmp = (CUI_stack)malloc(sizeof(CUI_stack));
	CUI_check_null(tmp, CUI_err_stack, "��ջʱ��Ϊstack�����ڴ�ʧ�ܣ�");

	tmp->node = NULL;
	tmp->p = *stack;
	tmp->index = (*stack)->index + 1;

	*stack = tmp;

	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_stack_pop(CUI_stack* stack)
{
	CUI_check_error();

	CUI_check_null(*stack, CUI_err_stack, "�������NULL���г�ջ������");

	CUI_stack tmp = (*stack)->p;
	CUI_stack pre = *stack;
	//free(pre);

	*stack = tmp;

	return CUI_err_code(CUI_err_ok);
}
