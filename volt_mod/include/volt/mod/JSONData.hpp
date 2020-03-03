#pragma once
#ifndef VOLT_FILE_JSONDATA_HPP
#define VOLT_FILE_JSONDATA_HPP

#include <filesystem>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace volt::file
{
    class JSONData
    {
    private:
        std::string                 type;
        std::string                 name;
        boost::property_tree::ptree root;
        std::filesystem::path       filePath;
        bool                        loaded = false;

    protected:
    public:
        JSONData(std::string const typeName, std::string const assetName,
                 boost::property_tree::ptree const rootData,
                 const std::filesystem::path       fileLocation);
        JSONData(const JSONData &other);
        JSONData &operator=(const JSONData &other);
        JSONData(JSONData &&other);
        JSONData &operator=(JSONData &&other);

        ~JSONData();

        inline std::string const &GetName() const { return this->name; }

        inline std::string const &GetType() const { return this->type; }

        inline boost::property_tree::ptree const &GetRoot() const
        {
            return this->root;
        }

        inline std::filesystem::path const &GetFileLocation()
        {
            return this->filePath;
        }
    };

} // namespace volt::file
#endif
