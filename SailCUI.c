#include "SailCUI.h"
CUI_page page;

int main(int argc, char const* argv[])
{
	setlocale(LC_ALL, "chs");
	CUI_cls();
	CUI_main(argc, argv);
	// while (CUI_flush() != CUI_err_exit)
	//     ;
	getchar();
	return 0;
}

CUI_err CUI_flush()
{
	return CUI_err_exit;
}

CUI_err CUI_page_new(CUI_page* self, CUI_err(*init)(), uint8_t width, wchar_t border_word, wchar_t line_word)
{
	*self = (CUI_page)malloc(sizeof(CUI_page));
	if (!*self)
		return CUI_err_page;
	(*self)->point = *self;
	(*self)->init = init;
	(*self)->width = width;
	(*self)->border_word = border_word;
	(*self)->line_word = line_word;
	return CUI_err_ok;
}
void CUI_page_del(CUI_page self)
{
	free(self);
}
CUI_err CUI_page_active(CUI_page self)
{
	CUI_cls();
	page = self;
	self->init();
}
//退出页面
CUI_err CUI_page_close(CUI_page self) {}


CUI_err CUI_widget_init(CUI_option* opt)
{
	memset(opt, 0, sizeof(CUI_option));
	return CUI_err_ok;
}

//绘制告示板函数
CUI_err CUI_widget_board(CUI_option opt)
{
	CUI_board self = opt.board;

	if (!self.border_word)
		self.border_word = page->border_word;

	if (!self.line_word)
		self.line_word = page->line_word;

	if (!self.width)
		self.width = page->width;

	int len = strlen((char*)self.title);

	wprintf(L"%c ", self.border_word);
	for (int i = 0; i < self.width - 4; i++)
		putwchar(self.line_word);
	wprintf(L" %c\n%c ", self.border_word, self.border_word);

	for (int i = 0; i < (int)((self.width - 4 - len) / 2.0 + 0.5); i++)
		putwchar(self.line_word);

	fflush(stdout);
	wprintf(L"%s", self.title);

	for (int i = 0; i < (int)((self.width - 4 - len) / 2); i++)
		putwchar(self.line_word);
	wprintf(L" %c\n%c ", self.border_word, self.border_word);

	fflush(stdout);
	for (int i = 0; i < self.width - 4; i++)
		putwchar(self.line_word);
	wprintf(L" %c\n", self.border_word);
	CUI_widget_init(&opt);
}

//绘制分割线函数
CUI_err CUI_widget_line(CUI_option opt)
{
	CUI_line self = opt.line;
	if (!self.border_word)
		self.border_word = page->border_word;

	if (!self.line_word)
		self.line_word = page->line_word;

	if (!self.width)
		self.width = page->width;

	wprintf(L"%c ", self.border_word);
	for (int i = 0; i < self.width - 4; i++)
		putwchar(self.line_word);
	wprintf(L" %c\n", self.border_word);
	CUI_widget_init(&opt);
}

// 绘制标签函数
CUI_err CUI_widget_lable(CUI_option opt)
{
	CUI_lable self = opt.lable;

	if (!self.border_word)
		self.border_word = page->border_word;

	if (!self.line_word)
		self.line_word = page->line_word;

	if (!self.width)
		self.width = page->width;
	int len = strlen((char*)self.title);

	wprintf(L"%c ", self.border_word);

	wprintf(L"%s ", self.title);
	for (int i = 0; i < (int)(self.width - 5 - len); i++)
		putwchar(' ');

	wprintf(L" %c\n", self.border_word);
	CUI_widget_init(&opt);
}