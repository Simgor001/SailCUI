#include "SailCUI_widget.h"

//��ʼ��ѡ������½�ѡ�����ʱ����ƺ������������
CUI_err CUI_widget_init(CUI_option* opt)
{
	CUI_check_error();
	memset(opt, 0, sizeof(CUI_option));

	return CUI_err_code(CUI_err_ok);
}

//���Ƹ�ʾ�庯��
CUI_err CUI_widget_board(CUI_option* opt)
{
	CUI_check_error();

	CUI_board self = _CUI_inheript_opt(opt->board);

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
	
	CUI_widget_init(opt);

	return CUI_err_code(CUI_err_ok);
}

//���Ʒָ��ߺ���
CUI_err CUI_widget_line(CUI_option * opt)
{
	CUI_check_error();
	CUI_line self = _CUI_inheript_opt(opt->line);

	CUI_wprintf(L"%c ", self.border_word);
	for (int i = 0; i < self.width - 4; i++)
		CUI_putwchar(self.line_word);
	CUI_wprintf(L" %c\n", self.border_word);

	//���ѡ��Ա���һ��ʹ��
	CUI_widget_init(opt);

	return CUI_err_code(CUI_err_ok);
}

// ���Ʊ�ǩ����
CUI_err CUI_widget_lable(CUI_option *opt)
{
	CUI_check_error();
	CUI_lable self = _CUI_inheript_opt(opt->lable);


	int len = CUI_strwlen(self.title);

	CUI_wprintf(L"%c ", self.border_word);

	CUI_wprintf(L"%s ", self.title);
	for (int i = 0; i < (int)(self.width - 5 - len); i++)
		CUI_putwchar(' ');

	CUI_wprintf(L" %c\n", self.border_word);
	CUI_widget_init(opt);

	return CUI_err_code(CUI_err_ok);
}


CUI_err CUI_widget_menu(CUI_option * opt)
{
	CUI_check_error();
	CUI_menu self = _CUI_inheript_opt(opt->menu);

	uint8_t item_width_max = 0;
	uint8_t item_width = 0;
	uint8_t line_qty = self.line_max ? self.line_max : self.width / 10;


	//ÿһ��Ŀ�ȣ�����ȫ���������һ���й�
	for (int i = 0; i < self.items_qty; i++)
	{
		//���źͱ���֮�䣬����һ��'.'������Ҫ��1
		item_width = self.items[i].len + self.items[i].sign_len + 1;
		item_width_max = item_width > item_width_max ? item_width : item_width_max;
	}

	//������֮�䣬��Ҫ���Ϸָ�����С���
	item_width_max += self.cut_width_min;
	int line_len = 0;
	while (line_qty)
	{
		line_len = line_qty * item_width_max + self.cut_width_min;
		if (line_len > self.width - 4)
		{
			line_qty--;
			line_len = 0;
		}
		else
			break;
	}

	//������Ͱ�һ�п��ԷŶ��ٸ�ѡ��qty���������
	if (line_qty == 0)
		return CUI_err_code_info(CUI_err_menu, "item��ʶ�����ȳ���menu��ȣ�");

	//�����һ�е��ܳ��ȣ�ʣ�µĿռ�ƽ�����䣬�����������
	//line_qty��Ϊ2ʱ��������ƽ̯�����ߣ�����޷�ƽ̯����ô�ұ߶�1
	//line_qtyΪ2ʱ���������ŵ���������м�

	//�������ڷ���ָ����Ŀռ�
	uint8_t spare = self.width - 4 - line_len;
	//�ָ�������
	uint8_t cut_len = spare / (line_qty + 1);
	//��ָ�������
	uint8_t cut_len_l = cut_len + self.cut_width_min;
	//�ҷָ������ȣ�����Ҫ������β����Ϊitem_width_max�Ѿ�������
	uint8_t cut_len_r = 0;

	if (line_qty == 2)
		cut_len += spare % (line_qty + 1);
	else
	{
		cut_len_l += (spare % (line_qty + 1)) / 2;
		cut_len_r += (uint8_t)((spare % (line_qty + 1)) / 2.0 + 0.5);
	}

	//���ⳤ�����࣬���Ҳ࿴��ȥ�ܿ�
	//�����ֳ���������Ҳ�ʱ�����ұߵķָ�����һ�������

	uint8_t item_width_r_max = 0;
	for (int i = line_qty - 1; i < self.items_qty; i += line_qty)
	{
		item_width = self.items[i].len + self.items[i].sign_len + 1;
		if (item_width < item_width_max)
			item_width_r_max = item_width > item_width_r_max ? item_width : item_width_r_max;
		else
			break;
	}
	//�������ٲ�����
	int8_t cut_len_rs = 0;
	if (item_width < item_width_max)
	{
		cut_len_rs = (item_width_max - item_width_r_max) / 4;
		cut_len_l += cut_len_rs;
	}

	//row����	n����

	//����˶��ٸ���
	uint8_t item_count = 0;
	while (item_count < self.items_qty)
	{
		//��߿�
		CUI_wprintf(L"%c ", self.border_word);
		//����
		for (int i = 0; i < cut_len_l; i++)
			CUI_putwchar(L' ');
		//�����
		for (int n = 0; n < line_qty; n++)
		{
			//����ĩβ�������Ҫ�ÿո��������
			if (item_count >= self.items_qty)
			{
				for (int i = 0; i < line_qty - n; i++)
					for (int j = 0; j < item_width_max + cut_len - ((i + 1 < line_qty - n) ? 0 : cut_len_rs); j++)
						CUI_putwchar(L' ');
				break;
			}
			//������ı�
			wchar_t* sign = (wchar_t*)malloc((uint8_t)(self.items[item_count].sign_len + 1) * sizeof(wchar_t));
			size_t sign_len = 0;
			CUI_check_null(sign, CUI_err_menu, "Ϊmenu_items_sign�����ڴ�ʧ�ܣ�");

			mbstowcs_s(&sign_len, sign, (uint8_t)(self.items[item_count].sign_len + 1), self.items[item_count].sign, self.items[item_count].sign_len);

			if (self.items[item_count].len > 0)
				CUI_wprintf(L"%s.%s", sign, self.items[item_count].title);
			else
				CUI_putwchar(L' ');
			
			//�����Ŀ��
			uint8_t item_width = self.items[item_count].len + self.items[item_count].sign_len + 1;
			//�����Ŀ�Ⱥ�����Ȳ����
			uint8_t item_spare = item_width_max - item_width;
			//��β�����ո��Զ�����һ��
			for (int i = 0; i < item_spare - ((n + 1 < line_qty) ? 0 : cut_len_rs); i++)
				CUI_putwchar(L' ');
			for (int i = 0; i < cut_len; i++)
				CUI_putwchar(L' ');

			item_count++;
		}
		//�Ҽ��
		for (int i = 0; i < cut_len_r; i++)
			CUI_putwchar(L' ');
		//�ұ߿�
		CUI_wprintf(L" %c\n", self.border_word);

	}
	CUI_widget_init(opt);
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

	CUI_check_null(tmp, CUI_err_menu_item, "Ϊmenu_items�����ڴ�ʧ�ܣ�");

	self.items = tmp;

	//���õ�����
	int len = CUI_strwlen(itm.title);
	/*if (len <= 0)
	{
		self.items[self.items_qty - 1].title = L"<NULL>";
		len = CUI_strwlen(L"<NULL>");
	}
	else*/
	self.items[self.items_qty - 1].title = itm.title;
	self.items[self.items_qty - 1].len = len;

	if (itm.sign == NULL)
	{
		if (len > 0)
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
			self.items[self.items_qty - 1].sign_len = 0;
			self.items[self.items_qty - 1].sign = "";
		}
	}
	else
	{
		len = CUI_strwlen(itm.sign);
		self.items[self.items_qty - 1].sign_len = len;
		self.items[self.items_qty - 1].sign = itm.sign;
	}

	self.items[self.items_qty - 1].fun = itm.fun;

	memcpy_s(opt, sizeof(CUI_item), &self, sizeof(CUI_item));

	return CUI_err_code(CUI_err_ok);
}