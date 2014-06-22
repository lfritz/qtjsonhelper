#pragma once

#include <QJsonObject>

class QByteArray;
class QDateTime;
class JsonArray;

// Wrapper around a QJsonObject object that makes it easier to read and write
// JSON.
//
// If parsing goes wrong (eg, a field is missing), a JsonException is thrown.
//
// Member functions with prefix n (nString, nDateTime, putNString,
// putNDateTime) also allow null values. JSON's null value then corresponds to
// a null QString / QDateTime object. See:
// http://qt-project.org/doc/qt-5/qstring.html#isNull
// http://qt-project.org/doc/qt-5/qdatetime.html#isNull
class JsonObject {
    QJsonObject o;

public:
    // Create an empty JsonObject.
    JsonObject();

    // Create JsonObject from JSON code.
    explicit JsonObject(const QByteArray& json);

    // Create JsonObject wrapping a given QJsonObject.
    explicit JsonObject(const QJsonObject& object);

    // Get the underlying QJsonObject.
    QJsonObject get() const { return o; }

    // Get JSON code.
    QByteArray toByteArray() const;
    QString toString() const;

    // Does the object contain the key?
    bool contains(const QString& key) const;

    // Throw JsonException if the object does not contain the key.
    void checkContains(const QString& key) const;

    // Get value (basic JSON types).
    QString string(const QString& key) const;
    double number(const QString& key) const;
    JsonObject object(const QString& key) const;
    JsonArray array(const QString& key) const;
    bool boolean(const QString& key) const;
    bool isNull(const QString& key) const;

    // Get value (converted from one of the basic types).
    QString nString(const QString& key) const;
    int integer(const QString& key) const;
    QDateTime dateTime(const QString& key) const;
    QDateTime nDateTime(const QString& key) const;

    // Put value (basic JSON types).
    void putString(const QString& key, const QString& value);
    void putNumber(const QString& key, double value);
    void putObject(const QString& key, const JsonObject& value);
    void putArray(const QString& key, const JsonArray& value);
    void putBoolean(const QString& key, bool value);
    void putNull(const QString& key);

    // Put value (converted to one of the basic types).
    void putNString(const QString& key, const QString& value);
    void putInteger(const QString& key, int value);
    void putDateTime(const QString& key, const QDateTime& value);
    void putNDateTime(const QString& key, const QDateTime& value);
};
