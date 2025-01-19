#include <iostream>
#include <memory>
#include <string>

// Klasa bazowa Robot
class Robot {
public:
    virtual ~Robot() = default;
    virtual void operacja() const = 0; // Metoda wspólna dla wszystkich robotów
};

// Klasa RobotPodstawowy (konkretny robot)
class RobotPodstawowy : public Robot {
public:
    void operacja() const override {
        std::cout << "Robot: porusza sie.\n";
    }
};

// Klasa bazowa dekoratora
class RobotDekorator : public Robot {
protected:
    std::shared_ptr<Robot> robot; // Dekorowany obiekt
public:
    explicit RobotDekorator(std::shared_ptr<Robot> r) : robot(std::move(r)) {}
    virtual void operacja() const override {
        robot->operacja(); // Wywołanie operacji bazowego robota
    }
};

// Klasa dekoratora RobotZKamera
class RobotZKamera : public RobotDekorator {
public:
    explicit RobotZKamera(std::shared_ptr<Robot> r) : RobotDekorator(std::move(r)) {}
    void operacja() const override {
        RobotDekorator::operacja();
        std::cout << "Robot: ma kamere.\n";
    }
};

// Klasa dekoratora RobotZCzujnikiemTemperatury
class RobotZCzujnikiemTemperatury : public RobotDekorator {
public:
    explicit RobotZCzujnikiemTemperatury(std::shared_ptr<Robot> r) : RobotDekorator(std::move(r)) {}
    void operacja() const override {
        RobotDekorator::operacja();
        std::cout << "Robot: ma czujnik temperatury.\n";
    }
};

// Klasa dekoratora RobotZDzwiekiem
class RobotZDzwiekiem : public RobotDekorator {
public:
    explicit RobotZDzwiekiem(std::shared_ptr<Robot> r) : RobotDekorator(std::move(r)) {}
    void operacja() const override {
        RobotDekorator::operacja();
        std::cout << "Robot: ma system dzwiekowy.\n";
    }
};

// Funkcja główna
int main() {
    // Tworzenie podstawowego robota
    std::shared_ptr<Robot> robot = std::make_shared<RobotPodstawowy>();
    std::string wybor;

    std::cout << "Witaj w systemie robota!\n";
    std::cout << "Mozesz dodawac funkcjonalnosci wpisujac polecenia:\n";
    std::cout << "  - kamera: Dodaje kamere\n";
    std::cout << "  - temperatura: Dodaje czujnik temperatury\n";
    std::cout << "  - dzwiek: Dodaje system dzwiekowy\n";
    std::cout << "  - koniec: Wyswietla wszystkie funkcjonalnosci i konczy program\n\n";

    while (true) {
        std::cout << "Wpisz polecenie: ";
        std::cin >> wybor;

        if (wybor == "kamera") {
            robot = std::make_shared<RobotZKamera>(robot);
            std::cout << "Dodano kamere do robota.\n";
        }
        else if (wybor == "temperatura") {
            robot = std::make_shared<RobotZCzujnikiemTemperatury>(robot);
            std::cout << "Dodano czujnik temperatury do robota.\n";
        }
        else if (wybor == "dzwiek") {
            robot = std::make_shared<RobotZDzwiekiem>(robot);
            std::cout << "Dodano system dzwiekowy do robota.\n";
        }
        else if (wybor == "koniec") {
            std::cout << "\nOstateczna konfiguracja robota:\n";
            robot->operacja();
            break;
        }
        else {
            std::cout << "Nieznane polecenie. Spróbuj ponownie.\n";
        }
    }

    return 0;
}
