/**
* ����������ֹͷ�ļ��ظ���ϰ���� _H__ ��β��
* �����Ŀ�ж���ļ���Ŀ¼�ṹ�������� ��Ŀ����_Ŀ¼_�ļ����� _H__ ����������ʽ
*/
#ifndef LEPTJSON_H__
#define LEPTJSON_H__  

//ö����������  {ö��ֵ} ö����������
//typedef ������������һ���µ����֣������Ǵ����µ����͡��� lept_type Ϊ���������
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

typedef struct {
    lept_type type;
}lept_value;

enum {
    LEPT_PARSE_OK = 0,  //�޴��󷵻�
    LEPT_PARSE_EXPECT_VALUE,  //��һ�� JSON ֻ���пհף����� LEPT_PARSE_EXPECT_VALUE
    LEPT_PARSE_INVALID_VALUE,  //��һ�� JSON ֻ���пհף����� LEPT_PARSE_EXPECT_VALUE
    LEPT_PARSE_ROOT_NOT_SINGULAR  //��ֵ��������������ֵ������ LEPT_PARSE_INVALID_VALUE
};

//���� JSON
//�����ַ��������ܸ��ģ����ʹ�� const char*
int lept_parse(lept_value* v, const char* json);

//���ʽ���ĺ��������ǻ�ȡ������
lept_type lept_get_type(const lept_value* v);
#endif /* LEPTJSON_H__ */
