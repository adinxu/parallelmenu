#include "parallelmenu.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define check 1
Page* current_page;
Option* current_opt;
Page* start_of_pagelist;
char pagenum;
void SetPageNum(int num)
{
    #if check
    if(num>MAX_NUM_OF_PAGE) return;
    #endif // check
    pagenum=num;
    start_of_pagelist=(Page*)malloc(num*sizeof(Page));

}
void SetPage(int num,int optnum,unsigned char* str)
{
    #if check
    if(num>pagenum||num<1) return;
    #endif // check
    optnum++;//加页面名字
    current_page=start_of_pagelist+num-1;
    current_page->optnum=optnum;
    current_page->option=(Option*)malloc(optnum*sizeof(Option));
    current_opt=current_page->option;
    current_opt->flag=(Type)0;
    current_opt->content.str=str;
    current_opt->name=0;

}
SmallNum GetSmallNum(float num)
{
    SmallNum smallnum;
    smallnum.integer=(int)num;
    smallnum.leave=(int)((num-(int)num)*100);
    return smallnum;

}
void SetOptContent(char flag,unsigned char* name,void* content)
{
    #if check
    if(current_opt>=current_page->option+current_page->optnum-1) return;
    #endif // check
    current_opt++;
    current_opt->flag=(Type)flag;
    switch(flag)
    {
        case 0:
        case 3: current_opt->content.str=(unsigned char*)content;break;
        case 1:
        case 4: current_opt->content.num=(int*)content;break;
        case 2:
        case 5: current_opt->content.smallnum=GetSmallNum(*(float*)content);
        default: break;
    }
    current_opt->name=name;

}
void EndPageSet()
{
    current_page=start_of_pagelist;
    current_page->selection=0;
    current_opt=current_page->option;
    _SetPosition();
}


void _SetPosition()
{
    //OLED_Clear();
    char leave=current_page->optnum-current_page->selection;
    if(leave>4) leave=4;
    char i=0;
    for(;i<leave;i++) DrawOpt((OptPosition)i);
    //OLED_Refresh_Gram();
}


void process_KeyAction(KeyValue keyvalue)
{
    switch(keyvalue)
    {
        case keyup: process_optchange(1);break;
        case keydown: process_optchange(0);break;
        case keyleft: process_valuechange(1);break;
        case keyright: process_valuechange(0);break;
        case keyenter: process_Enter();break;
        default: break;
    }
}



void process_optchange(char flag)
{

  if(flag)//上键
  {
    if(current_page->selection==0);
    else current_page->selection--;
  }
  else//下键
  {
    if(current_page->selection==current_page->optnum-1);
    else current_page->selection++;
  }
  current_opt=current_page->option+current_page->selection;//更新
  _SetPosition();//绘制
}//只把current_opt变为选择选项

void process_valuechange(char flag)
{
if(current_page->selection==0)
{
    if(flag)//回退
    {
        if(current_page-start_of_pagelist)
        {
            current_page--;
            current_opt=current_page->option;
            current_page->selection=0;
        }
        else
        {
            current_page=start_of_pagelist+pagenum-1;
            current_opt=current_page->option;
            current_page->selection=0;
        }
    }
    else//确认
    {
        if(current_page-start_of_pagelist<pagenum-1)
        {
            current_page++;
            current_opt=current_page->option;
            current_page->selection=0;
        }
        else
        {
            current_page=start_of_pagelist;
            current_opt=current_page->option;
            current_page->selection=0;
        }
    }
}
    switch(current_opt->flag)
    {
    //case adjustblestr: _adjustblestr(flag);break; //待扩展
    case adjustablenum: _adjustablenum(flag);break;
    case adjustblesmall: _adjustblesmall(flag);break;
    default: break;
    }
_SetPosition();//绘制
}
void process_Enter()
{

}
void _adjustblestr(char flag)
{

}

void _adjustablenum(char flag)
{
    if(flag)//左
    {
      if(*current_opt->content.num) (*current_opt->content.num)--;
    }
    else//右
    {
      if((*current_opt->content.num)<255) (*current_opt->content.num)++;
    }
}
void _adjustblesmall(char flag)
{
  static SmallNum _smallnum;
  _smallnum=current_opt->content.smallnum;
    if(flag)
    {
      if(_smallnum.integer||_smallnum.leave)
      {

          if(!_smallnum.leave)
          {
              _smallnum.integer--;
              _smallnum.leave=99;
          }
          else _smallnum.leave--;
      }
    }

    else
    {
        if((~_smallnum.integer)||(~_smallnum.leave))
      {
          if(_smallnum.leave==99)
          {
              _smallnum.integer++;
              _smallnum.leave=0;
          }
          else _smallnum.leave++;
      }
    }
    current_opt->content.smallnum=_smallnum;
}
//**************************************************************************************//
void switchtokeyvalue()
{
    int ascii=getch();
    system("cls");
    switch(ascii)
    {
    case 'w': process_KeyAction(keyup);break;
    case 'a': process_KeyAction(keyleft);break;
    case 's': process_KeyAction(keydown);break;
    case 'd': process_KeyAction(keyright);break;
    case 'f': process_KeyAction(keyenter);break;
    default: break;
    }
}
void DrawOpt(OptPosition position)//只负责填充数据，不会刷新显示
{
    unsigned char* str;
    if(str=(current_opt+(char)position)->name) printf("%s:",str);
    switch((current_opt+(char)position)->flag)
    {
    case strings: printf("%s\n",(current_opt+(char)position)->content.str);break;
    //case adjustblestr: break;
    case number:
    case adjustablenum: printf("%d\n",*((current_opt+(char)position)->content.num));break;
    case smallnum:
    case adjustblesmall:
        {
            SmallNum _small=(current_opt+(char)position)->content.smallnum;
            printf("%.2f\n",_small.integer+_small.leave*0.01);
        }
        break;
    default:break;
    }
}

