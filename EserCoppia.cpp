#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

struct Task {
    std::string description;
    std::string deadline;
    bool completed;
};

struct Project {
    std::string name;
    std::vector<Task> tasks;
};

std::vector<Project> projects;

void saveData() {
    std::ofstream file("data.txt");
    if (file.is_open()) {
        for (const auto& project : projects) {
            file << project.name << std::endl;
            for (const auto& task : project.tasks) {
                file << task.description << ","
                     << task.deadline << ","
                     << task.completed << std::endl;
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Data saved successfully." << std::endl;
    } else {
        std::cout << "Failed to save data." << std::endl;
    }
}

void loadData() {
    std::ifstream file("data.txt");
    if (file.is_open()) {
        projects.clear();
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            Project project;
            project.name = line;
            while (std::getline(file, line) && !line.empty()) {
                Task task;
                size_t pos = line.find(',');
                task.description = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(',');
                task.deadline = line.substr(0, pos);
                line.erase(0, pos + 1);
                task.completed = (line == "1");
                project.tasks.push_back(task);
            }
            projects.push_back(project);
        }
        file.close();
        std::cout << "Data loaded successfully." << std::endl;
    } else {
        std::cout << "Failed to load data." << std::endl;
    }
}

void displayProjects() {
    std::cout << "Projects:" << std::endl;
    for (const auto& project : projects) {
        std::cout << "- " << project.name << std::endl;
    }
}

void createProject() {
    std::string projectName;
    std::cout << "Enter project name: ";
    std::cin.ignore();
    std::getline(std::cin, projectName);

    projects.push_back({projectName, {}});
    std::cout << "Project created successfully." << std::endl;
    saveData();
}

void openProject() {
    std::string projectName;
    std::cout << "Enter project name: ";
    std::cin.ignore();
    std::getline(std::cin, projectName);

    for (auto& project : projects) {
        if (project.name == projectName) {
            // Display project tasks
            std::cout << "Tasks for project " << projectName << ":" << std::endl;
            for (const auto& task : project.tasks) {
                std::cout << "- " << task.description << " (Deadline: " << task.deadline << ")";
                if (task.completed) {
                    std::cout << " [Completed]";
                }
                std::cout << std::endl;
            }
            return;
        }
    }

    std::cout << "Project not found." << std::endl;
}

void delete

