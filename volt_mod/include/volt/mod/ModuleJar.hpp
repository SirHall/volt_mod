#pragma once
#ifndef VOLT_MOD_MODULEJAR_HPP
#define VOLT_MOD_MODULEJAR_HPP

#include "volt/mod/Module.hpp"

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace volt::mod
{

    class ModuleJar
    {
    private:
        // This vector is ordered in the order in which modules must be loaded
        std::vector<Module> modules;

    protected:
    public:
        ModuleJar(std::vector<Module> modulesToLoad);
        ModuleJar(const ModuleJar &other);
        ModuleJar &operator=(const ModuleJar &other);
        ModuleJar(ModuleJar &&other);
        ModuleJar &operator=(ModuleJar &&other);
        ~ModuleJar();

        inline std::vector<Module> const &GetModulesQueue()
        {
            return this->modules;
        }
    };

} // namespace volt::mod
#endif
