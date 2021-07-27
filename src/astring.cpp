#include <astring.h>

namespace AbyssCore{
    AString::AString(){
        _str = nullptr;
        length = 0;
    }

    AString::AString(const char* str){
        int length = 0;

        while(str[length] != '\0'){
            length++;
        }

        _str = (char*)malloc(sizeof(char) * (length + 1));

        for(int i = 0; i < length; i++){
            _str[i] = str[i];
        }

        _str[length] = '\0';

        this->length = length;
    }

    const char* AString::ToChars(){
        return _str;
    }

    int AString::Length(){
        return length;
        // if(_str == nullptr)
        //     return -1;

        // int count = 0;

        // while(*(_str + count) != '\0'){
        //     count++;
        // }

        // return count;
    }

    AString& AString::operator=(const char* str){
        int length = 0;

        while(str[length] != '\0'){
            length++;
        }

        _str = (char*)realloc(_str, sizeof(char) * (length + 1));

        for(int i = 0; i < length; i++){
            _str[i] = str[i];
        }

        _str[length] = '\0';

        this->length = length;

        return *this;
    }
}