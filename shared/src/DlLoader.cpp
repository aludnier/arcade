/*
** EPITECH PROJECT, 2026
** DlLoader
** File description:
** DlLoader
*/

#include <cstddef>
#include <cstdio>
#include <dlfcn.h>
#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include "DlLoader.hpp"

DlLoader::DlLoader(const std::string &path) : _location(path), _handle(nullptr)
{

}

DlLoader &DlLoader::operator=(DlLoader &&other) noexcept
{
    if (this != &other) {
        unload();
        _handle = other._handle;
        other._handle = nullptr;
    }
    return *this;
}

DlLoader::~DlLoader()
{
    unload();
}

void DlLoader::load()
{
    if (_handle != nullptr)
        return;

    _handle = dlopen(_location.c_str(), RTLD_LAZY);
    
    if (!_handle)
        throw std::runtime_error(dlerror());
}

void DlLoader::unload()
{
    if (_handle == nullptr)
        return;

    dlclose(_handle);
    _handle = nullptr;
}

void *DlLoader::sym(const std::string &symbol) const
{
    if (_handle == nullptr)
        return nullptr;


    void *result = dlsym(_handle, symbol.c_str());
    if (result == nullptr)
        throw std::runtime_error(dlerror());

    return result;
}

bool DlLoader::is_loaded() const
{
    return _handle != nullptr;
}
