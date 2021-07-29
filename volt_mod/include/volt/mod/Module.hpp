#pragma once
#ifndef VOLT_MOD_MODULE_HPP
#define VOLT_MOD_MODULE_HPP

#include "volt/mod/JSONData.hpp"

#include <string>
#include <utility>
#include <vector>

namespace volt::mod
{

    enum ModuleOrganizationStatus
    {
        Successful,
        MissingDependency,
        DependencyLoop
    };

    class Module
    {
    private:
        std::vector<JSONData>    jsonObjs;
        std::string              moduleName;
        std::vector<std::string> dependencies;
        // std::vector<std::string> loadBefore;
        std::vector<std::string> loadAfter;
        std::string              version;
        std::string              softwareVersion;
        std::string              author;
        std::string              site;
        std::string              repository;

    public:
        Module(std::vector<JSONData> jsonObjects, std::string name, std::vector<std::string> deps,
               std::vector<std::string> loadAfterModules,
               //    std::vector<std::string> loadBeforeModules,
               std::string moduleVersion, std::string targetSoftwareVersion, std::string authorName,
               std::string siteURL, std::string repositoryURL);
        Module(const Module &other);
        Module &operator=(const Module &other);
        Module(Module &&other);
        Module &operator=(Module &&other);

        ~Module();

        inline std::vector<JSONData> const &GetAutoloadJSONs() const { return this->jsonObjs; }

        inline std::string const &GetModuleName() const { return this->moduleName; }

        inline std::vector<std::string> const &GetDependencies() const { return this->dependencies; }

        inline std::string const &GetVersion() const { return this->version; }

        inline std::string const &GetTargetVersion() const { return this->softwareVersion; }

        inline std::string const &GetAuthor() const { return this->author; }

        inline std::string const &GetSite() const { return this->site; }

        inline std::string const &GetRepository() const { return this->repository; }

        inline std::vector<std::string> const &GetLoadAfter() const { return this->loadAfter; }

        // inline std::vector<std::string> const &GetLoadBefore() const
        // {
        //     return this->loadBefore;
        // }
    };

} // namespace volt::mod
#endif
