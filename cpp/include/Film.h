#ifndef filmSec
#define filmSec
#include <iostream>
#include "Video.h"
#include "OutputFormat.h"

/// Class For Film object
class Film : public Video
{
private:
    int *chapters;
    int length;

public:
    //! Film Parametrized Contructor
    Film(string nomObj, string filePath, int duration, int *chaps, int length) : Video(nomObj, filePath, duration), chapters(chaps), length(length)
    {
        this->setType("Film");
    };
    //! Get film chapters durations
    int *getChapters() const
    {
        return chapters;
    }
    //! Get film chapters durations
    void setChapters(int *chapters)
    {
        this->chapters = chapters;
    }
    //! Show film's chapters duration
    void show(ostream &stream) const
    {
        Multimedia::show(stream);
        stream << "\n"
               << this->getType() << "  chapters duration :"
               << "\n";
        for (int i = 0; i < length; i++)
        {
            stream << "[+] Chapter " << i << " duration : " << this->chapters[i] << "\n";
        }
    }
    //! Destroy Film
    ~Film()
    {
        delete[] chapters;
    };
};
#endif
