#include "volt/mod/Module.hpp"

#include <algorithm>
#include <functional>

using namespace volt::mod;

Module::Module(std::vector<JSONData> jsonObjects, std::string name,
               std::vector<std::string> deps,
               std::vector<std::string> loadAfterModules,
               //    std::vector<std::string> loadBeforeModules,
               std::string moduleVersion, std::string targetSoftwareVersion,
               std::string authorName, std::string siteURL,
               std::string repositoryURL)
    : jsonObjs(jsonObjects), moduleName(name), dependencies(deps),
      loadAfter(loadAfterModules),
      //   loadBefore(loadBeforeModules),
      version(moduleVersion), softwareVersion(targetSoftwareVersion),
      author(authorName), site(siteURL), repository(repositoryURL)
{
}

Module::Module(const Module &other)
    : jsonObjs(other.jsonObjs), moduleName(other.moduleName),
      loadAfter(other.loadAfter), dependencies(other.dependencies),
      version(other.version), softwareVersion(other.softwareVersion),
      author(other.author), site(other.site), repository(other.repository)
{
}

Module &Module::operator=(const Module &other)
{
    jsonObjs        = other.jsonObjs;
    moduleName      = other.moduleName;
    loadAfter       = other.loadAfter;
    dependencies    = other.dependencies;
    version         = other.version;
    softwareVersion = other.softwareVersion;
    author          = other.author;
    site            = other.site;
    repository      = other.repository;
    return *this;
}

Module::Module(Module &&other)
    : jsonObjs(std::move(other.jsonObjs)),
      moduleName(std::move(other.moduleName)),
      dependencies(std::move(other.dependencies)),
      loadAfter(std::move(other.loadAfter)), version(std::move(other.version)),
      softwareVersion(std::move(other.softwareVersion)),
      author(std::move(other.author)), site(std::move(other.site)),
      repository(std::move(other.repository))
{
}

Module &Module::operator=(Module &&other)
{
    jsonObjs        = std::move(other.jsonObjs);
    moduleName      = std::move(other.moduleName);
    loadAfter       = std::move(other.loadAfter);
    dependencies    = std::move(other.dependencies);
    version         = std::move(other.version);
    softwareVersion = std::move(other.softwareVersion);
    author          = std::move(other.author);
    site            = std::move(other.site);
    repository      = std::move(other.repository);
    return *this;
}

Module::~Module() {}
