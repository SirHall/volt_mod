#pragma once
#ifndef VOLT_FILE_LOADER_HPP
#define VOLT_FILE_LOADER_HPP

namespace volt::file{

    class Loader 
    {
    private:

    protected:

    public:
        Loader();
        Loader(const Loader &other);
        Loader &operator=(const Loader &other);
        Loader(Loader &&other);
        Loader &operator=(Loader &&other);
        ~Loader();
    };
    
} // namespace volt::file
#endif
