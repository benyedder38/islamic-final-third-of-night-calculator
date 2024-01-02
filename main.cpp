#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

int convertToMinutes(const std::string& time) {
    std::stringstream ss(time);
    std::string token;
    std::getline(ss, token, ':');
    int hours = std::stoi(token);
    std::getline(ss, token);
    int minutes = std::stoi(token);
    return hours * 60 + minutes;
}

std::string convertToHHMM(int minutes, bool use24HourFormat = false) {
    int hours = minutes / 60;
    minutes %= 60;
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes;

    if (use24HourFormat) {
        return ss.str();
    } else {
        // Convert to 12-hour format
        int hour12 = hours % 12;
        if (hour12 == 0) {
            hour12 = 12;  // 0 should be represented as 12 in 12-hour format
        }
        ss << (hours < 12 ? " AM" : " PM");
        return ss.str();
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <00:00> <23:59>" << std::endl;
        std::cerr << "       " << argv[0] << " <Fajr Time> <Maghrib Time>" << std::endl;
        return 1;
    }
    std::string fajrTime = argv[1]; 
    std::string maghribTime = argv[2];
    
    int fajrMinutes = convertToMinutes(fajrTime);
    int maghribMinutes = convertToMinutes(maghribTime);
    int midnightTime = convertToMinutes("24:00");
    
    int nightDurationMinutes = (midnightTime - maghribMinutes) + fajrMinutes;
    int finalThirdDurationMinutes = std::round(nightDurationMinutes / 3.0);
    
    int firstThirdEndMinutes = maghribMinutes + finalThirdDurationMinutes;
    int middleStartMinutes = (fajrMinutes + maghribMinutes) / 2;
    int finalThirdStartMinutes = fajrMinutes - finalThirdDurationMinutes;

    std::string finalThirdStart = convertToHHMM(finalThirdStartMinutes, true);
    std::string middleStart = convertToHHMM(middleStartMinutes, true);
    std::string firstThirdEnd = convertToHHMM(firstThirdEndMinutes, true);
    
    std::cout << "The first third of the night ends at: " << firstThirdEnd << std::endl;
    std::cout << "The middle of the night starts at: " << middleStart << std::endl;
    std::cout << "The final third of the night starts at: " << finalThirdStart << std::endl;
    
    return 0;
}
