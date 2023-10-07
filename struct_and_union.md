# 结构体和联合的标准定义。推荐

        struct 结构体名{ // 声明
            成员变量;
            成员函数；
        };
        struct 结构体名 var1, var2; // 定义
        var1 = {}; // 初始化

        union 联合名{
            成员变量；
            成员函数；
        };
        union 联合名 var1, var2;

# 其他定义

struct 结构体名{ // 声明+定义变量
    成员变量;
    成员函数；
}var1, var2;

union 联合名{
    成员变量；
    成员函数；
}var;
这种情境下，不推荐定义变量的时候同时初始化

# 不加结构体名和联合名

struct { // 声明+定义变量
    成员变量;
    成员函数；
}var1, var2;
// 此时将只存在两个结构体变量。
// 不能自由的定义结构体变量。
// 只能通过var1和var2使用两次该结构体

# 在使用 typedef 进行重命名的时候可以不加结构体名

typedef struct { // 声明+定义变量
    成员变量;
    成员函数；
}新的结构体名;

# 区别

内存占用
  结构体所占内存是全部成员的内存的累加；
  联合体所有成员共享一块地址空间。长度等于最长成员的长度。互斥访问内存。

# 联合使用

1、数据位操作

#include<stdio.h>
typedef struct
{
  unsigned char bit0:1;
  unsigned char bit1:1;
  unsigned char bit2:1;
  unsigned char bit3:1;
  unsigned char bit4:1;
  unsigned char bit5:1;
  unsigned char bit6:1;
  unsigned char bit7:1;
}bitValue;

typedef union
{
  unsigned char bytedata;
  bitValue  bitdata;
}regValue;

int main()
{
  regValue data;

  data.bytedata= 0x5A;
  printf("%d",data.bitdata.bit5);  //读取第6位

  data.bitdata.bit7 = 1;           //修改第8位
  return 0;
}

2、嵌套使用

struct tvFeature    //电视属性
{
   int screensize  //屏幕尺寸
   int resolution  //分辨率
}tvFeature;

struct airFeature  //空调属性
{
   int coldcapacity;//制冷量
   int hotcapacity;//制热量
}airFeature;

struct homeappliancesFeature  //电器属性
{
   char *logo; //品牌
   long country; //国家
   union
   {
      struct tvFeature tvST;
      struct airFeature airST;
   };
};

struct homeappliancesFeature tvfeature;
struct homeappliancesFeature airfeature;

3、串口数据发送

typedef union
{
  uint8   data8[4];
  uint32  data32;
}dataType;

uint32 sendData = 0x5A5AA5A5;
uint32 receiveData;
dataType commSend;

void main(void)
{
    uint8 commData[128];
    //数据复制
    commData.data32 = sendData;
    //发送数据,字节复制,不需要再将commData.data32单独移位拆分
    commData[0]= commSend.data8[0];
    commData[1]= commSend.data8[1];
    commData[2]= commSend.data8[2];
    commData[3]= commSend.data8[3];

    //读取数据时,字节复制,不需要再将已经读取到的4个单字节数据拼接
    receiveData =  commData.data32;
}

4、在同一段通信数据发送逻辑中，针对不同通信协议帧格式进行发送

typedef struct
{
   uint8 head;   //帧头格式相同
   union    //中间数据格式不一样
   {
      struct             //payloadType1
      {
        uint8 cmd;
        uint8 type;
        uint8 data[5];
        uint8 check;
      }msgType1;

      struct              //payloadType2
      {
        uint16 cmd;
        uint8 data[8];
        uint16 check;
      }msgType2;

     uint8 data[10];      //payloadType3
   } payloadType;
   uint8 end;    //帧尾格式相同
}frameType;

# 指针式访问

由于在一个成员长度不同的联合体里，分配给联合体的内存大小取决于它的最大成员的大小。
如果内部成员的大小相差太大，当存储长度较短的成员时，浪费的空间是相当可观的。
在这种情况下，更好的方法是在联合体中存储指向不同成员的指针而不是直接存储成员本身。
所有指针的长度都是相同的，这样能解决内存空间浪费的问题。

#include<stdio.h>
typedef struct
{
  unsigned char a;
  int b;
}stValue1;

typedef struct
{
  int c;
  unsigned char d[10];
  double e;
}stValue2;

//联合体成员定义为指针成员
union Un
{
  stValue1 *ptrSt1;
  stValue2 *ptrSt2;
};

int main()
{
  union Un *info;
  info->ptrSt1->a = 5;
  info->ptrSt2->e = 9.7f;
}
