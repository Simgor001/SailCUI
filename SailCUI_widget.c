#include "SailCUI_widget.h"

//初始化选项，请在新建选项变量时或绘制函数结束后调用
CUI_err CUI_widget_init(CUI_option* opt)
{
	CUI_check_error();
	memset(opt, 0, sizeof(CUI_option));

	return CUI_err_code(CUI_err_ok);
}

//绘制告示板函数
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

//绘制分割线函数
CUI_err CUI_widget_line(CUI_option * opt)
{
	CUI_check_error();
	CUI_line self = _CUI_inheript_opt(opt->line);

	CUI_wprintf(L"%c ", self.border_word);
	for (int i = 0; i < self.width - 4; i++)
		CUI_putwchar(self.line_word);
	CUI_wprintf(L" %c\n", self.border_word);

	//清空选项，以备下一次使用
	CUI_widget_init(opt);

	return CUI_err_code(CUI_err_ok);
}

// 绘制标签函数
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


	//每一项的宽度，都与全部项中最长的一项有关
	for (int i = 0; i < self.items_qty; i++)
	{
		//符号和标题之间，还有一个'.'，所以要加1
		item_width = self.items[i].len + self.items[i].sign_len + 1;
		item_width_max = item_width > item_width_max ? item_width : item_width_max;
	}

	//两个项之间，需要加上分隔符最小宽度
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

	//到这里就把一行可以放多少个选项qty，计算好了
	if (line_qty == 0)
		return CUI_err_code_info(CUI_err_menu, "item标识符长度超出menu宽度！");

	//计算出一行的总长度，剩下的空间平均分配，如果有余数：
	//line_qty不为2时，将余数平摊到两边，如果无法平摊，那么右边多1
	//line_qty为2时，将余数放到两个项的中间

	//空余用于分配分隔符的空间
	uint8_t spare = self.width - 4 - line_len;
	//分隔符长度
	uint8_t cut_len = spare / (line_qty + 1);
	//左分隔符长度
	uint8_t cut_len_l = cut_len + self.cut_width_min;
	//右分隔符长度，不需要基本项尾，因为item_width_max已经包含了
	uint8_t cut_len_r = 0;

	if (line_qty == 2)
		cut_len += spare % (line_qty + 1);
	else
	{
		cut_len_l += (spare % (line_qty + 1)) / 2;
		cut_len_r += (uint8_t)((spare % (line_qty + 1)) / 2.0 + 0.5);
	}

	//避免长项都在左侧，让右侧看上去很空
	//当发现长项都不在最右侧时，把右边的分隔符给一部分左侧

	uint8_t item_width_r_max = 0;
	for (int i = line_qty - 1; i < self.items_qty; i += line_qty)
	{
		item_width = self.items[i].len + self.items[i].sign_len + 1;
		if (item_width < item_width_max)
			item_width_r_max = item_width > item_width_r_max ? item_width : item_width_r_max;
		else
			break;
	}
	//最右项少补长度
	int8_t cut_len_rs = 0;
	if (item_width < item_width_max)
	{
		cut_len_rs = (item_width_max - item_width_r_max) / 4;
		cut_len_l += cut_len_rs;
	}

	//row：行	n：项

	//输出了多少个项
	uint8_t item_count = 0;
	while (item_count < self.items_qty)
	{
		//左边框
		CUI_wprintf(L"%c ", self.border_word);
		//左间隔
		for (int i = 0; i < cut_len_l; i++)
			CUI_putwchar(L' ');
		//输出项
		for (int n = 0; n < line_qty; n++)
		{
			//处理末尾不够项，需要用空格代替的情况
			if (item_count >= self.items_qty)
			{
				for (int i = 0; i < line_qty - n; i++)
					for (int j = 0; j < item_width_max + cut_len - ((i + 1 < line_qty - n) ? 0 : cut_len_rs); j++)
						CUI_putwchar(L' ');
				break;
			}
			//输出项文本
			wchar_t* sign = (wchar_t*)malloc((uint8_t)(self.items[item_count].sign_len + 1) * sizeof(wchar_t));
			size_t sign_len = 0;
			CUI_check_null(sign, CUI_err_menu, "为menu_items_sign分配内存失败！");

			mbstowcs_s(&sign_len, sign, (uint8_t)(self.items[item_count].sign_len + 1), self.items[item_count].sign, self.items[item_count].sign_len);

			if (self.items[item_count].len > 0)
				CUI_wprintf(L"%s.%s", sign, self.items[item_count].title);
			else
				CUI_putwchar(L' ');
			
			//这个项的宽度
			uint8_t item_width = self.items[item_count].len + self.items[item_count].sign_len + 1;
			//这个项的宽度和最大宽度差多少
			uint8_t item_spare = item_width_max - item_width;
			//项尾补够空格以对齐下一项
			for (int i = 0; i < item_spare - ((n + 1 < line_qty) ? 0 : cut_len_rs); i++)
				CUI_putwchar(L' ');
			for (int i = 0; i < cut_len; i++)
				CUI_putwchar(L' ');

			item_count++;
		}
		//右间隔
		for (int i = 0; i < cut_len_r; i++)
			CUI_putwchar(L' ');
		//右边框
		CUI_wprintf(L" %c\n", self.border_word);

	}
	CUI_widget_init(opt);
	return CUI_err_code(CUI_err_ok);
}
CUI_err CUI_widget_menu_item(CUI_option* opt, CUI_item itm)
{
	CUI_check_error();
	CUI_menu self = _CUI_inheript_opt(opt->menu);

	//为菜单的item数组，分配内存
	CUI_item* tmp = { 0 };
	if (self.items == NULL)
		tmp = (CUI_item*)malloc(sizeof(CUI_item) * (++self.items_qty));
	else
		tmp = (CUI_item*)realloc(self.items, sizeof(CUI_item) * (++self.items_qty));

	CUI_check_null(tmp, CUI_err_menu_item, "为menu_items分配内存失败！");

	self.items = tmp;

	//设置单个项
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
				return CUI_err_code_info(CUI_err_menu_item, "为menu_item分配索引时，索引转换失败！");
			if (self.items[self.items_qty - 1].sign == NULL)
				return CUI_err_code_info(CUI_err_menu_item, "为menu_item分配索引时，分配内存失败！");

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