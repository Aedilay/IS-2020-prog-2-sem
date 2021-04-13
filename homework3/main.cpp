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
    if (comp.second < result) {
        comp.second = result;
        comp.first = std::move(change);
    }
    return comp;
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
    for (auto &each: routeAndStops) {
        for(auto &res: each.second){
            result.first = each.first;
            result.second = compare(result.second, res.second, res.first);
        }
        cout << result.first << " " << result.second.first << " " << result.second.second << endl;
        result.second.first = "";
        result.second.second = 0;
    }
}

void longestRoute(xml_node &timetable) {
    map<string, map<string, vector<pair<double, double>>>> routesAndCoords;
    for (auto &data : timetable) {
        string coords = data.child("coordinates").text().as_string();
        pair<double, double> pairCords;
        auto ss = istringstream(coords);
        string line;
        getline(ss, line, ',');
        pairCords.first = stod(line);
        getline(ss, line, ',');
        pairCords.second = stod(line);
        vector<string> routes = createRoutes(data);
        for (auto &route: routes)
            routesAndCoords[data.child("type_of_vehicle").text().as_string()][route].push_back(pairCords);
    }
    pair<string, pair<string, double>> result;
    cout << "\nНаиболее длинные маршруты:" << endl;
    for (auto &each: routesAndCoords) {
        for (auto &res: each.second) {
            result.first = each.first;
            double x2 = res.second[0].second;
            double x1 = res.second[0].first;
            double sum = 0;
            for (auto coords: res.second) {
                sum += sqrt(pow(x2 - x1, 2) + pow(coords.second - coords.first, 2));
                x1 = coords.first;
                x2 = coords.second;
            }
            result.second = compare(result.second, sum, res.first);
        }
        cout << result.first << ' ' << result.second.first << ' ' << result.second.second << endl;
        result.second.first = "";
        result.second.second = 0;
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
    for (auto &each: stops){
        result = compare(result, each.second, each.first);
    }
    cout << endl;
    cout << "Улица с наибольшим числом остановок:" << '\n' << result.first << ' ' << result.second << endl;
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
