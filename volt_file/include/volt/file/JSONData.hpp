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
    };

} // namespace volt::file
#endif
