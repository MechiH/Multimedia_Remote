//
// Multimedia.cpp
// Created on 14/12/2021
//

#include "include/Multimedia.h"
#include "include/OutputFormat.h"
#include <iostream>

using namespace std;

const regex regexp("/^[ _@./#&+-]*$/");
//! Construction
Multimedia ::Multimedia(){};
Multimedia::Multimedia(string nomObj, string filePath) : nomObj(nomObj), filePath(filePath)
{
    this->type = "Multimedia object";
};

string Multimedia::getNomObj() const
{
    return nomObj;
}

void Multimedia::setNomObj(string nomObj)
{
    nomObj = nomObj;
}

string Multimedia::getFilePath() const
{
    return filePath;
}

void Multimedia::setFilePath(string filePath)
{
    filePath = filePath;
}
string Multimedia::getType() const
{
    return type;
}

void Multimedia::setType(string type)
{
    this->type = type;
}
void Multimedia::show(ostream &stream) const
{
    stream << "\n"
           << this->getType() << " prorpreties :"
           << "\n";
    stream << "[+] " << this->type << " Name : " << Multimedia::getNomObj() << "\n";
    stream << "[+] " << this->type << " Related File Name : " << Multimedia::getFilePath() << "\n";
}

Multimedia::~Multimedia()
{
    cout << "\n"
         << BOLDRED << "[!] " << this->getNomObj() << " Deleted"
         << "\n";
}