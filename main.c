#include "SailCUI.h"
#include "page.h"

CUI_err CUI_main(int argc, char const *argv[])
{
    //初始化CUI库
    CUI_init();
    //显示page_main页面
    CUI_page_active(page_main);
    return 0;
}

