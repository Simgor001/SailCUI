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

//page_main页面的初始化函数
CUI_err page_main_init()
{
	CUI_check_error();

	CUI_option opt;
	CUI_widget_init(&opt);

	//绘制一个告示牌
	opt.board.title = L"第一行";
	CUI_widget_board(opt);

	//绘制一个标签
	opt.lable.title = L"在这里输入的数据，等下还会显示的";
	CUI_widget_lable(opt);

	//绘制一条分割线
	CUI_widget_line(opt);

	//CUI_input(L"请输入：");

	CUI_wprintf(L"请输入：");

	wchar_t buf[40] = { 0 };

	CUI_wscanf_s(L"%s", buf, 40);

	CUI_input(L"请按任意键翻页...");

	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"A_ABABBABAA" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"B_ABABBABA" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"C_ABABBABA" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"D" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"E_ABABBABA" });

	CUI_widget_menu(opt);
	CUI_page_active(page_find);

	return CUI_err_code(CUI_err_ok);
}

CUI_err page_find_init()
{
	CUI_check_error();

	CUI_option opt;
	CUI_widget_init(&opt);

	//绘制一个告示牌
	opt.board.title = L"第二页";
	CUI_widget_board(opt);

	CUI_input(L"请输入：");

	return CUI_err_code(CUI_err_ok);
}
