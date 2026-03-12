#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Common.hpp"

class Environment {
    std::unordered_map<std::string, Value> values;
    std::shared_ptr<Environment> enclosing;
public:
    Environment();
    Environment(std::shared_ptr<Environment> enclosing);
    
    void define(const std::string& name, const Value& value);
    Value get(const std::string& name);
    void assign(const std::string& name, const Value& value);
};
