/**
 * @file unittest.h
 * @VisualGMQ
 * @brief 一个小的单元测试系统
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __UNITTEST_H__
#define __UNITTEST_H__
#include <stdio.h>
#include <string.h>
#include <math.h>
#define ESP 0.0001

static unsigned int __unittest_success_num = 0;
static unsigned int __unittest_totle = 0;

/**
 * @brief 用于判断表达式exp与result是否相等
 */
#define ADD_TEST_TRUE(name, exp, result) \
__unittest_totle++;\
if(exp==result){    \
    printf("[%s]: <expression> 「%s==%s」    test success\t\t✔️\n", name, #exp, #result);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: <expression> 「%s==%s」    test failed\t\t❌\n", name, #exp, #result); \
}

/**
 * @brief 用于判断任意的结构在内存上是否相等
 */
#define ADD_TEST_EQUALOBJ(name, obj1, obj2) \
__unittest_totle++;\
if(memcmp(&obj1, &obj2, sizeof(obj1))==0){    \
    printf("[%s]: <object> 「%s==%s」    test success\t\t✔️\n", name, #obj1, #obj2);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: <object> 「%s==%s」    test failed\t\t❌\n", name, #obj1, #obj2); \
}

#define ADD_TEST_FALSEF(name, exp, result) \
__unittest_totle++;\
if(fabs(exp, result)>ESP){    \
    printf("[%s]: <expression> 「%s!=%s」    test success\t\t✔️️️️\n", name, #exp, result);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: <expression> 「%s!=%s」    test failed\t\t❌\n", name, #exp, result); \
}

/**
 * @brief 用于判断表达式exp和result是否不等
 */
#define ADD_TEST_FALSE(name, exp, result) \
__unittest_totle++;\
if(exp!=result){    \
    printf("[%s]: <expression> 「%s!=%s」    test success\t\t✔️️️️\n", name, #exp, result);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: <expression> 「%s!=%s」    test failed\t\t❌\n", name, #exp, result); \
}

/**
 * @brief 用于判断浮点数表达式exp和result是否不等
 */
#define ADD_TEST_FALSEF(name, exp, result) \
__unittest_totle++;\
if(fabs(exp, result)>ESP){    \
    printf("[%s]: <expression> 「%s!=%s」    test success\t\t✔️️️️\n", name, #exp, result);    \
    __unittest_success_num++;   \
}else{  \
    printf("[%s]: <expression> 「%s!=%s」    test failed\t\t❌\n", name, #exp, result); \
}

/**
 * @brief 用于判断函数func的输出和result是否相等
 */
#define ADD_OUTPUT_TEST(name, func, result) \
{\
    int i = 0;\
    __unittest_totle++;\
    char buffer[1024] = {0};\
    setbuf(stdout, buffer);\
    func;\
    fflush(stdout);\
    setbuf(stdout, NULL);\
    for(i=0;i<strlen(buffer);i++)\
        putchar('\b');\
    if(strcmp(buffer, result) == 0){\
        printf("[%s]: <output> 「%s」    test success\t\t✔️\n", name, buffer);    \
        __unittest_success_num++;   \
    }else{\
        printf("[%s]: <output> 「%s」    test failed\t\t❌\n", name, buffer); \
    }\
    fflush(stdout);\
}

/**
 * @brief 用来显示最后测试结果的宏
 * @warn 这个宏最好放在main()函数的底部，在所有测试用例都编写完之后再使用
 */
#define TEST_SHOW_STATISTICS() printf("\n----------test result----------:\n\
totle num:     %d\n\
success num:   %d\n\
rate:          %.0f%%\n", __unittest_totle, __unittest_success_num, (float)__unittest_success_num/__unittest_totle*100);

/**
 * @brief 用于暂停控制台输出，让测试者可以看到测试结果
 * @warn 这个宏可以放在所有测试语句的最后面。
 */
#define TEST_PAUSE_CONSOLE() \
printf("\n================================\npress enter to exit\n");\
getchar();

#endif