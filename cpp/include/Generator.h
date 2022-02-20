#ifndef generatorSec
#define generatorSec
#include <iostream>
#include <map>
#include <typeinfo>
#include "OutputFormat.h"
#include "Group.h"
#include "Multimedia.h"

using namespace std;
/// Class For Generating Groups and Media Objects and store them
class Generator
{
private:
    // ! Map of Groups Pointers
    map<string, Group<Multimedia *> *> groups;
    // ! Map of Multimedia Objects  Pointers
    map<string, Multimedia *> medias;

public:
    // ! Generator Constructor
    Generator();
    // !  Create a Photo Object and add it to medias map
    Photo *createPhoto(string name, string filePath, float latitude, float longitude);
    // !  Create a Video Object and add it to medias map
    Video *createVideo(string name, string filePath, int duration);
    // !  Create a Film Object and add it to medias map
    Film *createFilm(string name, string filePath, int duration, int *chaps, int length);
    // !  Create a Group of Object and add it to groups map
    Group<Multimedia *> *createGroup(string name);

    // !  Add Media object already created to a Group already created
    void addToGroup(string groupName, string mediaName);
    // !  Show Media Object propreties or Group content
    void print(string name, ostream &stream);
    // !  Show Generator Content
    void listGen(ostream &stream);
    // !  Sanitizing Input
    bool linkChecker(vector<string> attributes);
    // !  Check That all required parameters are supplied
    bool paramsCheck(int len, int n, ostream &stream);
    // !  Play media object
    void run(string name, ostream &stream = cout);

    // !  Generator Destructor
    ~Generator();
};

#endif
