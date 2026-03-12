#include "../core/Environment.hpp"

Environment::Environment() : enclosing(nullptr) {}
Environment::Environment(std::shared_ptr<Environment> enclosing) : enclosing(enclosing) {}

void Environment::define(const std::string& name, const Value& value) {
    values[name] = value;
}

Value Environment::get(const std::string& name) {
    if (values.find(name) != values.end()) {
        return values[name];
    }
    if (enclosing) return enclosing->get(name);
    throw std::runtime_error("Undefined variable '" + name + "'.");
}

void Environment::assign(const std::string& name, const Value& value) {
    if (values.find(name) != values.end()) {
        values[name] = value;
        return;
    }
    if (enclosing) {
        enclosing->assign(name, value);
        return;
    }
    throw std::runtime_error("Undefined variable '" + name + "'.");
}
