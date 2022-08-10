#include "page.h"

CUI_page page_main;
CUI_page page_find;
CUI_err page_main_init();
CUI_err page_find_init();

CUI_err CUI_init()
{
	//先创建页面，再创建组件
	CUI_page_new(&page_main, page_main_init, 50, L'#', L'-');
	CUI_page_new(&page_find, page_find_init, 50, L'@', L'=');

	return CUI_err_code(CUI_err_ok);
}
CUI_err page_main_init()
{
	CUI_check_error();

	CUI_option opt;
	CUI_widget_init(&opt);

	//绘制一个告示牌
	opt.board.title = L"标题页";
	CUI_widget_board(opt);

	//绘制一个标签
	opt.lable.title = L"在这里输入的数据，等下还会显示的";
	CUI_widget_lable(opt);

	//绘制一条分割线
	CUI_widget_line(opt);

	CUI_wprintf(L"请输入文字：");
	wchar_t buf[40] = { 0 };
	CUI_wscanf_s(L"%s", buf, 40);
	

	getchar();
	CUI_page_active(page_find);

	return CUI_err_code(CUI_err_ok);
}
CUI_err page_find_init()
{
	CUI_option opt;
	CUI_widget_init(&opt);

	//绘制一个告示牌
	opt.board.title = L"第二页";
	CUI_widget_board(opt);
	getchar();
	return CUI_err_code(CUI_err_ok);
}
