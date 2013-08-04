#ifndef _STRING_HPP_
#define _STRING_HPP_

#include <string>

namespace kp {

    namespace string {

        std::string vformat(const char* format, va_list ap);
        std::string format(const char* format, ...);

    }

}

#endif
