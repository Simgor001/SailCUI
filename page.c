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

	//绘制一条分割线
	opt.line.line_word = L'=';
	CUI_widget_line(&opt);

	//绘制一个告示牌
	opt.board.title = L"XXX学生信息管理系统";
	CUI_widget_board(&opt);

	//绘制一个标签
	opt.lable.title = L"当前文件：file.data";
	CUI_widget_lable(&opt);

	//绘制一条分割线
	CUI_widget_line(&opt);

	//绘制一个标签
	opt.lable.title = L"学生总数： 2 （名）";
	CUI_widget_lable(&opt);
	//绘制一个标签
	opt.lable.title = L"数据项：   5 （项）";
	CUI_widget_lable(&opt);

	//绘制一条分割线
	CUI_widget_line(&opt);

	//CUI_input(L"请输入：");

	/*CUI_wprintf(L"请输入：");

	wchar_t buf[40] = { 0 };

	CUI_wscanf_s(L"%s", buf, 40);

	CUI_input(L"请按任意键翻页...");*/

	//设置菜单选项
	/*CUI_widget_menu_item(&opt, (CUI_item) { .title = L"添加hhhhhh" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"修改" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"测试的" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"排序" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"凑数2333" });*/

	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"添加" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"修改" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"排序" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"删除" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"查看" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"关于" });
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"" });
	wchar_t w[] = L"Q";
	CUI_widget_menu_item(&opt, (CUI_item) { .title = L"退出", .sign = w, .sign_len = 2 });

	//设置菜单选项间最小宽度
	opt.menu.cut_width_min = 2;
	//设置菜单一行选项数最大值
	opt.menu.line_max = 4;
	//绘制菜单
	CUI_widget_menu(&opt);

	//绘制一条分割线
	opt.line.line_word = L'=';
	CUI_widget_line(&opt);

	CUI_input(L">请选择操作：");
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
	CUI_widget_board(&opt);

	CUI_input(L"请输入：");

	return CUI_err_code(CUI_err_ok);
}
