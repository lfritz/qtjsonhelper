#include <iostream>

#include "jsonarray.h"
#include "jsonexception.h"
#include "jsonobject.h"

// Example program to show use of JsonObject and JsonArray.

// Create JSON object.
QByteArray createObject() {
    JsonArray phoneNumbers;
    phoneNumbers.appendString("212 555-1234");
    phoneNumbers.appendString("646 555-4567");
    JsonObject o;
    o.putString("name", "John Smith");
    o.putBoolean("retired", false);
    o.putInteger("age", 25);
    o.putArray("phoneNumbers", phoneNumbers);
    return o.toByteArray();
}

// Parse JSON object and print fields.
void parseObject(const QByteArray& bytes) {
    try {
        JsonObject o(bytes);
        std::cout
            << "Name: " << qPrintable(o.string("name")) << "\n"
            << "Age: " << o.integer("age") << "\n"
            << "Retired: " << (o.boolean("retired") ? "yes" : "no") << "\n"
            << "Phone numbers:\n";
        JsonArray phoneNumbers = o.array("phoneNumbers");
        for (int i = 0; i < phoneNumbers.size(); ++i)
            std::cout << qPrintable(phoneNumbers.string(i)) << "\n";
    } catch (const JsonException& e) {
        std::cout << "Error parsing JSON: " << qPrintable(e.what()) << "\n";
    }
}

int main(int, char **) {
    QByteArray bytes = createObject();
    parseObject(bytes);
}
