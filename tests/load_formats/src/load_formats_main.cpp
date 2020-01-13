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
                  << "JSONs:\t\t";
        for (auto &jsonFile : module.GetAutoloadJSONs())
            std::cout << jsonFile.GetName() << " ";
        std::cout << "\n}" << std::endl;
    }

    return 0;
}