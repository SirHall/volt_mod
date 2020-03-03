#pragma once
#ifndef VOLT_FILE_JSONLOADER_HPP
#define VOLT_FILE_JSONLOADER_HPP

#include "volt/file/JSONData.hpp"
#include "volt/file/Module.hpp"
#include "volt/file/ModuleJar.hpp"

#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace volt::file
{

    class JSONLoader
    {
    private:
        boost::asio::thread_pool thr_pool;

    protected:
    public:
        JSONLoader();
        JSONLoader(const JSONLoader &other);
        JSONLoader &operator=(const JSONLoader &other);
        JSONLoader(JSONLoader &&other);
        JSONLoader &operator=(JSONLoader &&other);
        ~JSONLoader();

        ModuleJar LoadModuleCollection(std::string const &collectionDir);

        bool LoadModule(std::string const &  moduleDir,
                        std::vector<Module> &modules);

        bool RecursiveLoadDir(std::string const &    loadDir,
                              std::vector<JSONData> &jsonObjects);
    };

} // namespace volt::file
#endif
