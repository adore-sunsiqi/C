const 定义只读的常量，不允许修改
const int temp = 5;

const int * ptr = array; 
// ptr是常量指针，*ptr 是const int类型。
// 其指向的内容即 *ptr 是不可修改的：*ptr = 56是错误的。但是可以修改array。
// 但是指针本身（指针指向的地址）ptr是可以修改的：ptr = &b是正确的

int * const ptr;
// ptr是指针常量，ptr是int * const类型
// 指针本身 ptr 是不可以修改的：ptr = &b是错误的
// 指针指向的内容是可以修改的： *ptr = 400 是正确的
