#include <iostream>
#include <string>
#include <vector>

class Company {
public:    
    std::string name = "unknown";
    int countTeams = 0;
    int countWorkers = 0;
    int directive = 0;
};

class Workman:public Company {
protected:
    class Team* team = nullptr;
public:    
    Workman(int& j, class Team* inTeam); // объявление конструктора Workman
    char task = 'X';
};

class Team:public Company {
public: 
    std::vector <Workman> workers;
    Team(int& i) { 
        std::cout << "\tEnter Team Manager name " << i + 1 << ": ";
        std::cin >> name;
    }
    int taskCount = 0;
    const char tasks[3] = {'A', 'B', 'C'};

    void TaskType() {
        for (int i = 0; i < taskCount; i++) {
            workers[i].task = tasks[rand() % sizeof(tasks) / sizeof(tasks[0])];
        }
    }

    void AddWorkman() {
        for (int j = 0; j < countWorkers; j++) { 
            Workman* workman = new Workman(j, this);
            workers.push_back(*workman);
            delete workman; workman = nullptr;
        }
    }
};

Workman::Workman(int& j, class Team* inTeam) { // определение конструктора Workman
    std::cout << "\t\tEnter worker name " << j + 1 << "(manager " << inTeam->name << "): ";
    std::cin >> name;
}

class Director:public Company {
public:
    std::vector <Team> teams;
    Director() {
        std::cout << "Enter the name of the Director: ";
        std::cin >> name;
    }

    void Directions() {
        for (int i = 0; i < teams.size(); i++) {
            if (!teams[i].workers.empty()) {
                teams[i].directive = this->directive + i + 1;
                std::cout << "\nThe manager was instructed " << teams[i].name << '\n';
                std::srand(teams[i].directive);
                teams[i].taskCount = std::rand() % teams[i].workers.size() + 1;
                teams[i].TaskType();
                int count = 0;
                for (int j = 0; j < teams[i].workers.size(); j++) {
                    if (teams[i].workers[j].task != 'X') {
                        count++;
                        std::cout << teams[i].workers[j].name << " task assigned " << teams[i].workers[j].task << '\n';
                    }
                }
                for (int s = 0; s < count; s++)
                    teams[i].workers.erase(teams[i].workers.begin());
            } 
        }
    }

    bool UnemployedWorkers() const {
        bool found = false;
        for (int i = 0; i < teams.size() && !found; i++) {
            if (!teams[i].workers.empty()) {
                found = true;
                std::cout << "\nRemaining unemployed workers:\n";
            }
        }

        for (int i = 0; i < teams.size(); i++) {
            if (!teams[i].workers.empty()) {
                std::cout << "Team " << teams[i].name << ":\n";
                for (int j = 0; j < teams[i].workers.size(); j++) {
                    std::cout << j + 1 << ": " << teams[i].workers[j].name << '\n';
                }
                std::cout << '\n';
            }
        }
        return found;
    }
};

int main() { 
    Director* director = new Director;
    std::cout << "Enter the number of teams: ";
    std::cin >> director->countTeams;

    for (int i = 0; i < director->countTeams; i++) {
        Team* team = new Team(i);
        std::cout << "\tEnter the number of team members " << team->name << ": ";
        std::cin >> team->countWorkers;
        team->AddWorkman();
        director->teams.push_back(*team);
        delete team; team = nullptr;
    }

    do {
        std::cout << "\nEnter the direction of the head of the company(integer identifier): ";
        std::cin >> director->directive;
        director->Directions();
    } while (director->UnemployedWorkers());
    delete director; director = nullptr;

    std::cout << "\nAll workers are busy with tasks!\n";
}