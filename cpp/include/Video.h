#ifndef videoSec
#define videoSec

#include <iostream>
#include "Multimedia.h"
#include "OutputFormat.h"

/// Class For Video object
class Video : public Multimedia
{
private:
    int duration = 0;

public:
    //! Video Paramterized Constructor with input santization
    Video(string nomObj, string filePath, int duration) : Multimedia(nomObj, filePath), duration(duration)
    {
        this->setType("Video");
    };

    //! Get video duration
    int getDuration() const
    {
        return duration;
    }

    //! Set video duration
    void setDuration(int duration)
    {
        duration = duration;
    }

    //! Set video duration
    void show(ostream &stream) const override
    {
        Multimedia::show(stream);
        stream << "[+] Duration : " << Video::getDuration() << "\n";
    }
    //! Play video using mpv player
    void play() const override
    {
        string command = "mpv " + Multimedia::getFilePath() + " &";

        try
        {
            system(command.data());
        }
        catch (const std::exception &e)
        {
            cerr << BOLDRED << "/!\\ Please Verifiy that you have mvp on your machine";
            exit(0);
        }
    }
    //! Video Destructor
    ~Video()
    {
        cout << "\n"
             << BOLDRED << "[!] Video Deleted"
             << "\n";
    }
};

#endif