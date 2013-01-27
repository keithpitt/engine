#ifndef _FILE_HPP_
#define _FILE_HPP_

namespace kp {

    namespace file {
        void init(const char* argv0);
        void cleanup();

        const char* read(const char filename[]);
    }

}

#endif
