#include "volt/file/Module.hpp"

using namespace volt::file;

Module::Module(std::vector<JSONData> jsonObjects, std::string name,
               std::vector<std::string> deps, std::string moduleVersion,
               std::string targetSoftwareVersion, std::string authorName,
               std::string siteURL, std::string repositoryURL)
    : jsonObjs(jsonObjects), moduleName(name), dependencies(deps),
      version(moduleVersion), softwareVersion(targetSoftwareVersion),
      author(authorName), site(siteURL), repository(repositoryURL)
{
}

Module::Module(const Module &other)
    : jsonObjs(other.jsonObjs), moduleName(other.moduleName),
      dependencies(other.dependencies), version(other.version),
      softwareVersion(other.softwareVersion), author(other.author),
      site(other.site), repository(other.repository)
{
}

Module::Module(Module &&other)
    : jsonObjs(std::move(other.jsonObjs)),
      moduleName(std::move(other.moduleName)),
      dependencies(std::move(other.dependencies)),
      version(std::move(other.version)),
      softwareVersion(std::move(other.softwareVersion)),
      author(std::move(other.author)), site(std::move(other.site)),
      repository(std::move(other.repository))
{
}

Module::~Module() {}
