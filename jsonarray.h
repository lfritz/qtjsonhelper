#pragma once

#include <QJsonArray>

class QByteArray;
class JsonObject;
class QDateTime;

// Wrapper around a QJsonArray object that makes it easier to read and write
// JSON arrays.
//
// If parsing goes wrong (eg, wrong type), a JsonException is thrown.
//
// Member functions with prefix n (nString, nDateTime, putNString,
// putNDateTime) also allow null values. JSON's null value then corresponds to
// a null QString / QDateTime object. See:
// http://qt-project.org/doc/qt-5/qstring.html#isNull
// http://qt-project.org/doc/qt-5/qdatetime.html#isNull
class JsonArray {
    QJsonArray a;

public:
    // Create an empty JsonArray.
    JsonArray();

    // Create JsonArray from JSON code.
    explicit JsonArray(const QByteArray& json);

    // Create JsonArray wrapping the given QJsonArray.
    explicit JsonArray(const QJsonArray& array);

    // Get the underlying QJsonArray.
    QJsonArray get() const { return a; }

    // Get JSON code.
    QByteArray toByteArray() const;
    QString toString() const;

    // Get the number of elements in the array.
    int size() const { return a.size(); }

    // Get value (basic JSON types).
    QString string(int i) const;
    double number(int i) const;
    JsonObject object(int i) const;
    JsonArray array(int i) const;
    bool boolean(int i) const;
    bool isNull(int i) const;

    // Get value (converted from one of the basic types).
    QString nString(int i) const;
    int integer(int i) const;
    QDateTime dateTime(int i) const;
    QDateTime nDateTime(int i) const;

    // Append value (basic JSON types).
    void appendString(const QString& s);
    void appendNumber(double d);
    void appendObject(const JsonObject& o);
    void appendArray(const JsonArray& array);
    void appendBoolean(bool b);
    void appendNull();

    // Append value (converted to one of the basic types).
    void appendNString(const QString& s);
    void appendInteger(int integer);
    void appendDateTime(const QDateTime& d);
    void appendNDateTime(const QDateTime& d);
};
