#ifndef ASTRING_H
#define ASTRING_H

#include <malloc.h>

namespace AbyssCore{
    class AString{
        private:
            char* _str;
            int length;

        public:
            AString();
            AString(const char* str);

            char* ToChars();
            int Length();

        public:
            AString& operator=(const char* astr);
    };
}

#endif