#include <iostream>
#include "pugixml.hpp"

int main() {

    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("timetable.xml");

    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;

    return 0;
}
