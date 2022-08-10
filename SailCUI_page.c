#include "SailCUI_page.h"
CUI_err _CUI_page_init()
{
	CUI_check_error();

	CUI_stack_new(&_CUI_dat_page_stack);
	_CUI_dat_page_stack_count = 0;

	return CUI_err_code(CUI_err_ok);
}

CUI_err _CUI_page_deinit()
{
	while (_CUI_dat_page_stack_count > 0)
	{
		CUI_stack_pop(&_CUI_dat_page_stack);
		if (_CUI_dat_page_stack->node == NULL)
			continue;
		CUI_page_del(_CUI_dat_page_stack->node);
	}

	return CUI_err_code(CUI_err_ok);
}

CUI_err CUI_page_new(CUI_page* self, CUI_err(*init)(), uint8_t width, wchar_t border_word, wchar_t line_word)
{
	CUI_check_error();

	CUI_page tmp = (CUI_page)malloc(sizeof(CUI_page));
	CUI_check_null(tmp, CUI_err_page, "为page分配内存失败！");

	if (tmpfile_s(&(tmp->fp)))
		return CUI_err_code_info(CUI_err_page_fp, "分配内存文件失败！");

	tmp->init = init;
	tmp->width = width;
	tmp->border_word = border_word;
	tmp->line_word = line_word;

	*self = tmp;

	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_page_del(CUI_page self)
{
	fclose(self->fp);
	//这里出错了，可能要优化一下free部分
	//free(self);
	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_page_active(CUI_page self)
{
	CUI_check_error();

	//设置当前页面
	_CUI_dat_page_stack->node = self;
	_CUI_dat_page_stack_count++;
	//把当前页面添加到栈
	CUI_stack_push(&_CUI_dat_page_stack);
	_CUI_dat_page = self;


	CUI_cls();
	self->init();

	return CUI_page_return(self);
}
//返回上一级
CUI_err CUI_page_return(CUI_page self)
{
	CUI_check_error();

	//把当前页面注销
	CUI_stack_pop(&_CUI_dat_page_stack);
	CUI_page_del(self);

	//如果当前页面就是最后一个页面就返回
	if (--_CUI_dat_page_stack_count <= 0)
		return CUI_err_code(CUI_err_ok);

	//还原上一个页面
	CUI_page page = { 0 };
	do
	{
		CUI_stack_pop(&_CUI_dat_page_stack);
		//如果当前页面就是最后一个页面就返回
		if (_CUI_dat_page_stack == NULL)
			return CUI_err_code(CUI_err_ok);
		page = (CUI_page)_CUI_dat_page_stack->node;
	} while (page == NULL);

	_CUI_dat_page = page;
	long pos = ftell(page->fp);
	fseek(page->fp, 0, SEEK_SET);

	CUI_cls();
	while (pos-- > 0)
		putwchar(fgetwc(page->fp));

	return CUI_err_code(CUI_err_ok);
}
