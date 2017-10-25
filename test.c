#include "parallelmenu.h"
int main()
{
    int speed=0;
    float pi=13.14;
    SetPageNum(4);
    SetPage(1,3,"oled_show");
    SetOptContent(0,"zaofan","baozi");
    SetOptContent(4,"speed",&speed);
    SetOptContent(5,"pi",&pi);

    SetPage(2,3,"zaofan");
    SetOptContent(0,0,"baozi");
    SetOptContent(0,0,"mantou");
    SetOptContent(0,0,"shengjianbao");

    SetPage(3,3,"wufan");
    SetOptContent(0,0,"baozi");
    SetOptContent(0,0,"mantou");
    SetOptContent(0,0,"shengjianbao");

    SetPage(4,3,"wanfan");
    SetOptContent(0,0,"baozi");
    SetOptContent(0,0,"mantou");
    SetOptContent(0,0,"shengjianbao");
    EndPageSet();

        while(1)
    {
        switchtokeyvalue();
    }

    return 0;

}
