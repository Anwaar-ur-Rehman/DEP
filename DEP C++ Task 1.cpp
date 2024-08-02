#include <iostream>
#include <vector>
#include <string>

// Location Class
class Location {
public:
    std::string name;
    double latitude;
    double longitude;

    Location(std::string n, double lat, double lon) : name(n), latitude(lat), longitude(lon) {}

    void displayLocation() const {
        std::cout << "Location: " << name << ", Latitude: " << latitude << ", Longitude: " << longitude << std::endl;
    }
};

// LocationManager Class
class LocationManager {
private:
    std::vector<Location> locations;

public:
    void addLocation(const Location& loc) {
        locations.push_back(loc);
    }

    void removeLocation(const std::string& name) {
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
};

// WeatherVariable Class
class WeatherVariable {
public:
    std::string type;
    double value;

    WeatherVariable(std::string t, double v) : type(t), value(v) {}

    void displayWeatherVariable() const {
        std::cout << "Weather Variable: " << type << ", Value: " << value << std::endl;
    }
};

// WeatherForecastingSystem Class
class WeatherForecastingSystem {
public:
    // Mock function to simulate API call
    std::string fetchWeatherData(const std::string& location) {
        // Simulated API response
        return "Sunny, 25°C";
    }

    void getWeatherForecast(const std::string& location) {
        std::string data = fetchWeatherData(location);
        std::cout << "Weather Forecast for " << location << ": " << data << std::endl;
    }
};

int main() {
    LocationManager locManager;

    // Adding locations
    locManager.addLocation(Location("New York", 40.7128, -74.0060));
    locManager.addLocation(Location("San Francisco", 37.7749, -122.4194));

    // Listing locations
    std::cout << "All Locations:" << std::endl;
    locManager.listLocations();

    // Removing a location
    locManager.removeLocation("New York");

    // Listing locations after removal
    std::cout << "\nLocations after removal:" << std::endl;
    locManager.listLocations();

    // Creating weather variables
    WeatherVariable temperature("Temperature", 25.5);
    WeatherVariable windSpeed("Wind Speed", 10.0);

    // Displaying weather variables
    temperature.displayWeatherVariable();
    windSpeed.displayWeatherVariable();

    // Fetching and displaying weather forecast for a location
    WeatherForecastingSystem weatherSystem;
    weatherSystem.getWeatherForecast("San Francisco");

    return 0;
}
