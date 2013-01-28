#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

namespace kp {
    
    namespace debug {
    
        void info(const char* message, ...);
        void error(const char* message, ...);
        void fatal(const char* message, ...);
        
    };

}

#endif