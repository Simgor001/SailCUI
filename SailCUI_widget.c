#include "SailCUI_widget.h"

//��ʼ��ѡ������½�ѡ�����ʱ����ƺ������������
CUI_err CUI_widget_init(CUI_option* opt)
{
	CUI_check_error();
	memset(opt, 0, sizeof(CUI_option));

	return CUI_err_code(CUI_err_ok);
}

//���Ƹ�ʾ�庯��
CUI_err CUI_widget_board(CUI_option opt)
{
	CUI_check_error();

	CUI_board self = _CUI_inheript_opt(opt.board);

	int len = strlen((char*)self.title);

	CUI_wprintf(L"%c ", self.border_word);
	for (int i = 0; i < self.width - 4; i++)
		CUI_putwchar(self.line_word);
	CUI_wprintf(L" %c\n%c ", self.border_word, self.border_word);

	for (int i = 0; i < (int)((self.width - 4 - len) / 2.0 + 0.5); i++)
		CUI_putwchar(self.line_word);

	fflush(stdout);
	CUI_wprintf(L"%s", self.title);

	for (int i = 0; i < (int)((self.width - 4 - len) / 2); i++)
		CUI_putwchar(self.line_word);
	CUI_wprintf(L" %c\n%c ", self.border_word, self.border_word);

	fflush(stdout);
	for (int i = 0; i < self.width - 4; i++)
		CUI_putwchar(self.line_word);
	CUI_wprintf(L" %c\n", self.border_word);
	CUI_widget_init(&opt);

	return CUI_err_code(CUI_err_ok);
}

//���Ʒָ��ߺ���
CUI_err CUI_widget_line(CUI_option opt)
{
	CUI_check_error();
	CUI_line self = _CUI_inheript_opt(opt.line);

	CUI_wprintf(L"%c ", self.border_word);
	for (int i = 0; i < self.width - 4; i++)
		CUI_putwchar(self.line_word);
	CUI_wprintf(L" %c\n", self.border_word);
	CUI_widget_init(&opt);

	return CUI_err_code(CUI_err_ok);
}

// ���Ʊ�ǩ����
CUI_err CUI_widget_lable(CUI_option opt)
{
	CUI_check_error();
	CUI_lable self = _CUI_inheript_opt(opt.lable);


	int len = strlen((char*)self.title);

	CUI_wprintf(L"%c ", self.border_word);

	CUI_wprintf(L"%s ", self.title);
	for (int i = 0; i < (int)(self.width - 5 - len); i++)
		CUI_putwchar(' ');

	CUI_wprintf(L" %c\n", self.border_word);
	CUI_widget_init(&opt);

	return CUI_err_code(CUI_err_ok);
}


CUI_err CUI_widget_menu(CUI_option opt)
{
	CUI_check_error();
	CUI_menu self = _CUI_inheript_opt(opt.menu);



	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_widget_menu_item(CUI_option opt, CUI_item itm)
{
	CUI_check_error();
	CUI_menu self = _CUI_inheript_opt(opt.menu);

	CUI_item* tmp = { 0 };
	if (self.items == NULL)
		self.items = (CUI_item*)malloc(sizeof(CUI_item) * (++self.items_count));
	else
		tmp = (CUI_item*)realloc(self.items, sizeof(CUI_item) * (++self.items_count));
	if (tmp == NULL)
		return CUI_err_code_info(CUI_err_page, "Ϊmenu_items�����ڴ�ʧ�ܣ�");
	self.items = tmp;

	int len = strlen((char*)itm.title);
	if (len <= 0)
	{
		self.items[self.items_count - 1].title = L"<NULL>";
		len = 7;
	}
	self.items[self.items_count - 1].len = len;

	if (itm.sign == '\0')
		self.items[self.items_count - 1].sign = self.items_count + '0';
	else
		self.items[self.items_count - 1].sign = itm.sign;

	self.items[self.items_count - 1].fun = itm.fun;

	CUI_widget_init(&opt);

	return CUI_err_code(CUI_err_ok);
}