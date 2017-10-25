#ifndef PARALLELMENU_H_INCLUDED
#define PARALLELMENU_H_INCLUDED

#define MAX_NUM_OF_PAGE 24

typedef enum//键值枚举变量
{
  keyup,
  keydown,
  keyleft,
  keyright,
  keyenter
}KeyValue;
typedef enum //屏幕位置枚举变量
{
  fristline,
  secondline,
  thirdline,
  fourthline
}OptPosition;
typedef enum
{
    strings,//0
    number,//1
    smallnum,//2
    adjustblestr,//3
    adjustablenum,//4
    adjustblesmall//5
}Type;
struct _SmallNum
{
    int integer;
    unsigned char leave;
};
union optcontent
{
    unsigned char* str;
    int* num;
    struct _SmallNum smallnum;
};
struct _Page
{
    char optnum;//选项数目
    struct _Option* option;//本页选项结构体数组指针
    char selection;//当前选中的选项标号，从0开始计数
};

struct _Option
{
  Type flag;//用作标识普通选项与可调整选项的标志位  0普通 1可调整
  unsigned char* name;
  union optcontent content;
};

  typedef struct _Page Page;
  typedef struct _Option Option;
  typedef struct _SmallNum SmallNum;


void SetPageNum(int num);
void SetPage(int num,int optnum,unsigned char* str);
void SetOptContent(char flag,unsigned char* name,void* content);
void EndPageSet();

void _SetPosition();

void process_KeyAction(KeyValue keyvalue);

void process_optchange(char flag);
void process_valuechange(char flag);
void process_Enter();

void _adjustblestr(char flag);
void _adjustablenum(char flag);
void _adjustblesmall(char flag);

void DrawOpt(OptPosition position);

void switchtokeyvalue();
#endif // PARALLELMENU_H_INCLUDED
