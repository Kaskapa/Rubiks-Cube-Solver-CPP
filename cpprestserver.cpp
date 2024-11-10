#include "idaStarF2l.h"
#include "idaStarCross.h"

#include <iostream>
#include <served/served.hpp>
#include <future>  // For async threading


// Inline helper function to get move string
inline std::string getMoveString(int move) {
    return ACTIONS.at(move) + " ";
}

// Function to process the solution
std::string process_solution(const std::string &scramble) {
    std::vector<int> crossSol = getCrossSolution(scramble);

    std::string crossSolution;
    for (int move : crossSol) {
        crossSolution += getMoveString(move);
    }

    std::vector<std::vector<std::vector<int>>> allSol = getSolutions(scramble, crossSolution);
    std::ostringstream response;

    response << "{\n";
    response << "  \"cross_solution\":[\n";
    response << "    \"";
    for (int move : crossSol) {
        response << getMoveString(move);
    }
    response << "\"\n";
    response << "  ],\n";

    int counter = 0;
    for (const auto &f2l_sol : allSol) {
        response << "  \"solution" << counter++ << "\":[\n";
        for (size_t i = 0; i < f2l_sol.size(); ++i) {
            response << "    \"";
            for (int move : f2l_sol[i]) {
                response << getMoveString(move);
            }
            response << "\"";
            if (i != f2l_sol.size() - 1) {
                response << ",";
            }
            response << "\n";
        }
        response << "  ]";
        if (counter != allSol.size()) {
            response << ",";
        }
        response << "\n";
    }

    response << "}\n";
    return response.str();
}

int main(int argc, const char *argv[]) {
    served::multiplexer mux;

    mux.handle("/api/v1/greeting")
        .get([](served::response &res, const served::request &req) {
            // Extract scramble query parameter
            std::string scramble = req.query["scramble"];

            // Process each request asynchronously
            auto future_result = std::async(std::launch::async, process_solution, scramble);
            std::string result = future_result.get();

            // Set response
            res.set_header("content-type", "application/json");
            res << result;
        });

    std::cout << "Try this example with:" << std::endl;
    std::cout << "  curl \"http://localhost:8123/api/v1/greeting?scramble='R U R U'\"" << std::endl;

    // Run server with multiple threads
    served::net::server server("127.0.0.1", "8123", mux);
    server.run(10);  // 10 threads for handling requests

    return (EXIT_SUCCESS);
}