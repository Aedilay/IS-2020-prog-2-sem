#include <iostream>
#include "pugixml.hpp"
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;
using namespace pugi;


vector<string> createRoutes(xml_node data){
    string file = data.child("routes").text().as_string();
    char parse;
    if (file.find(',') != string::npos)
        parse = ',';
    else
        parse = '.';
    vector<string> routes;
    auto ss = istringstream(file);
    string temp;
    while (getline(ss, temp, parse))
        routes.push_back(temp);
    return routes;
}

pair<string, double> compare(pair<string, double> comp, double result, string change) {
    auto [route, res] = std::move(comp);
    if (res < result) {
        res = result;
        route = std::move(change);
    }
    return std::make_pair(route, res);
}

void routeWithMaxStops(xml_node timetable) {
    map<string, map<string, int>> routeAndStops;
    for (auto &data : timetable) {
        vector<string> routes = createRoutes(data);
        for (auto &route: routes){
            routeAndStops[data.child("type_of_vehicle").text().as_string()][route]++;
        }
    }
    pair <string, pair <string, int>> result;
    cout << "\nМаршруты с наибольшим количеством остановок:" << endl;
    for (auto &[trasport, otherPair]: routeAndStops) {
        auto [resultTransport, pair] = result;
        resultTransport = trasport;
        for(auto &[route, stops]: otherPair){
            pair = compare(pair, stops, route);
        }
        auto [resultRoute, maxStops] = pair;
        cout << resultTransport << " " << resultRoute << " " << maxStops << endl;
    }
}

void longestRoute(xml_node &timetable) {
    map<string, map<string, vector<pair<double, double>>>> routesAndCoords;
    for (auto &data : timetable) {
        string coords = data.child("coordinates").text().as_string();
        pair<double, double> pairCords;
        auto ss = istringstream(coords);
        string line;
        auto[coord1, coord2] = pairCords;
        getline(ss, line, ',');
        coord1 = stod(line);
        getline(ss, line, ',');
        coord2 = stod(line);
        pairCords = std::make_pair(coord1, coord2);
        vector<string> routes = createRoutes(data);
        for (auto &route: routes)
            routesAndCoords[data.child("type_of_vehicle").text().as_string()][route].push_back(pairCords);
    }
    pair<string, pair<string, double>> result;
    cout << "\nНаиболее длинные маршруты:" << endl;
    for (auto &[trasport, otherPair]: routesAndCoords) {
        auto [resultTransport, pair] = result;
        resultTransport = trasport;
        for (auto &[route, dist]: otherPair) {
            auto[x_, y_] = dist[0];
            double x = x_;
            double y = y_;
            double sum = 0;
            for (auto[coord1, coord2]: dist) {
                sum += sqrt(pow(x - coord2, 2) + pow(y - coord1, 2));
                y = coord1;
                x = coord2;
            }
            pair = compare(pair, sum, route);
        }
        auto [resultRoute, resultDist] = pair;
        cout << resultTransport << ' ' << resultRoute << ' ' << resultDist << endl;
        resultDist = 0;
    }
}

void streetWithMaxStops(xml_node timetable) {
    map<string, int> stops;
    for (auto &data : timetable) {
        string location = data.child("location").text().as_string();
        if (!location.empty()) {
            if (location.find(',') != string::npos)
                stops[data.child("location").text().as_string()]++;
            else{
                char parse = ',';
                auto ss = istringstream(location);
                string line;
                while (getline(ss, line, parse))
                    stops[line]++;
            }
        }
    }
    pair<string, int> result;
    for (auto &[street, num]: stops){
        result = compare(result, num, street);
    }
    auto [resultStreet, resultNum] = result;
    cout << endl;
    cout << "Улица с наибольшим числом остановок:" << '\n' << resultStreet << ' ' << resultNum << endl;
}


int main() {
    system("chcp 65001");
    xml_document doc;
    doc.load_file("timetable.xml");
    auto timetable = doc.child("dataset");
    routeWithMaxStops(timetable);
    longestRoute(timetable);
    streetWithMaxStops(timetable);
    return 0;
}
