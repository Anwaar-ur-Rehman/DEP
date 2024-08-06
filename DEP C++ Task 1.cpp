#include <iostream>
#include <vector>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;

class Location {
public:
    string name;
    double latitude;
    double longitude;

    Location(string n, double lat, double lon) : name(n), latitude(lat), longitude(lon) {}

    void displayLocation() const {
        cout << "Location: " << name << ", Latitude: " << latitude << ", Longitude: " << longitude << endl;
    }
};

class LocationManager {
private:
    vector<Location> locations;

public:
    void addLocation(const Location& loc) {
        locations.push_back(loc);
    }

    void removeLocation(const string& name) {
        for (auto it = locations.begin(); it != locations.end(); ++it) {
            if (it->name == name) {
                locations.erase(it);
                break;
            }
        }
    }

    void listLocations() const {
        for (const auto& loc : locations) {
            loc.displayLocation();
        }
    }

    vector<Location> getLocations() const {
        return locations;
    }
};

class WeatherVariable {
public:
    string type;
    double value;

    WeatherVariable(string t, double v) : type(t), value(v) {}

    void displayWeatherVariable() const {
        cout << "Weather Variable: " << type << ", Value: " << value << endl;
    }
};

class WeatherForecastingSystem {
private:
    string apiKey;

public:
    WeatherForecastingSystem(const string& apiKey) : apiKey(apiKey) {}

    nlohmann::json fetchWeatherData(const string& location) {
        string url = "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=" + apiKey + "&units=metric";
        cpr::Response r = cpr::Get(cpr::Url{});

        if (r.status_code == 200) {
            return nlohmann::json::parse(r.text);
        } else {
            throw runtime_error("Failed to fetch weather data: " + to_string(r.status_code));
        }
    }

    void getWeatherForecast(const string& location) {
        try {
            nlohmann::json data = fetchWeatherData(location);
            string weatherDescription = data["weather"][0]["description"];
            double temperature = data["main"]["temp"];
            double humidity = data["main"]["humidity"];
            double windSpeed = data["wind"]["speed"];

            cout << "Weather Forecast for " << location << ": " << weatherDescription 
                 << ", Temperature: " << temperature << "°C, Humidity: " << humidity << "%, Wind Speed: " << windSpeed << " m/s" << endl;
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }
};

int main() {
    LocationManager locManager;

    locManager.addLocation(Location("Islamabad", 33.6844, 73.0479));
    locManager.addLocation(Location("Lahore", 31.5497, 74.3436));

    cout << "All Locations:" << endl;
    locManager.listLocations();

    locManager.removeLocation("Islamabad");

    cout << "\nLocations after removal:" << endl;
    locManager.listLocations();

    WeatherVariable temperature("Temperature", 25.5);
    WeatherVariable windSpeed("Wind Speed", 10.0);

    temperature.displayWeatherVariable();
    windSpeed.displayWeatherVariable();

    string apiKey = "29bc43d56695b2002be1e6d96ec518ad";
    WeatherForecastingSystem weatherSystem(apiKey);

    cout << "\nWeather Forecasts:" << endl;
    for (const auto& loc : locManager.getLocations()) {
        weatherSystem.getWeatherForecast(loc.name);
    }

    return 0;
}

