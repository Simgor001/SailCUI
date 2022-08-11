#include "SailCUI.h"


//全局错误码
CUI_err _CUI_dat_err;

int main(int argc, char const* argv[])
{
	setlocale(LC_ALL, "chs");
	//printf("CUI库正在启动...");

	_CUI_page_init();
	CUI_cls();

	CUI_main(argc, argv);
	// while (CUI_flush() != CUI_err_exit)
	//     ;
	_CUI_page_deinit();
	system("pause");
	return 0;
}

int CUI_wprintf(const wchar_t* fmt, ...)
{
	/*
		要重写'\t'部分，不然无法识别导致边框溢出
	*/
	va_list ap;

	va_start(ap, fmt);
	int count = vwprintf(fmt, ap);
	va_end(ap);

	va_start(ap, fmt);
	vfwprintf(_CUI_dat_page->fp, fmt, ap);
	va_end(ap);
	return count;
}

/*用来获取字符串时，记得指定最大长度*/
int CUI_wscanf_s(const wchar_t* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	int count = vwscanf_s(fmt, ap);
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
	printf("程序遇到了一些问题，信息如下：\n\n");
	printf("CUI库版本：\t%s\n编译日期：\t%s\n", _CUI_DAT_VISION, __DATE__);
	printf("错误码：\t%d\n", err);
	printf("---------------------------------\n");
	_CUI_dat_err = err;

	printf("在文件 \"%s\" 中，\n第 %d 行提出错误%s%s\n\n", file, line, *info ? "：" : "。", info);
	printf("请按任意键退出...\n");
	return err;
}

CUI_err CUI_stack_new(CUI_stack* stack)
{
	CUI_check_error();

	CUI_stack tmp = (CUI_stack)malloc(sizeof(struct _CUI_stack));
	CUI_check_null(tmp, CUI_err_stack, "新建stack时，为stack分配内存失败！");

	tmp->node = NULL;
	tmp->p = NULL;
	tmp->index = 0;

	*stack = tmp;

	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_stack_push(CUI_stack* stack)
{
	CUI_check_error();

	CUI_check_null(stack, CUI_err_stack, "不允许对NULL进行入栈操作！");

	CUI_stack tmp = (CUI_stack)malloc(sizeof(struct _CUI_stack));
	CUI_check_null(tmp, CUI_err_stack, "入栈时，为stack分配内存失败！");

	tmp->node = NULL;
	tmp->p = *stack;
	tmp->index = (*stack)->index + 1;

	*stack = tmp;

	return CUI_err_code(CUI_err_ok);
}

CUI_err CUI_stack_pop(CUI_stack* stack)
{
	CUI_check_error();

	CUI_check_null(*stack, CUI_err_stack, "不允许对NULL进行出栈操作！");

	CUI_stack tmp = (*stack)->p;
	free(*stack);
	*stack = tmp;

	return CUI_err_code(CUI_err_ok);
}
