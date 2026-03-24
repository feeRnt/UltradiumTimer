## Ultradium: A lightweight, customizable Qt application for work-break scheduling. Android, Windows and GNU-Linux. (Work in progress)

The app's name, Ultradium, is based on the existence of the *Ultradian Cycles*, typically 90 to 120 minute cycles in humans and other mammals    
(and other families), that govern the distribution of biological energy, i.e., work, focus, activity, and rest, i.e., sleep, relaxation and growth.

The knowledge of these cycles can help govern how we choose to engage in our work and other important activities, leading to a more balanced work-life schedule, 
and preventing burnout!

While there may be some open-source apps making use of this ultradian cycle concept, I couldn't find any that combines **another** popular mechanism for
proper work efficiency: the Pomodoro Technique, which states that many of us work best when we work for 25 minutes, and take a 5 minute break on each such interval.


Joining together this 25 minute work - 5 minute break cycle, with the 90 minute work period with a 30 minute break, I devised the thought for this app!


I no longer have to constantly remember my work timings, and can delegate the full focus to the work at hand. This has personally helped me greatly in not 
getting burnt out from overworking.  
I also included some inspirational quotes that I thought were worth a mention (even though I struggled to justify a reason to include some of them; don't worry
you can turn these off if you wish).


You can also adjust the work-break times if you want, for a more personalized experience.

----

# The current version of the app is very much a work-in-progress:

There are many missing features, such as: 
- A journaling feature by day to keep track of your work,
- A proper settings menu to declutter everything from the main interface.,
- Functioning notification system with Qt for Desktop and Mobile,
- Adjusting the background color for work or break periods with a color picker,
- Removing or adding text to the quotes list,
- Beautifying and clearing up the app's GUI, which is somehwat of a mess at present, and others
- Oh and also, to compile for Android, which I still haven't tested

----

# Features:
- Combines 25-5 work-break split (Pomodoro) with a 90-30 work-break split (Ultradian)
- Allows selecting your own time ranges
- Pause, reset time as needed
- Ding sounds to notify of finished work or break periods
- Quotes...

# How to use:

The best way to use this app right now, is to clone the repo
```bash
git clone https://github.com/feeRnt/UltradiumTimer
```
and import the project into Qt Creator, then Build (& Run) it, or to build it manually using CMake directly after the clone:

```bash
cd UltradiumTimer
mkdir build_cmake_manual
cd build_cmake_maunal
cmake ..
# I have not tested manually with CMake like this before, but it should work.
```
You will need to have your distro or OS' version of build-essentials installed beforehand of course.
```
sudo apt install build-essential
```

Detailed instructions for compiling and pre-built, **small** (hopefully! I didn't realize how big Qt could get) binaries/packages will be released in the future.

## What does it look like?

Despite its rudimentary nature, I thought I should paste some photos of the app. Here they are:


<img src="./Pictures/image1.png" width="745" alt="The app as it is in break mode, yes it is lovely green" />
<br>
And here is another view of the app in the working phase,
<img src="./Pictures/image2.png" width="745" alt="What it looks like during a work cycle" />
<br>    

Did I mention there are quotes?    

----

Credits: 
- https://www.asianefficiency.com/productivity/ultradian-rhythms/ , this pretty nice article originally introduced me to the topic
- Me: Coded it (please star if you think it's cool!)
- AI: Yes it helped, and gave boilerplate for the code in its initial phase
