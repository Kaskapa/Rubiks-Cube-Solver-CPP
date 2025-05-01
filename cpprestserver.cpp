#include "idaStarF2l.h"
#include "idaStarCross.h"

#include <iostream>
#include <served/served.hpp>
#include <future>  // For async threading

// Function to process the solution
std::string process_solution(const std::string &scramble) {
    std::vector<int> crossSol = getCrossSolution(scramble);

    std::string crossSolution;
    for (int move : crossSol) {
        crossSolution += ACTIONS.at(move) + " ";
    }

    std::vector<std::vector<std::vector<int>>> allSol = getSolutions(scramble, crossSolution);
    std::ostringstream response;

    response << "{\n";
    response << "  \"cross_solution\":[\n";
    response << "    \"";
    for (int move : crossSol) {
        response << ACTIONS.at(move) << " ";
    }
    response << "\"\n";
    response << "  ],\n";

    int counter = 0;
    for (const auto &f2l_sol : allSol) {
        response << "  \"solution" << counter++ << "\":[\n";
        for (size_t i = 0; i < f2l_sol.size(); ++i) {
            response << "    \"";
            for (int move : f2l_sol[i]) {
                response << ACTIONS.at(move) << " ";
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

std::string process_solution_one_by_one(const std::string &scramble, const std::vector<int> &order) {
    std::vector<int> crossSol = getCrossSolution(scramble);

    std::string crossSolution;
    for (int move : crossSol) {
        crossSolution += ACTIONS.at(move) + " ";
    }

    std::vector<std::vector<std::vector<int>>> allSol = getSolutionsOneByOne(scramble, crossSolution, order);
    std::ostringstream response;

    response << "{\n";
    response << "  \"cross_solution\":[\n";
    response << "    \"";
    for (int move : crossSol) {
        response << ACTIONS.at(move) << " ";
    }
    response << "\"\n";
    response << "  ],\n";

    int counter = 0;
    for (const auto &f2l_sol : allSol) {
        response << "  \"solution" << counter++ << "\":[\n";
        for (size_t i = 0; i < f2l_sol.size(); ++i) {
            response << "    \"";
            for (int move : f2l_sol[i]) {
                response << ACTIONS.at(move) << " ";
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

    mux.handle("/api/v1/greeting_one_by_one")
        .get([](served::response &res, const served::request &req) {
            // Extract scramble and order query parameters
            std::string scramble = req.query["scramble"];
            std::string order_str = req.query["order"];

            // Convert order string to vector of integers
            std::vector<int> order;
            std::istringstream iss(order_str);
            std::string token;
            while (std::getline(iss, token, ',')) {
                order.push_back(std::stoi(token));
            }

            // Process each request asynchronously
            auto future_result = std::async(std::launch::async, process_solution_one_by_one, scramble, order);
            std::string result = future_result.get();

            // Set response
            res.set_header("content-type", "application/json");
            res << result;
        });

    std::cout << "Try these examples with:" << std::endl;
    std::cout << "  curl \"http://localhost:8123/api/v1/greeting?scramble='R U R U'\"" << std::endl;
    std::cout << "  curl \"http://localhost:8123/api/v1/greeting_one_by_one?scramble='R U R U'&order=1,2,3,4\"" << std::endl;

    // Run server with multiple threads
    served::net::server server("0.0.0.0", "8123", mux);
    server.run(10);  // 10 threads for handling requests

    return (EXIT_SUCCESS);
}
