#include "SailCUI.h"


//ȫ�ִ�����
CUI_err _CUI_dat_err = CUI_err_ok;

//ȫ�ֵ�ǰ�����������Ŀ��
uint8_t _CUI_dat_stdout_width;

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
size_t CUI_wprintf(const wchar_t* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);

	//SailCUI�����棬Ϊ�����������д���ĵط�
	wchar_t buf[255] = { 0 };

	uint8_t count = (uint8_t)vswprintf(buf, 255, fmt, ap);

	/*
		����ͳ���ж��ٸ�\t��ÿһ��\t������4��λ��
		ע�⣬���û�л��У�stdout_width���ܱ�ˢ��
	*/

	//ѭ�����֮��i����fmt�ַ����ĳ���
	uint8_t i = 0;
	uint8_t tab_count = 0;
	while (buf[i] != L'\0')
		if (buf[i++] == L'\t')
			tab_count++;

	//������Ҫ2�ֽ�
	uint8_t  str_len = i + tab_count * 3 + 2;
	wchar_t* str = NULL;
	str = (wchar_t*)calloc((str_len), sizeof(wchar_t));

	CUI_check_null(str, CUI_err_stdout, "Ϊ��ʽ���ַ��������ڴ�ʧ�ܣ�");

	//ԭ�ַ�������
	i = 0;
	//���ַ�������
	count = 0;
	//���ڼ���tab�ո���
	uint8_t tab = 0;
	while (buf[i] != L'\0')
		if (buf[i] == L'\t')
		{
			tab = 4 - (_CUI_dat_stdout_width % 4);
			for (int n = 0; n < tab; n++)
			{
				_CUI_dat_stdout_width++;
				str[count++] = L' ';
			}
			i++;
		}
		else if (count < str_len)
		{
			str[count++] = buf[i];
			if (buf[i] == L'\n')
				_CUI_dat_stdout_width = 0;
			else
				_CUI_dat_stdout_width += buf[i] > 0xff ? 2 : 1;
			i++;
		}
	if (str[0] != '\0')
		_CUI_dat_stdout_width--;
	str[count] = L'\0';

	vwprintf(str, ap);
	va_end(ap);

	va_start(ap, fmt);
	vfwprintf(_CUI_dat_page->fp, str, ap);
	va_end(ap);
	return (size_t)count - 1;
}

/*������ȡ�ַ���ʱ���ǵ�ָ����󳤶�*/
size_t CUI_wscanf_s(const wchar_t* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	size_t count = vwscanf_s(fmt, ap);
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
	if (_Character == L'\n')
		_CUI_dat_stdout_width = 0;
	else
		_CUI_dat_stdout_width += _Character > 0xff ? 2 : 1;
	return fputwc(_Character, _CUI_dat_page->fp);
}

wint_t CUI_getwchar(void)
{
	wint_t tmp = getwchar();
	fputwc(tmp, _CUI_dat_page->fp);
	fputwc(L'\n', _CUI_dat_page->fp);

	return tmp;
}

wint_t CUI_input(const wchar_t* str)
{
	wprintf(L"%s", str);
	fwprintf(_CUI_dat_page->fp, L"%s", str);

	wint_t tmp = getwchar();
	fputwc(tmp, _CUI_dat_page->fp);
	fputwc(L'\n', _CUI_dat_page->fp);

	int c = 0;
	while ((c = getchar()) != '\n' && c != '\0' && c != EOF)
		continue;

	return tmp;
}

size_t CUI_strwlen(const wchar_t* str)
{
	size_t i = 0;
	size_t len = 0;
	while (str[i] != L'\0')
		len += str[i++] > 0xFF ? 2 : 1;
	return len;
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

	CUI_stack tmp = (CUI_stack)malloc(sizeof(struct _CUI_stack));
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

	CUI_stack tmp = (CUI_stack)malloc(sizeof(struct _CUI_stack));
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
	free(*stack);
	*stack = tmp;

	return CUI_err_code(CUI_err_ok);
}
