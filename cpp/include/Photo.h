#ifndef photoSec
#define photoSec

#include <iostream>
#include <string>
#include "Multimedia.h"
#include "OutputFormat.h"

/// Class For Photo object
class Photo : public Multimedia
{
private:
    int latitude = 0;
    int longitude = 0;

public:
    //! Photo Paramterized Constructor with input santization
    Photo(string nomObj, string filePath, float latitude, float longitude) : Multimedia(nomObj, filePath), latitude(latitude), longitude(longitude)
    {
        this->setType("Photo");
    };
    //! Get photo latitude
    float getLatitude() const
    {
        return latitude;
    }

    //! Set photo latitude
    void setLatitude(int latitude)
    {
        latitude = latitude;
    }

    //! Get photo longitude
    float getLongitude() const
    {
        return longitude;
    }

    //! Set photo longitude
    void setLongitude(int longitude)
    {
        longitude = longitude;
    }
    //! Show photo dimensions
    void show(ostream &stream) const override
    {
        string s;
        Multimedia::show(stream);
        stream << "[+] Latitude : " << Photo::getLatitude() << "\n";
        stream << "[+] Longitude : " << Photo::getLongitude() << "\n";
    }
    //! Show photo using imagej
    void play() const override
    {
        string command = "imagej " + Multimedia::getFilePath() + " &";

        try
        {
            system(command.data());
        }
        catch (const std::exception &e)
        {
            cerr << BOLDRED << "/!\\ Please Verifiy that you have imagej on your machine";
            exit(0);
        }
    }
    //! Photo Destructor
    ~Photo()
    {
        cout << "\n"
             << BOLDRED << "[!] Photo Deleted"
             << "\n";
    }
};

#endif