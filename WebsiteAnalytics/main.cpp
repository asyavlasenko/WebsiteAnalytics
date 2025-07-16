#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

using UserVisits = std::unordered_map<std::string, std::unordered_set<std::string>>;

UserVisits parse_csv(const std::string& filename) {
    UserVisits visits;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);

    std::string user_id, product_id, timestamp;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, user_id, ',');
        std::getline(ss, product_id, ',');
        std::getline(ss, timestamp, ',');
        visits[user_id].insert(product_id);
    }
    return visits;
}

std::vector<std::string> find_users_with_new_visits(
    const UserVisits& visits_day1,
    const UserVisits& visits_day2
) {
    std::vector<std::string> result;

    for (const auto& [user, day2_products] : visits_day2) {
        if (!visits_day1.count(user)) continue;

        const auto& day1_products = visits_day1.at(user);
        for (const std::string& product : day2_products) {
            if (!day1_products.count(product)) {
                result.push_back(user);
                break;
            }
        }
    }

    return result;
}

void print_users(const std::vector<std::string>& users) {
    std::cout << "=== Users who visited NEW products on Day 2 ===\n\n";
    for (const std::string& user : users) {
        std::cout << "[+] " << user << '\n';
    }
    std::cout << "\nTotal users: " << users.size() << '\n';
}

int main() {
    std::string file1 = "data/day1.csv";
    std::string file2 = "data/day2.csv";

    UserVisits day1 = parse_csv(file1);
    UserVisits day2 = parse_csv(file2);

    std::vector<std::string> new_users = find_users_with_new_visits(day1, day2);
    print_users(new_users);

    return 0;
}
