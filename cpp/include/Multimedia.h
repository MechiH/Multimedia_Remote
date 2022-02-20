//
// Multimedia.h
// Created on 14/12/2021
//
#ifndef multSec
#define multSec

#include <iostream>
#include <regex>
using namespace std;

/// Class For Multimedia Object
class Multimedia
{
private:
    string nomObj = "";
    string filePath = "";
    string type;

public:
    //! Multimedia Default Constructor
    Multimedia();

    //! Multimedia Parametrized Contructor
    Multimedia(string nomObj, string filePath);
    //! Get multimedia object name
    string getNomObj() const;

    //! Set multimedia object name
    void setNomObj(string nomObj);

    //! Get name of file containing multimedia object path
    string getFilePath() const;

    //! Set name of file containing multimedia object path
    void setFilePath(string ilePath);

    //! Get type of file containing multimedia object
    string getType() const;

    //! Set type of file containing multimedia object
    void setType(string type);

    //! Show multimedia object details
    virtual void show(ostream &stream) const;

    //! Show multimedia object details
    virtual void play() const {};

    //! Object Destructor
    ~Multimedia();
};

#endif