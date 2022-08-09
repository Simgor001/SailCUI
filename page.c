#include "page.h"

CUI_page page_main;
CUI_page page_find;
CUI_err page_main_init();
CUI_err page_find_init();

CUI_err CUI_init()
{
	//先创建页面，再创建组件
	CUI_page_new(&page_main, page_main_init, 50, L'#', L'-');
	CUI_page_new(&page_find, page_find_init, 50, L'#', L'-');
}
CUI_err page_main_init()
{
	CUI_option opt;
	CUI_widget_init(&opt);

	//绘制一个告示牌
	opt.board.title = L"标题";
	CUI_widget_board(opt);

	//绘制一个标签
	opt.lable.title = L"标签：内容";
	CUI_widget_lable(opt);

	//绘制一条分割线
	CUI_widget_line(opt);

	return CUI_err_ok;
}
CUI_err page_find_init()
{
}
