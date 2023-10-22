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

std::string convertToHHMM(int minutes) {
    int hours = minutes / 60;
    minutes %= 60;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes;
    return ss.str();
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <00:00> <23:59>" << std::endl;
        std::cerr << "       " << argv[0] << " <Fajr Time> <Isha Time>" << std::endl;
        return 1;
    }
    std::string fajrTime = argv[1]; 
    std::string ishaTime = argv[2];
    
    int fajrMinutes = convertToMinutes(fajrTime);
    int ishaMinutes = convertToMinutes(ishaTime);
    int midnightTime = convertToMinutes("24:00");
    
    int nightDurationMinutes = (midnightTime - ishaMinutes) + fajrMinutes;
    int finalThirdDurationMinutes = std::round(nightDurationMinutes / 3.0);
    
    int finalThirdStartMinutes = fajrMinutes - finalThirdDurationMinutes;
    int firstThirdEndMinutes = ishaMinutes + finalThirdDurationMinutes;
    
    std::string finalThirdStart = convertToHHMM(finalThirdStartMinutes);
    std::string firstThirdEnd = convertToHHMM(firstThirdEndMinutes);
    
    std::cout << "The first third of the night ends at: " << firstThirdEnd << std::endl;
    std::cout << "The final third of the night starts at: " << finalThirdStart << std::endl;
    
    return 0;
}