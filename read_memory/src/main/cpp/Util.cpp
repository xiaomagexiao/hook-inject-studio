#include "Util.h"
#include "cxxabi.h"
#include "StackCallBack.h"

string Util::ENTER_LINE("\r\n");
string Util::TABLE_LINE("\t");
string Util::FUNCTION_TAG("SYM");
bool Util::FUNCTION_ENCRYPT = true;

void *Util::pe_malloc(unsigned long size) {
    void *ptr;
    ptr = malloc(size);
    if (!ptr && size)
        cout << "memory full" << endl;
    return ptr;
}

void Util::pe_free(void *ptr) {
    free(ptr);
}

void *Util::pe_mallocz(unsigned long size) {
    void *ptr;
    ptr = pe_malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

void *Util::pe_realloc(void *ptr, unsigned long size) {
    void *ptr1 = realloc(ptr, size);
    return ptr1;
}

void *Util::load_data(int fd, unsigned long file_offset, unsigned long size) {
    void *data;
    data = pe_malloc(size);
    lseek(fd, file_offset, SEEK_SET);
    read(fd, data, size);
    return data;
}

int Util::write_to_file(int fd, unsigned long file_offset, void *ptr, int size) {
    lseek(fd, file_offset, SEEK_SET);
    cout << "[!] write: offset " << hex << file_offset << ", size " << size << endl;
    int result = write(fd, ptr, size);
    assert(result == size);
    return result;
}

void Util::saveFile(const string &fileFullPath, const string &str) {
    ofstream out(fileFullPath.c_str(),
                 ios::out | ios::app); //ofstream out("out.txt",ios::out | ios::app);
    out << str << endl;
    out.close();
}

void
Util::readFile(const string &fileFullPath, vector<string> &vec, bool excludeBlankLine, bool trim) {
    ifstream inFile;
    inFile.open(fileFullPath.c_str(), ios::in);
    if (!inFile) {
        cout << "文件不存在： " << fileFullPath << endl;
        return;
    }
    char buffer[256];
    while (!inFile.eof()) {
        inFile.getline(buffer, 256, '\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束
        string temp = buffer;
        replaceEnterLine(temp);
        if (trim) {
            string_trim(temp);
        }
        if (excludeBlankLine && temp.empty()) {
            continue;
        }
        vec.push_back(temp);
    }
    inFile.close();
}

void Util::getAllFormatFiles(string path, vector<string> &files, string format) {

    /* DIR *dir = opendir(path.c_str());//打开指定目录
     dirent *p = NULL;//定义遍历指针
     while ((p = readdir(dir)) != NULL)//开始逐个遍历
     {
         //这里需要注意，linux平台下一个目录中有"."和".."隐藏文件，需要过滤掉
         if (p->d_name[0] != '.')//d_name是一个char数组，存放当前遍历到的文件名
         {
             string name = string(p->d_name);
             if (name.find("." + format) != string::npos) {
                 files.push_back(name);
             }
         }
     }
     closedir(dir);//关闭指定目录*/
    string cmd = "find " + path + " -name '*." + format + "'";
    executeCmdWithResult(cmd, files);
}

void Util::deleteFolder(const string &fullpath) {
    executeCmd("rm -rf " + fullpath);
}

void Util::createFolder(const string &fullpath) {
    executeCmd("mkdir -p " + fullpath);
}

string Util::getNameByFullpath(const string &fullPath) {
    assert(fullPath.length());
    return fullPath.substr(fullPath.find_last_of("/") + 1, fullPath.length());
}

string Util::string_replace(const string &s1, const string &s2, const string &s3) {
    string::size_type pos = 0;
    string::size_type a = s2.size();
    string::size_type b = s3.size();
    string result = s1;
    while ((pos = result.find(s2, pos)) != string::npos) {
        result.replace(pos, a, s3);
        pos += b;
    }
    return result;
}

void Util::string_trim(string &s) {
    if (s.empty()) {
        return;
    }
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
}

//字符串分割函数
vector<string> Util::string_split(string str,string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

bool Util::string_start_with(const string &mainstr, const string &substr) {
    return mainstr.find(substr) == 0;
}

void Util::replaceEnterLine(string &temp) {
    temp = string_replace(temp, "\n", "");
    temp = string_replace(temp, "\r", "");
}

void Util::executeCmd(const string &cmd) {
    checkCmdLength(cmd);
    cout << "[!] cmd : " << cmd << endl;
    int result = system(cmd.c_str());
    if (result) {
        cout << "[!] execute error!!! - " << result << endl;
    }

    StackCallBack::backtraceToLogcat();
}

void Util::executeCmdWithResult(const string &cmd, vector<string> &vec) {
    FILE *fpRead = popen(cmd.c_str(), "r");
    char buf[1024] = {0};
    while (fgets(buf, 1024 - 1, fpRead) != NULL) {
        string temp(buf);
        replaceEnterLine(temp);
        vec.push_back(temp);
    }
    if (fpRead != NULL)
        pclose(fpRead);
}

string Util::CxxDemangle(const char *symbol) {
    size_t size;
    int status;
    char *demangled;
    if (NULL != (demangled = abi::__cxa_demangle(symbol, NULL, &size, &status))) {
        string result(demangled);
        free(demangled);
        return result;
    } else {
        return string(symbol);
    }
}

static unsigned int MAX_CMD_LENGTH = 0;

void Util::checkCmdLength(const string &cmd) {
    /* if (!MAX_CMD_LENGTH) {
         vector<string> result;
         executeCmdWithResult("getconf ARG_MAX", result);
         MAX_CMD_LENGTH = atoi(result[0].c_str());
         for (vector<string>::iterator iter = result.begin(); iter != result.end(); iter++) {
             cout << *iter << endl;
         }
         cout << "CMD max length: " << result[0] << ", " << MAX_CMD_LENGTH << endl;
     }
     assert(cmd.length() < MAX_CMD_LENGTH);
     */
}