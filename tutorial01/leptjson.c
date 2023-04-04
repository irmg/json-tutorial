#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

/**
* 断言（assertion）是 C 语言中常用的防御式编程方式，减少编程错误。
* 断言用于检测程序员是否进行了错误编码。
* 最常用的是在函数开始的地方，检测所有参数。有时候也可以在调用函数后，检查上下文是否正确。
*/
#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char* json;
}lept_context;

/* ws = *(%x20 / %x09 / %x0A / %x0D) */
static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

/* null  = "null" */
static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');

    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}



/* true  = "true" */
static int lept_parse_true(lept_context* c, lept_value* v) {
    EXPECT(c, 't');

    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

/* false  = "false" */
static int lept_parse_false(lept_context* c, lept_value* v) {
    EXPECT(c, 'f');

    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}


/* value = null / false / true */
/* 提示：下面代码没处理 false / true，将会是练习之一 */
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);

        case 't':  return lept_parse_true(c, v);
        case 'f':  return lept_parse_false(c, v);

        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}


/**
* 提示：这里应该是 JSON-text = ws value ws   （whitespace）空格
* 以下实现没处理最后的 ws 和 LEPT_PARSE_ROOT_NOT_SINGULAR
* 解析 JSON
* 传入字符串，不能更改，因此使用 const char*
*/
int lept_parse(lept_value* v, const char* json) {
    lept_context c;

    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);

    /**
    * 修正关于 LEPT_PARSE_ROOT_NOT_SINGULAR 的单元测试，若 json 在一个值之后，空白之后还有其它字符，
    * 则要返回 LEPT_PARSE_ROOT_NOT_SINGULAR。
    */
    // 修正也正确
    /*if (lept_parse_value(&c, v) == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (*c.json != "\0")
            return LEPT_PARSE_ROOT_NOT_SINGULAR;
    }  
    return lept_parse_value(&c, v);*/

    //第二种写法

    int ret;
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (*c.json != "\0")
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret; 
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
