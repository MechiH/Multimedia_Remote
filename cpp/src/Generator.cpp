//
// Multimedia.cpp
// Created on 18/02/2022
//

#include "include/Generator.h"
#include "include/OutputFormat.h"
#include <iostream>

using namespace std;

Generator::Generator(){};

Photo *Generator::createPhoto(string name, string filePath, float latitude, float longitude)
{
    try
    {
        /* code */
        Photo *img(new Photo(name, filePath, latitude, longitude));
        medias[name] = img;
        return img;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
};

Video *Generator::createVideo(string name, string filePath, int duration)
{
    Video *vid(new Video(name, filePath, duration));
    medias[name] = vid;
    return vid;
};

Film *Generator::createFilm(string name, string filePath, int duration, int *chaps, int length)
{
    Film *film(new Film(name, filePath, duration, chaps, length));
    medias[name] = film;
    return film;
};

Group<Multimedia *> *Generator::createGroup(string name)
{
    Group<Multimedia *> *mult = new Group<Multimedia *>(name);
    groups[name] = mult;
    return mult;
};

void Generator::print(string name, ostream &stream)
{

    if (medias.find(name) != medias.end())
    {
        medias[name]->show(stream);
    }
    else if (groups.find(name) != groups.end())
    {
        groups[name]->content(stream);
    }
    else
    {
        stream << "Please verify That requested object exists !";
    }
};

void Generator::run(string name, ostream &stream)
{

    if (medias.find(name) != medias.end())
    {
        medias[name]->play();
    }
    else
    {
        stream << "Please verify That requested object exists !";
    }
}

void Generator::listGen(ostream &stream)
{
    stream << "Groups List :"
           << "\n";
    for (auto it = groups.begin(); it != groups.end(); ++it)
    {

        stream << "[*] " << it->first << "\n";
    }
    stream << "Medias List :"
           << "\n";
    for (auto it = medias.begin(); it != medias.end(); ++it)
    {

        stream << "[*] " << it->first << "\n";
    }
}
bool Generator::linkChecker(vector<string> attributes)
{
    for (auto it = attributes.begin(); it != attributes.end(); ++it)
    {
        if ((*it).find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890./") != std::string::npos)
        {
            cerr << BOLDRED << "/!\\ Might be Malicous link"
                 << RESET;
            return true;
        }
    }
    return false;
}
void Generator::addToGroup(string groupName, string mediaName)
{
    groups[groupName]->push_back(medias[mediaName]);
};
bool Generator::paramsCheck(int len, int n, ostream &stream)
{
    if (len < n)
    {
        stream << "Please Supply all necessary parameters";
        return false;
    }
    return true;
}
Generator::~Generator()
{
    cout << "\n"
         << BOLDRED << "[!] "
         << "Generator Deleted"
         << "\n";
};
