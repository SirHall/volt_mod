#include <iostream>

#include <volt/file.hpp>

int main(int argc, char *argv[])
{
    auto loader  = volt::file::JSONLoader();
    auto modules = loader.LoadModuleCollection("./res");

    if (modules.size() <= 0)
    {
        std::cerr << "No modules loaded" << std::endl;
        return 1;
    }

    for (auto &module : modules)
    {
        std::cout << "{\n\t"
                  << "Module:\t\t" << module.GetModuleName() << "\n\t"
                  << "Author:\t\t" << module.GetAuthor() << "\n\t"
                  << "Version:\t" << module.GetVersion() << "\n\t"
                  << "Site:\t\t" << module.GetSite() << "\n\t"
                  << "JSONs:\n";
        for (auto &jsonFile : module.GetAutoloadJSONs())
        {
            std::cout << "\t\t{\n";
            for (auto &jsonField : jsonFile.GetRoot())
                std::cout << "\t\t\t" << jsonField.first << ": "
                          << jsonField.second.get_value_optional<std::string>()
                                 .value_or("")
                          << "\n";
            std::cout << "\t\t}\n";
        }
        std::cout << "}" << std::endl;
    }

    return 0;
}