#include "volt/file/JSONLoader.hpp"

#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

using namespace volt::file;

JSONLoader::JSONLoader() {}

JSONLoader::JSONLoader(const JSONLoader &other) {}

JSONLoader &JSONLoader::operator=(const JSONLoader &other) { return *this; }

JSONLoader::JSONLoader(JSONLoader &&other) {}

JSONLoader &JSONLoader::operator=(JSONLoader &&other) { return *this; }

JSONLoader::~JSONLoader() {}

std::vector<Module>
    JSONLoader::LoadModuleCollection(std::string const &collectionDir)
{
    auto modules = std::vector<Module>();

    // If this isn't a directory, just return an empty vector
    if (!std::filesystem::is_directory(collectionDir))
        return modules;

    for (auto &dir :
         std::filesystem::recursive_directory_iterator(collectionDir))
    {
        std::error_code err;
        if (dir.exists(err))
        {
            // This directory exists
            if (err)
            {
                throw std::runtime_error("Error occurred while trying to read "
                                         "file/directory: '" +
                                         dir.path().generic_string() +
                                         "': " + err.message());
                // Just incase we compile without exceptions
                return modules;
            }

            // Is this a directory
            if (dir.is_directory() &&
                LoadModule(dir.path().generic_string(), modules))
            {
                // This should be a module, attempt to load it
            }
        }
    }
    return modules;
}

bool JSONLoader::LoadModule(std::string const &  moduleDir,
                            std::vector<Module> &modules)
{
    if (!std::filesystem::is_directory(moduleDir))
        return false;

    for (auto &dir : std::filesystem::recursive_directory_iterator(moduleDir))
    {
        if (dir.is_regular_file() && dir.path().has_filename() &&
            dir.path().filename() == "module.json")
        {
            // This is a module, load it

            auto moduleFileRoot = boost::property_tree::ptree();
            boost::property_tree::read_json(dir.path().generic_string(),
                                            moduleFileRoot);

            // Loaded the file, now find the mandatory labels

            auto moduleName =
                moduleFileRoot.get_optional<std::string>("moduleName");
            if (!moduleName.has_value())
            {
                // This module should have a name
                // TODO: Use some way of nicely reporting this
                continue;
            }

            // Which other modules must be loaded before this one (Primarily for
            // scripts)
            auto moduleDependenciesVec = std::vector<std::string>();
            auto moduleDependencies =
                moduleFileRoot.get_child_optional("dependencies");
            if (moduleDependencies.has_value())
            {
                for (auto &dep : moduleDependencies.value())
                {
                    auto depVal = dep.second.get_value_optional<std::string>();
                    if (depVal.has_value())
                        moduleDependenciesVec.push_back(depVal.value());
                }
            }

            // Which version of the game this module is supposed to be
            // compatible with
            auto moduleTargetVersion =
                moduleFileRoot.get_optional<std::string>("targetVersion");

            auto moduleAuthor =
                moduleFileRoot.get_optional<std::string>("author");
            auto moduleVersion =
                moduleFileRoot.get_optional<std::string>("version");
            auto moduleSite = moduleFileRoot.get_optional<std::string>("site");
            auto moduleRepository =
                moduleFileRoot.get_optional<std::string>("repository");

            // Now load all JSON objects recursively

            auto jsonObjects = std::vector<JSONData>();

            RecursiveLoadDir(moduleDir, jsonObjects);

            // Add the new module to the list of modules
            modules.push_back(
                Module(jsonObjects, moduleName.value_or("NULL"),
                       moduleDependenciesVec, moduleVersion.value_or("0.0.0"),
                       moduleTargetVersion.value_or("0.0.0"),
                       moduleAuthor.value_or(""), moduleSite.value_or(""),
                       moduleRepository.value_or("")));

            break;
        }
    }
    return true;
}

bool JSONLoader::RecursiveLoadDir(std::string const &    loadDir,
                                  std::vector<JSONData> &jsonObjects)
{
    if (!std::filesystem::is_directory(loadDir))
        return false;

    for (auto &dir : std::filesystem::recursive_directory_iterator(loadDir))
    {
        if (dir.is_directory())
        {
            // RecursiveLoadDir(dir.path().generic_string(), jsonObjects);
        }
        else if (dir.is_regular_file())
        {
            // Load the single JSON file (Don't read module.json files)
            if (dir.path().has_filename() && dir.path().has_extension() &&
                (dir.path().extension() == ".json") &&
                (dir.path().filename() != "module.json"))
            {
                // This is a json data, attempt to load it
                //--- START READING JSON ASSET FILE ---//
                auto fileRoot = boost::property_tree::ptree();
                boost::property_tree::read_json(dir.path().generic_string(),
                                                fileRoot);

                // Loaded the file, now find the mandatory labels

                // Firstly, is this json file supposed to be auto-loaded as
                // an asset?
                auto isJsonObjectAnAsset =
                    fileRoot.get_optional<bool>("__autoload_asset__");
                if (!isJsonObjectAnAsset.value_or(false))
                {
                    // This json object should not be auto-loaded, skip it
                    continue;
                }

                auto jsonType = fileRoot.get_optional<std::string>("type");
                if (!jsonType.has_value())
                {
                    throw std::runtime_error(
                        "Autoloaded JSON file has no 'type' field: " +
                        dir.path().generic_string());
                    continue;
                }

                auto assetName = fileRoot.get_optional<std::string>("name");
                if (!assetName.has_value())
                {
                    throw std::runtime_error(
                        "Autoloaded JSON file has no 'type' field: " +
                        dir.path().generic_string());
                    continue;
                }

                // Now create the json object and push it onto the vector
                jsonObjects.push_back(
                    JSONData(jsonType.value(), assetName.value(), fileRoot));
            }
        }
    }

    return true;
}