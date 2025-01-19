#define _USE_MATH_DEFINES // Umożliwia dostęp do stałych matematycznych
#include <cmath>
#include <iostream>

// Klasa RobotStary
class RobotStary {
public:
    virtual void idzDo(double x, double y) {
        std::cout << "RobotStary: Ide do punktu (" << x << ", " << y << ") w ukladzie wspolrzędnych prostokatnych.\n";
    }
};

// Klasa RobotNowy
class RobotNowy {
public:
    void idzDo(double kat, double odleglosc) {
        std::cout << "RobotNowy: Ide do punktu o kacie " << kat << " stopni i odleglosci " << odleglosc << ".\n";
    }
};

// Klasa AdapterRobota
class AdapterRobota : public RobotStary {
private:
    RobotNowy* nowyRobot;

public:
    AdapterRobota(RobotNowy* robot) : nowyRobot(robot) {}

    void idzDo(double x, double y) override {
        // Konwersja współrzędnych prostokątnych na biegunowe
        double odleglosc = std::sqrt(x * x + y * y);
        double kat = std::atan2(y, x) * (180.0 / M_PI); // Kąt w stopniach
        nowyRobot->idzDo(kat, odleglosc);
    }
};

// Funkcja główna
int main() {
    RobotNowy nowy;
    AdapterRobota adapter(&nowy);

    double x, y;

    // Pobieranie współrzędnych od użytkownika
    std::cout << "Podaj wspolrzedne prostokatne (x, y):\n";
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;

    // Przekazanie współrzędnych do adaptera
    adapter.idzDo(x, y);

    return 0;
}
