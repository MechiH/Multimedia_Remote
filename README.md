# Multimedia Project

<pre>
.
├── cpp
│   ├── assets
│   │   ├── img.png
│   │   └── video.mp4
│   ├── config_doxygene
│   ├── include
│   │   ├── ccsocket.h
│   │   ├── Film.h
│   │   ├── Generator.h
│   │   ├── Group.h
│   │   ├── Multimedia.h
│   │   ├── OutputFormat.h
│   │   ├── Photo.h
│   │   ├── tcpserver.h
│   │   └── Video.h
│   ├── Makefile
│   ├── readme.md
│   └── src
│       ├── ccsocket.cpp
│       ├── Generator.cpp
│       ├── main.cpp
│       ├── Multimedia.cpp
│       └── tcpserver.cpp
└── swing
    ├── assets
    │   ├── clear.png
    │   ├── close.png
    │   ├── connect.png
    │   ├── help.png
    │   └── more.png
    ├── help.txt
    ├── Main.java
    └── Makefile
</pre>

# Cook Book

 <pre style=" text-align: left;
    white-space: pre-line;">
 To run this project :
 open a terminal
 1)cd cpp
 2)make run
 open another terminal
 1) cd swing
 2) make run

 In your interface You have 3 main Parts :
The top Menu :
 Containing several button to make diffrent types of requests and a text field
 in which you specify your request parameters
 The Text Area:
 In which You see you requests results
 The bottom Menu :
 Containing Controll buttons

 First Step To work with this repote is to Open your C++ Server and connect to
 it by pressing Connect button</pre>

## List Button

 <pre style=" text-align: left;
    white-space: pre-line;">This button allows you to list all the content already created and available content
 <b style="color:blue">Params</b> no Paramter required</pre>

## Show Button

 <pre style=" text-align: left;
    white-space: pre-line;">This button allows you to print your media object or group charchteristics
 <b style="color:blue">Params</b> You must specify the name of object in the command field
<b style="color:orange">Example</b>  image1</pre>

## Play Button

 <pre style=" text-align: left;
    white-space: pre-line;">This button allows you to play your object
 <b style="color:blue">Params</b> You must specify the name of object in the command field
<b style="color:orange">Example</b>  video1</pre>

## Add Photo

 <pre style=" text-align: left;
    white-space: pre-line;">This button allow you to add a Photo
 <b style="color:blue">Params</b> Name Path/to/Image latitud logntitude
<b style="color:crimson">Remarque</b>latitude and longtitude should be floats
 <b style="color:orange">Example</b> imag ./assets/img.png 10 12</pre>

##  Add Video

 <pre style=" text-align: left;
    white-space: pre-line;">This button allow you to add a Video
 <b style="color:blue">Params</b> Name Path/to/Video duration
<b style="color:crimson">Remarque</b>  duration int
<b style="color:orange">Example</b>  video ./assets/video.mp4 10</pre>

## Add Film

 <pre style=" text-align: left;
    white-space: pre-line;">This button allow you to add a Film
 <b style="color:blue">Params</b> Name Path/to/Film duration of film durations of chapters number of chapters
<b style="color:orange">Example</b>  SAW ./assets/video.mp4 134 10 80 20 24 4</pre>

## Add Group

 <pre style=" text-align: left;
    white-space: pre-line;">This button allow you to add a Group
 <b style="color:blue">Params</b> You Must specify The name of the group in the command field
<b style="color:orange">Example</b>  ImagesGroup</pre>

## Add To Group

<pre> This button allow you to add an already existing media object to an
 already existing group
 <b style="color:blue">Params</b> Group Name Object Name
<b style="color:orange">Example</b>  VideosGroup video1</pre>
<pre>
@Important all your inputs chacrahters must be in this permitted inputs list any charachter outside this list your request won't be processed:
 - [a,z]
 - [A,Z]
 - [0,9]
 - "/" and "."</pre>
