/**
* 宏声明：防止头文件重复。习惯以 _H__ 结尾。
* 如果项目有多个文件或目录结构，可以用 项目名称_目录_文件名称 _H__ 这种命名方式
*/
#ifndef LEPTJSON_H__
#define LEPTJSON_H__  
//枚举数据类型  {枚举值} 枚举数据类型
//typedef 赋予现有类型一个新的名字，而不是创造新的类型。如 lept_type 为替代的名字
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

typedef struct {
    lept_type type;
}lept_value;

enum {
    LEPT_PARSE_OK = 0,  //无错误返回
    LEPT_PARSE_EXPECT_VALUE,  //若一个 JSON 只含有空白，传回 LEPT_PARSE_EXPECT_VALUE
    LEPT_PARSE_INVALID_VALUE,  //若值不是null、false、true三种字面值，传回 LEPT_PARSE_INVALID_VALUE
    LEPT_PARSE_ROOT_NOT_SINGULAR  //若一个值之后，在空白之后还有其他字符，传回 LEPT_PARSE_ROOT_NOT_SINGULAR
};

//解析 JSON
//传入字符串，不能更改，因此使用 const char*
int lept_parse(lept_value* v, const char* json);

//访问结果的函数，就是获取其类型
lept_type lept_get_type(const lept_value* v);
#endif /* LEPTJSON_H__ */
