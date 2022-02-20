#ifndef groupSec
#define groupSec
#include <iostream>
#include <list>
#include "OutputFormat.h"

/// Class For Putting Differents Medias into Groups
template <class TYPE>
class Group : public list<TYPE>
{
private:
    string groupName;

public:
    //! Group Parametrized Contructor
    Group<TYPE>(string groupName) : groupName(groupName){};

    //! Get Group name
    string getGroupName() const
    {
        return groupName;
    }

    //! Set Group name
    void setGroupName(string groupName)
    {
        groupName = groupName;
    }

    //! Show Group's elemnts propreties
    void content(ostream &stream) const
    {
        stream << "\n"
               << this->getGroupName() << " elements :"
               << "\n";
        for (auto it = this->begin(); it != this->end(); ++it)
        {
            (*it)->show(stream);
        }
    }
    //! Group Destructor
    ~Group()
    {
        cout << "\n"
             << BOLDRED << "[!] Group Deleted"
             << "\n";
    };
};

#endif