#include <iostream>
#include "Board.h"
#include "timing.h"

void print_usage() {
    std::cout << "Usage: gol --load <filename> --save <filename> --generations <n> --measure\n";
}

int main(int argc, char* argv[]) {
    std::string input_file, output_file;
    int generations = 0;
    bool measure = false;

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--load") {
            input_file = argv[++i];
        } else if (std::string(argv[i]) == "--save") {
            output_file = argv[++i];
        } else if (std::string(argv[i]) == "--generations") {
            generations = std::stoi(argv[++i]);
        } else if (std::string(argv[i]) == "--measure") {
            measure = true;
        }
    }

    if (input_file.empty() || output_file.empty() || generations <= 0) {
        print_usage();
        return -1;
    }

    Timing* timing = Timing::getInstance();
    timing->startSetup();
    GameBoard board(0, 0);
    board.loadFromFile(input_file);
    timing->stopSetup();

    timing->startComputation();
    for (int gen = 0; gen < generations; ++gen) {
        board.advanceGeneration();
    }
    timing->stopComputation();

    timing->startFinalization();
    board.saveToFile(output_file);
    timing->stopFinalization();

    if (measure) {
        std::cout << timing->getResults() << "\n";
    }

    return 0;
}
