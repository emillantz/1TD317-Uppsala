#include <iostream>
using namespace std;

// Not sure if allowed to use functions yet but extracted this to avoid repeating ugly math in main
// (and it's more descriptive adding 24 hours to seconds than 86400)
int toSeconds(int hr, int min, int sec)
{
    // 60*60 seconds in an hour, 60 seconds in a minute
    return hr * 3600 + min * 60 + sec;
}

int main()
{
    int startNr;
    int startHr, startMin, startSec;
    int finishHr, finishMin, finishSec;
    int winningNr, winningTime = __INT_MAX__; // winningTime set to max int value on init to ensure no funny business
    int nbrContestants = 0;
    while (true)
    {
        cout << "Startnummer? ";
        cin >> startNr;
        if (startNr <= 0)
        {
            break;
        }
        cout << "Starttid (hr min sek)? ";
        cin >> startHr >> startMin >> startSec;
        cout << "Måltid? (hr min sek)? ";
        cin >> finishHr >> finishMin >> finishSec;
        // I was going insane when testing multiple contestants so added this newline to make it easier to read
        cout << endl;

        // Convert start & finish times to seconds
        int startTime = toSeconds(startHr, startMin, startSec);
        int finishTime = toSeconds(finishHr, finishMin, finishSec);

        // Add 24 hours if contestant finished after midnight (since 1 day = 24 hours etc.)
        if (finishTime < startTime)
        {
            finishTime += toSeconds(24, 0, 0);
        }

        int time = finishTime - startTime;
        // If the difference between start and finish time is less than the current winning time, set new winning time & number
        if (time < winningTime)
        {
            winningTime = time;
            winningNr = startNr;
        }
        nbrContestants++;
    }
    if (nbrContestants > 0)
    {
        cout << "\nVinnare är startnr: " << winningNr << "\n"
             << "Tim: " << winningTime / 3600 << "\n"
             << "Min: " << (winningTime % 3600) / 60 << "\n"
             << "Sek: " << (winningTime % 3600) % 60 << endl;
        cout << "Antal tävlande: " << nbrContestants << endl;
    }
    else
    {
        cout << "Inga tävlande" << endl;
    }
    cout << "Programmet avslutas" << endl;

    return 0;
}