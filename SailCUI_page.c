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
	CUI_check_null(tmp, CUI_err_page, "Ϊpage�����ڴ�ʧ�ܣ�");

	if (tmpfile_s(&(tmp->fp)))
		return CUI_err_code_info(CUI_err_page_fp, "�����ڴ��ļ�ʧ�ܣ�");

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
	//��������ˣ�����Ҫ�Ż�һ��free����
	//free(self);
	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_page_active(CUI_page self)
{
	CUI_check_error();

	//���õ�ǰҳ��
	_CUI_dat_page_stack->node = self;
	_CUI_dat_page_stack_count++;
	//�ѵ�ǰҳ����ӵ�ջ
	CUI_stack_push(&_CUI_dat_page_stack);
	_CUI_dat_page = self;


	CUI_cls();
	self->init();

	return CUI_page_return(self);
}
//������һ��
CUI_err CUI_page_return(CUI_page self)
{
	CUI_check_error();

	//�ѵ�ǰҳ��ע��
	CUI_stack_pop(&_CUI_dat_page_stack);
	CUI_page_del(self);

	//�����ǰҳ��������һ��ҳ��ͷ���
	if (--_CUI_dat_page_stack_count <= 0)
		return CUI_err_code(CUI_err_ok);

	//��ԭ��һ��ҳ��
	CUI_page page = { 0 };
	do
	{
		CUI_stack_pop(&_CUI_dat_page_stack);
		//�����ǰҳ��������һ��ҳ��ͷ���
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
