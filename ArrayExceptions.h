#pragma once
#include <exception>

class ArrayBadLength : public std::exception
{
public:
    virtual const char *what() const noexcept override
    {
        return "ERROR: Bad length!";
    }
};

class ArrayBadRange : public std::exception
{
public:
    virtual const char *what() const noexcept override
    {
        return "ERROR: Bad range!";
    }
};

class ArrayNotFound : public std::exception
{
public:
    virtual const char *what() const noexcept override
    {
        return "ERROR: Search result not found!";
    }
};