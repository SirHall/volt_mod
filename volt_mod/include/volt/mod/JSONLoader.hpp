#pragma once
#ifndef VOLT_MOD_JSONLOADER_HPP
#define VOLT_MOD_JSONLOADER_HPP

#include "volt/mod/JSONData.hpp"
#include "volt/mod/Module.hpp"
#include "volt/mod/ModuleJar.hpp"

#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace volt::mod
{

    class JSONLoader
    {
    private:
        // boost::asio::thread_pool thr_pool;

    protected:
    public:
        JSONLoader();
        // JSONLoader(const JSONLoader &other);
        // JSONLoader &operator=(const JSONLoader &other);
        // JSONLoader(JSONLoader &&other);
        // JSONLoader &operator=(JSONLoader &&other);
        // ~JSONLoader();

        ModuleJar LoadModuleCollection(std::string const &collectionDir);

        bool LoadModule(std::string const &moduleDir, std::vector<Module> &modules);

        bool RecursiveLoadDir(std::string const &loadDir, std::vector<JSONData> &jsonObjects);
    };

} // namespace volt::mod
#endif
