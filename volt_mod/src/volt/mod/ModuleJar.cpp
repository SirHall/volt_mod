#include "volt/mod/ModuleJar.hpp"

#include <exception>

using namespace volt::mod;

inline void MoveModuleToQueue(std::vector<Module> &         modulesToLoad,
                              std::vector<Module>::iterator it,
                              std::vector<Module> &         loadQueue)
{

    Module modToMove(*it);
    modulesToLoad.erase(it);
    loadQueue.push_back(std::move(modToMove));
}

// TODO: This could be spit into smaller functions
ModuleJar::ModuleJar(std::vector<Module> modulesToLoad)
{
    this->modules.clear();
    this->modules.reserve(modulesToLoad.size());
    while (modulesToLoad.size() > 0)
    {
        auto modulesToLoadCount = modulesToLoad.size();
        for (auto i = modulesToLoad.begin(); i != modulesToLoad.end(); i++)
        {
            if (i->GetDependencies().size() == 0 &&
                i->GetLoadAfter().size() == 0)
            {
                MoveModuleToQueue(modulesToLoad, i, this->modules);
                break;
            }
            // Now load in all modules with dependencies that have already been
            // loaded, and respect the load after rules, assuming those modules
            // exist.
            bool allDepsLoaded = true;
            for (auto const &dep : i->GetDependencies())
            {
                if (std::none_of(this->modules.begin(), this->modules.end(),
                                 [&](Module const &loadedMod) {
                                     return loadedMod.GetModuleName() == dep;
                                 }))
                {
                    // This dependency has not been loaded yet
                    allDepsLoaded = false;
                    break;
                }
            }

            if (allDepsLoaded)
            {
                // All required dependencies have been loaded, now ensure that
                // all loadAfters that exist are loaded first
                bool allLoadAftersLoaded = true;
                for (auto const &loadAfter : i->GetLoadAfter())
                {

                    if (std::any_of(modulesToLoad.begin(), modulesToLoad.end(),
                                    [&](Module const &existingMod) {
                                        return existingMod.GetModuleName() ==
                                               loadAfter;
                                    }))
                    {
                        // This loadAfter module still needs to be loaded
                        allLoadAftersLoaded = false;
                        break;
                    }
                }

                // Have both the dependencies, and the loadAfterModules been
                // loaded?
                if (allLoadAftersLoaded)
                {
                    // Both have been loaded, add it to the load queue
                    MoveModuleToQueue(modulesToLoad, i, this->modules);
                    break;
                }
            }
        }

        if (modulesToLoad.size() == modulesToLoadCount)
        {
            // Not a single module was loaded in the last iteration, there must
            // be a cyclic dependency, or a dependency that doesn't exist
            // TODO: Return a more useful string
            throw std::runtime_error(
                "Circular dependency, or missing dependency discovered");
        }
    }
}

ModuleJar::ModuleJar(const ModuleJar &other) : modules(other.modules) {}

ModuleJar &ModuleJar::operator=(const ModuleJar &other)
{

    modules.clear();
    std::copy(other.modules.begin(), other.modules.end(),
              std::back_inserter(modules));
    return *this;
}

ModuleJar::ModuleJar(ModuleJar &&other) : modules(std::move(other.modules)) {}

ModuleJar &ModuleJar::operator=(ModuleJar &&other)
{
    modules = std::move(other.modules);
    return *this;
}

ModuleJar::~ModuleJar() {}