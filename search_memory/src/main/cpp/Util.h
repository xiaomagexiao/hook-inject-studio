#ifndef elf_util_h
#define elf_util_h

#include "Common.h"

/**
 * 工具类，提供全局变量和静态工具函数
 */
class Util {
public:
    static string ENTER_LINE;
    static string TABLE_LINE;
    static string FUNCTION_TAG;
    static bool FUNCTION_ENCRYPT;

    //===========================内存操作===============================//
    /**
     * malloc
     * @param size 大小
     * @return void *
     */
    static void *pe_malloc(unsigned long size);

    /**
     * free
     * @param ptr  指针
     */
    static void pe_free(void *ptr);

    /**
     * malloc同时清空
     * @param size 大小
     * @return void *
     */
    static void *pe_mallocz(unsigned long size);

    /**
     * realloc，重新扩大内存
     * @param ptr 指针
     * @param size 新大小
     * @return 新的指针
     */
    static void *pe_realloc(void *ptr, unsigned long size);

    //===========================文件操作===============================//
    /**
     * 申请内存，从文件指定偏移读取指定大小的字节到该内存
     * @param fd  句柄
     * @param file_offset 文件偏移
     * @param size 大小
     * @return 指针
     */
    static void *load_data(int fd, unsigned long file_offset, unsigned long size);

    /**
     * 把某大小的数据写入的指定文件偏移
     * @param fd 句柄
     * @param file_offset 文件偏移
     * @param ptr  输入内容指针
     * @param size 大小
     * @return 写入的大小
     */
    static int write_to_file(int fd, unsigned long file_offset, void *ptr, int size);

    /**
     * 字符串保存到文件
     * @param fileFullPath
     * @param str
     */
    static void saveFile(const string &fileFullPath, const string &str);

    /**
     * 从文件读取内容，保存到vector里
     * @param fileFullPath
     * @param vec 引用，输入的存储容器
     * @param excludeBlankLine 是否排除空白行
     * @param trim 是否trim
     */
    static void readFile(const string &fileFullPath, vector<string> &vec, bool excludeBlankLine, bool trim);

    /**
    * 获取指定路径下的指定格式文件
    * @param path 路径
    * @param files 输入的存储容器
    * @param format 文件格式，如txt
    */
    static void getAllFormatFiles(string path, vector<string> &files, string format);

    /**
     * 删除文件夹
     * @param fullpath 文件夹全路径
     */
    static void deleteFolder(const string &fullpath);

    /**
     * 创建文件夹
     * @param fullpath 文件夹全路径
     */
    static void createFolder(const string &fullpath);

    /**
     * 通过路径获取名字
     * @param fullPath 全路径
     * @return 名字
     */
    static string getNameByFullpath(const string &fullPath);

    //===========================字符串操作===============================//
    /**
     * 字符串替换
     * @param s1 输入的字符串
     * @param s2  匹配的字符串
     * @param s3  替换的字符串
     * @return 结果字符串，是个新的
     */
    static string string_replace(const string &s1, const string &s2, const string &s3);

    /**
     * 字符串去除前后空格
     * @param s 要去除的字符串，该输入字符串会被直接修改
     */
    static void string_trim(string &s);

    /**
     * 字符串切割
     * @param str 原始字符串的副本
     * @param pattern 要切割的内容
     * @return 切割后结果
     */
    static vector<string> string_split(string str, string pattern);

    /**
     * 以某字符串开头
     * @param mainstr 主串
     * @param substr 子串
     * @return bool
     */
    static bool string_start_with(const string &mainstr, const string &substr);

    /**
     * 替换回车、换行符
     * @param temp 要处理的字符串，同时也是结果
     */
    static void replaceEnterLine(string &temp);

    //===========================其他===============================//
    /**
     * 指定shell命令
     * @param cmd 命令内容
     */
    static void executeCmd(const string &cmd);

    /**
     * 执行shell，获取返回结果
     * @param cmd shell内容
     * @param vec 存储结果容器
     */
    static void executeCmdWithResult(const string &cmd, vector<string> &vec);

    /**
     * md5
     * @param str 字符串
     * @return 结果
     */
    static string createMD5Str(const string &str);

    /**
     * 通过符号表获取函数真正声明，类似c++filt
     * @param symbol 符号表信息
     * @return 函数原型字符串
     */
    static string CxxDemangle(const char *symbol);

private:
    static void checkCmdLength(const string &cmd);


};

#endif