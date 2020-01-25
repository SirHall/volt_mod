#include "volt/file/JSONData.hpp"

using namespace volt::file;

JSONData::JSONData(std::string const typeName, std::string const assetName,
                   boost::property_tree::ptree const rootData,
                   const std::filesystem::path       fileLocation)
    : type(typeName), name(assetName), root(rootData), filePath(fileLocation)
{
}

JSONData::JSONData(const JSONData &other)
    : type(other.type), name(other.name), root(other.root),
      filePath(other.filePath)
{
}

JSONData &JSONData::operator=(const JSONData &other)
{
    type     = other.type;
    name     = other.name;
    root     = other.root;
    filePath = other.filePath;
    return *this;
}

JSONData::JSONData(JSONData &&other)
    : type(std::move(other.type)), name(std::move(other.name)),
      root(std::move(other.root)), filePath(std::move(other.filePath))
{
}

JSONData &JSONData::operator=(JSONData &&other)
{
    type     = std::move(other.type);
    name     = std::move(other.name);
    root     = std::move(other.root);
    filePath = std::move(other.filePath);
    return *this;
}

JSONData::~JSONData() {}
