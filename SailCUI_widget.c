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

	int len = CUI_strwlen(self.title);

	CUI_wprintf(L"%c ", self.border_word);
	for (int i = 0; i < self.width - 4; i++)
		CUI_putwchar(self.line_word);
	CUI_wprintf(L" %c\n%c ", self.border_word, self.border_word);

	for (int i = 0; i < (int)((self.width - 4.0 - len) / 2.0 + 0.5); i++)
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

	//���ѡ��Ա���һ��ʹ��
	CUI_widget_init(&opt);

	return CUI_err_code(CUI_err_ok);
}

// ���Ʊ�ǩ����
CUI_err CUI_widget_lable(CUI_option opt)
{
	CUI_check_error();
	CUI_lable self = _CUI_inheript_opt(opt.lable);


	int len = CUI_strwlen(self.title);

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

	uint8_t qty = self.max ? self.max : self.width / 10;
	uint8_t item_len = 0;
	while (qty)
	{
		int i = 0;
		for (i = 0; i < self.items_qty; i++)
		{
			item_len += self.items[i].len + self.items[i].sign_len + 1;
			if (item_len > self.width - 4)
			{
				qty--;
				item_len = 0;
				i = 0;
				break;
			}
			if ((i + 1) % qty == 0)
				item_len = 0;
		}
		if (i >= self.items_qty)
			break;
	}
	//������Ͱ�һ�п��ԷŶ��ٸ�ѡ��qty���������
	if(qty == 0)
		return CUI_err_code_info(CUI_err_menu,"item��ʶ�����ȳ���menu��ȣ�");

	CUI_widget_init(&opt);
	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_widget_menu_item(CUI_option* opt, CUI_item itm)
{
	CUI_check_error();
	CUI_menu self = _CUI_inheript_opt(opt->menu);

	//Ϊ�˵���item���飬�����ڴ�
	CUI_item* tmp = { 0 };
	if (self.items == NULL)
		tmp = (CUI_item*)malloc(sizeof(CUI_item) * (++self.items_qty));
	else
		tmp = (CUI_item*)realloc(self.items, sizeof(CUI_item) * (++self.items_qty));

	if (tmp == NULL)
		return CUI_err_code_info(CUI_err_menu_item, "Ϊmenu_items�����ڴ�ʧ�ܣ�");
	self.items = tmp;

	//���õ�����
	int len = CUI_strwlen(itm.title);
	if (len <= 0)
	{
		self.items[self.items_qty - 1].title = L"<NULL>";
		len = 7;
	}
	self.items[self.items_qty - 1].len = len;

	if (itm.sign == NULL)
	{
		char buf[4] = { 0 };
		_itoa_s(self.items_qty, buf, 4, 10);
		self.items[self.items_qty - 1].sign = (char*)malloc(4 * sizeof(char));

		if (buf == NULL)
			return CUI_err_code_info(CUI_err_menu_item, "Ϊmenu_item��������ʱ������ת��ʧ�ܣ�");
		if (self.items[self.items_qty - 1].sign == NULL)
			return CUI_err_code_info(CUI_err_menu_item, "Ϊmenu_item��������ʱ�������ڴ�ʧ�ܣ�");

		strncpy_s(self.items[self.items_qty - 1].sign, 4, buf, 4);
		self.items[self.items_qty - 1].sign_len = strlen(buf);
	}
	else
	{
		len = strlen(itm.sign);
		self.items[self.items_qty - 1].sign_len = len;
		strncpy_s(self.items[self.items_qty - 1].sign, len, itm.sign, len);
	}

	self.items[self.items_qty - 1].fun = itm.fun;

	memcpy_s(opt, sizeof(CUI_item), &self, sizeof(CUI_item));

	return CUI_err_code(CUI_err_ok);
}