#pragma once
#ifndef VOLT_FILE_JSONDATA_HPP
#define VOLT_FILE_JSONDATA_HPP

#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace volt::file
{
    class JSONData
    {
    private:
        const std::string                 type;
        const std::string                 name;
        const boost::property_tree::ptree root;

    protected:
    public:
        JSONData(std::string const typeName, std::string const assetName,
                 boost::property_tree::ptree const rootData);
        JSONData(const JSONData &other);
        JSONData(JSONData &&other);
        ~JSONData();

        inline std::string const &GetName() const { return this->name; }

        inline std::string const &GetType() const { return this->type; }

        inline boost::property_tree::ptree const &GetRoot() const
        {
            return this->root;
        }
    };

} // namespace volt::file
#endif
