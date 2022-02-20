//
// main.cpp
// Created on 21/10/2018
//
// les pointeurs pointent sur le même objet ! pour la copie
// on doit supprimer le tableau contenant les durée des chatitres du film lors de destruction d'objet film
/*! \mainpage 
Creating software for a multi-media set-top box that can, among other things, play music, movies, and films, as well as show images, is a challenging endeavor. 
*/
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include "include/Video.h"
#include "include/Photo.h"
#include "include/Film.h"
#include "include/Group.h"
#include "include/tcpserver.h"
#include "Generator.cpp"
#include "Multimedia.cpp"
using namespace std;

typedef std::shared_ptr<Video> VideoPtr;
const int PORT = 3331;

int main(int argc, const char *argv[])
{
#ifdef VERSION_TRUC
    Multimedia *mult = new Multimedia("test", "/hdh");
    Video *vid1 = new Video("video1", "./assets/video.mp4", 10);
    Video *vid2 = new Video("video2", "./assets/video.mp4", 4);

    Photo *img1 = new Photo("image1", "./assets/img.png", 5, 187);
    Photo *img2 = new Photo("image2", "./assets/img.png", 2, 124);
    //! Polymorphism  Test
    list<Multimedia *> list;
    list.push_back(mult);
    list.push_back(vid1);
    list.push_back(img1);
    // for (auto &it : list)
    // {
    //     it->show(cout);
    // }

    //! Film Class Test
    int *duration = new int[4]{12, 34, 56, 6};
    Film *film = new Film("video", "./assets/video.mp4", 10, duration, 4);
    // film->show(cout);
    // film->~Film();

    //! Group Class Test
    Group<Video *> *videos = new Group<Video *>("Videos Group");
    videos->push_back(vid1);
    videos->push_back(vid2);
    Group<Photo *> *photos = new Group<Photo *>("Photos Group");
    photos->push_back(img1);
    photos->push_back(img2);
    Group<Video *> *mixed = new Group<Video *>("Mixed Group");
    mixed->push_back(vid1);
    mixed->push_back(film);

    // videos->content(cout);
    // photos->content(cout);
    // mixed->content(cout);

    Group<VideoPtr> *SmartPointers = new Group<VideoPtr>("Smart Pointers Group");
    SmartPointers->push_back(VideoPtr(new Video("video1", "./assets/video.mp4", 10)));
    SmartPointers->push_back(VideoPtr(new Video("video2", "./assets/video.mp4", 4)));
    SmartPointers->content(cout);
    auto it = SmartPointers->begin();
    std::advance(it, 1);
    SmartPointers->erase(SmartPointers->begin(), it);
#endif
    // ! Creating Genenrator instance
    Generator *gen = new Generator();
    Video *vid1 = new Video("video1", "./assets/video.mp4", 10);
    Video *vid2 = new Video("video2", "./assets/video.mp4", 4);
    gen->createVideo("video1", "./assets/video.mp4", 4);
    gen->createPhoto("image1", "./assets/img.png", 5, 187);
    Group<Multimedia *> *group = gen->createGroup("VideosGroup");
    group->push_back(vid1);
    group->push_back(vid2);

    // ! TCPServer Creation
    auto *server =
        new TCPServer([&](std::string const &request, std::string &response)
                      {
                          cerr << "\nRequest: '" << request << "'" << endl;
                          // ! Handling Request
                          stringstream str, answer;
                          string action, s;
                          vector<string> attributes;
                          str << request;

                          while (str >> s)
                          {
                              attributes.push_back(s);
                          }
                          // ! Sanitizing Input
                          if (gen->linkChecker(attributes))
                          {
                              answer << "Please Verify that your link dosen't contain special caracters";
                              return true;
                          }
                          action = attributes[0];
                          int length = attributes.size();
                          try
                          {

                              // ! Switching through action cases with parameters checking
                              if (action == "SHOW")
                              {
                                  if (!gen->paramsCheck(length, 1, answer))
                                      return true;
                                  gen->print(attributes[1], answer);
                              }
                              if (action == "LIST")
                              {
                                  gen->listGen(answer);
                              }
                              else if (action == "PLAY")
                              {
                                  if (!gen->paramsCheck(length, 1, answer))
                                      return true;
                                  gen->run(attributes[1], answer);
                                  answer << "Play " << attributes[1] << "\n";
                              }
                              else if (action == "ADDPHOTO")
                              {
                                  if (!gen->paramsCheck(length, 4, answer))
                                      return true;
                                  gen->createPhoto(attributes[1], attributes[2], stof(attributes[3]), stof(attributes[4]));
                                  gen->print(attributes[1], answer);
                              }
                              else if (action == "ADDFILM")
                              {
                                  int len = stoi(attributes.back());
                                  int arr[len];
                                  for (int i = 0; i < len; i++)
                                  {
                                      arr[i] = stoi(attributes[i + 4]);
                                  }

                                  int *chaps = arr;
                                  gen->createFilm(attributes[1], attributes[2], stoi(attributes[3]), chaps, len);
                                  gen->print(attributes[1], answer);
                              }
                              else if (action == "ADDVIDEO")
                              {
                                  if (!gen->paramsCheck(length, 3, answer))
                                      return true;
                                  gen->createVideo(attributes[1], attributes[2], stoi(attributes[3]));
                                  gen->print(attributes[1], answer);
                              }
                              else if (action == "ADDGROUP")
                              {
                                  if (!gen->paramsCheck(length, 1, answer))
                                      return true;
                                  gen->createGroup(attributes[1]);
                                  gen->print(attributes[1], answer);
                              }
                              else if (action == "ADDTOGROUP")
                              {
                                  if (!gen->paramsCheck(length, 2, answer))
                                      return true;
                                  gen->addToGroup(attributes[1], attributes[2]);
                                  gen->print(attributes[1], answer);
                              }
                              // ! Relpying to Request
                              if (answer.str().empty())
                              {
                                  response = "404 COULD NOT FIND \n";
                              }
                              else
                              {
                                  response = "200 OK \n " + answer.str() + "\n";
                                  std::replace(response.begin(), response.end(), '\n', ';');
                              }
                          }
                          catch (exception &e)
                          {
                              answer << "Please verify your request attributes" << '\n';
                          }

                          // renvoyer false si on veut clore la connexion avec le client
                          return true;
                      });

    // lance la boucle infinie du serveur
    std::cout << "Starting Server on port " << PORT << std::endl;

    int status = server->run(PORT);

    // en cas d'erreur
    if (status < 0)
    {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }
    return 0;
}
