# QtJsonHelper
QtJsonHelper is a set of classes for reading and writing JSON (http://json.org/). It uses the JSON classes in Qt 5 (http://qt-project.org/doc/qt-5/json.html) but provides a higher-level interface.

## Rationale
Since version 5.0, Qt includes classes to read and write JSON. While these aren't difficult to use, they can require a lot of boilerplate code, especially if you're parsing JSON and you want to have proper error checks. For example, the following code extracts a single field from a JSON object:

    QJsonParseError pe;
    QJsonDocument doc = QJsonDocument::fromJson(json, &pe);
    if (pe.error != QJsonParseError::NoError) {
        std::cout << "Error: " << qPrintable(pe.errorString()) << "\n";
        return;
    }
    if ( ! doc.isObject()) {
        std::cout << "Error: expected JSON object\n";
        return;
    }
    QJsonObject o = doc.object();
    if ( ! o.contains("name")) {
        std::cout << "Error: missing element 'name'\n";
        return;
    }
    QJsonValue nameValue = o.value("name");
    if ( ! nameValue.isString()) {
        std::cout << "Error: element 'name' should be a string.\n";
        return;
    }
    QString name = nameValue.toString();
    std::cout << "name: " << qPrintable(name) << "\n";

Here's the corresponding code using QtJsonHelper:

    try {
        JsonObject o(json);
        QString name = o.string("name");
        std::cout << "name: " << qPrintable(name) << "\n";
    } catch (const JsonException& e) {
        std::cout << "Error parsing JSON: " << qPrintable(e.what()) << "\n";
    }

## Use
The easiest way to use the classes is to simply copy the source and header files (except `main.cpp`) into your C++ source code directory. Alternatively, you can change `qtjsonhelper.pro` to build a static or dynamic library from Qt Creator or using qmake directly.

See `main.cpp` for an example of how to use the API.

## License
The code is copyright (c) 2014 Brain Innovation B.V., Maastricht, The Netherlands. It is open source under the terms of the MIT license (see accompanying file LICENSE).
