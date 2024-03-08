#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for seeding rand()

using namespace std;

class Process {
private:
    int uniqueID; // Unique identifier of a process
    std::vector<int> tickets; // a vector holding the tickets in a process

public:
    // Public initializer
    Process(int id, const std::vector<int>& ticketList) : uniqueID(id), tickets(ticketList) {}

    // A public function that returns the unique identifier of a process
    int getUniqueID() const { return uniqueID; }

    // A public function that returns the tickets in a process
    std::vector<int>& getTickets() { return tickets; }

    // A function that returns the sum of tickets in a process
    int sumOfTickets() {
        int result = 0;
        for (int ticket : getTickets()) {
            result += ticket;
        }
        return result;
    }
};

class Scheduler {
private:
    std::vector<Process> processList;
    int totalTickets;

public:
    Scheduler() : totalTickets(0) {}

    void addNewProcess(Process& newProcess) {
        processList.push_back(newProcess); // Adds new process to process list

        totalTickets += newProcess.sumOfTickets(); // Adds sum of new ticket to totalTickets
    }
    void allocateTickets() {
        for (auto& process : processList) { // Iterate by reference to modify tickets
            std::vector<int>& processTickets = process.getTickets();
            for (int& ticket : processTickets) { // Iterate by reference to modify tickets
                ticket = std::max(1, ticket);
            }
        }
    }

    int generateRandomTicket() {
        int result = rand() % totalTickets + 1; // Generates a random number in the range 1...totalTickets
        return result;
    }

    // The function to select the next process using the random number generator
    const Process* selectNextProcess() {
        int randomTicket = generateRandomTicket();
        std::cout << "Random number is: " << randomTicket << std::endl;

        for (auto& existingProcess : processList) {
            for (int ticket : existingProcess.getTickets()) {
                if (randomTicket <= ticket) {
                    return &existingProcess;
                }
                randomTicket -= ticket;
            }
        }
        return nullptr;
    }

};

int main() {
    srand(time(nullptr)); // Seed the random number generator with current time

    // Example usage
    Process process1(1, { 5, 3, 2 });
    Process process2(2, { 10, 6 });
    Process process3(3, { 3 });

    Scheduler scheduler;
    scheduler.addNewProcess(process1);
    scheduler.addNewProcess(process2);
    scheduler.addNewProcess(process3);

    scheduler.allocateTickets();

    const Process* nextProcess = scheduler.selectNextProcess();
    if (nextProcess) {
        std::cout << "Process " << nextProcess->getUniqueID() << " wins the lottery!" << std::endl;
    }
    else {
        std::cout << "No processes to select from." << std::endl;
    }

    return 0;
}