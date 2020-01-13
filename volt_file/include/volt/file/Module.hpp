#pragma once
#ifndef VOLT_FILE_MODULE_HPP
#define VOLT_FILE_MODULE_HPP

#include "volt/file/JSONData.hpp"

#include <string>
#include <vector>

namespace volt::file
{
    class Module
    {
    private:
        const std::vector<JSONData>    jsonObjs;
        const std::string              moduleName;
        const std::vector<std::string> dependencies;
        const std::string              version;
        const std::string              softwareVersion;
        const std::string              author;
        const std::string              site;
        const std::string              repository;

    protected:
    public:
        Module(std::vector<JSONData> jsonObjects, std::string name,
               std::vector<std::string> deps, std::string moduleVersion,
               std::string targetSoftwareVersion, std::string authorName,
               std::string siteURL, std::string repositoryURL);
        Module(const Module &other);
        Module(Module &&other);
        ~Module();

        inline std::vector<JSONData> const &GetAutoloadJSONs()
        {
            return this->jsonObjs;
        }

        inline std::string const &GetModuleName() { return this->moduleName; }

        inline std::vector<std::string> const &GetDependencies()
        {
            return this->dependencies;
        }

        inline std::string const &GetVersion() { return this->version; }

        inline std::string const &GetTargetVersion()
        {
            return this->softwareVersion;
        }

        inline std::string const &GetAuthor() { return this->author; }

        inline std::string const &GetSite() { return this->site; }

        inline std::string const &GetRepository() { return this->repository; }
    };

} // namespace volt::file
#endif
