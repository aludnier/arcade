/*
** EPITECH PROJECT, 2026
** DlLoader
** File description:
** DlLoader
*/

#pragma once

#include <string>

class DlLoader {
    public:
        DlLoader(const std::string &path);
        DlLoader &operator=(DlLoader &&other) noexcept;
        ~DlLoader();

        void load();
        void unload();
        void *sym(const std::string & symbol) const;
        bool is_loaded() const;

    private:
        std::string _location;
        void *_handle;
};
