#include "volt/file/JSONData.hpp"

using namespace volt::file;

JSONData::JSONData(std::string const typeName, std::string const assetName,
                   boost::property_tree::ptree const rootData)
    : type(typeName), name(assetName), root(rootData)
{
}

JSONData::JSONData(const JSONData &other)
    : type(other.type), name(other.name), root(other.root)
{
}

JSONData::JSONData(JSONData &&other)
    : type(std::move(other.type)), name(std::move(other.name)),
      root(std::move(other.root))
{
}

JSONData::~JSONData() {}
