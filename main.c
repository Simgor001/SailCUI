#include "SailCUI.h"
#include "page.h"

CUI_err CUI_main(int argc, char const *argv[])
{
    //��ʼ��CUI��
    CUI_init();
    //��ʾpage_mainҳ��
    CUI_page_active(page_main);
    return 0;
}

