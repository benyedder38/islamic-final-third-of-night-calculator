#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

/**
 * Function to convert time string to total minutes
 * @param const string& time
 * @return int
*/
int time_to_minutes(const string& time) {
    int hours, minutes;
    char colon;
    stringstream ss(time);
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

/**
 * Function to convert total minutes back to a time string in "hh:mm" format
 * @param int minutes
 * @return string
 */
string minutes_to_time(int minutes) {
    int hours = (minutes / 60) % 24;
    int mins = minutes % 60;
    stringstream ss;
    ss << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << mins;
    return ss.str();
}


int main(int argc, char** argv) {
    // cli error checking
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <Fajr Time (hh:mm)> <Maghrib Time (hh:mm)>" << endl;
        return 1;
    }
    
    // the start and end of the night can be denoted as the time of maghrib until fajr the next day
    string fajr_time = argv[1]; 
    string maghrib_time = argv[2];
    
    // get the total time difference, convert times to string, then add the time difference from midnight
    int maghrib_minutes = time_to_minutes(maghrib_time);
    int fajr_minutes = time_to_minutes(fajr_time);
    int midnight_minutes = 24 * 60; // 1440 will denote the time of midnight
    int total_time_difference = (midnight_minutes - maghrib_minutes) + fajr_minutes;
    
    // create necesdary partitions from the total time
    int third = total_time_difference / 3;
    int half = total_time_difference / 2;
    
    // calculate specific times
    int first_third_of_night = maghrib_minutes + third; // first third of the night - recommended time for isha
    int middle_of_night = maghrib_minutes + half; // middle of the night - last time to pray isha
    int final_third_of_night = fajr_minutes - third; // final third of the night - best time for qiyam al-layl

    // convert back to string
    string first_third_time = minutes_to_time(first_third_of_night);
    string middle_night_time = minutes_to_time(middle_of_night);
    string final_third_time = minutes_to_time(final_third_of_night);

    // output
    cout << "\tIsha recommended dealine:    " << first_third_time << endl;
    cout << "\tIsha deadline:               " << middle_night_time << endl;
    cout << "\tBest time for Qiyam Al-Layl: " << final_third_time << endl;

    return 0;
}
