#ifndef MEETING_H
#define MEETING_H

using namespace std;


class meeting
{
    private:
    string title;
    int day;
    int hour;
    bool nullTree;    
    meeting* leftTree;
    meeting* rightTree;

    public:
    meeting();
    bool Empty() const;
    string gettitle()const;
    int getday()const;
    int gethour()const;
    void start(const meeting &m);
    meeting* left();
    meeting* right();
    bool insert (const string &addedTitle, const int &addedDay, const int &addedHour);
    meeting* retrieve(const int &addedDay, const int &addedHour);
    void changeTitle(const string &addedTitle);
    void Delete();

};

#endif
