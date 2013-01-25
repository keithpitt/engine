#ifndef _FILE_HPP_
#define _FILE_HPP_

namespace kp {

    class File {
        
    public:
        
        static const char* read(const char filename[]);
        static const char* join(const char start[], const char end[]);
        static const char* wd();
        
        const char* filename;
        
        File(const char* filename);
        
        const char* path();
        const char* read();
        
    };

}

#endif