#include "Type.h"
#include <assert.h>
#include <sstream>

// 不确定这个size改动会不会导致数组出问题，感觉应该没事

IntType TypeSystem::commonConstInt = IntType(32, true);
IntType TypeSystem::commonInt = IntType(32);
IntType TypeSystem::commonBool = IntType(1);
VoidType TypeSystem::commonVoid = VoidType();

Type* TypeSystem::constIntType = &commonConstInt;
Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::boolType = &commonBool;

std::string IntType::toStr() {
    std::ostringstream buffer;
    if (constant)
        buffer << "const int";
    else
        buffer << "int";
    buffer << size;
    return buffer.str();
}

std::string VoidType::toStr() {
    return "void";
}

std::string ArrayType::toStr() {
    std::vector<std::string> vec;
    Type* temp = this;
    while (temp && temp->isArray()) {
        std::ostringstream buffer;
        if (temp == this && length == 0)
            buffer << '[' << ']';
        else
            buffer << '[' << ((ArrayType*)temp)->getLength() << ']';
        vec.push_back(buffer.str());
        temp = ((ArrayType*)temp)->getElementType();
        ;
    }
    assert(temp->isInt());
    std::ostringstream buffer;
    if (constant)
        buffer << "const ";
    buffer << "int";
    for (auto it = vec.begin(); it != vec.end(); it++)
        buffer << *it;
    return buffer.str();
}

std::string FunctionType::toStr() {
    std::ostringstream buffer;
    buffer << returnType->toStr() << "(";
    for (auto it = paramsType.begin(); it != paramsType.end(); it++) {
        buffer << (*it)->toStr();
        if (it + 1 != paramsType.end())
            buffer << ", ";
    }
    buffer << ')';
    return buffer.str();
}

std::string StringType::toStr() {
    std::ostringstream buffer;
    buffer << "const char[" << length << "]";
    return buffer.str();
}

std::string PointerType::toStr() {
    std::ostringstream buffer;
    buffer << valueType->toStr() << "*";
    return buffer.str();
}
