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

std::vector<JSONData>
    JSONLoader::LoadModuleCollection(std::string const &collectionDir)
{
    auto jsonObjects = std::vector<JSONData>();

    // If this isn't a directory, just return an empty vector
    if (!std::filesystem::is_directory(collectionDir))
        return jsonObjects;

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
                return jsonObjects;
            }

            // Is this a directory
            if (dir.is_directory() &&
                RecursiveLoadDir(dir.path().generic_string(), jsonObjects))
            {
                // This should be a module, attempt to load it
            }
        }
    }
}

bool JSONLoader::RecursiveLoadDir(std::string const &    loadDir,
                                  std::vector<JSONData> &jsonObjects)
{
    if (!std::filesystem::is_directory(loadDir))
        return false;

    for (auto &dir : std::filesystem::recursive_directory_iterator(loadDir))
    {
        if (dir.is_directory() &&
            RecursiveLoadDir(dir.path().generic_string(), jsonObjects))
        {}
        else if (dir.is_regular_file())
        {
            // Load the single JSON file
            if (dir.path().has_filename() && dir.path().has_extension() &&
                (dir.path().extension() == "json"))
            {
                // This is a json data, attempt to load it
                //--- START READING JSON ASSET FILE ---//
                auto fileRoot = boost::property_tree::ptree();
                boost::property_tree::read_json(dir.path().generic_string(),
                                                fileRoot);

                // Loaded the file, now find the mandatory labels

                // Firstly, is this json file supposed to be auto-loaded as an
                // asset?
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