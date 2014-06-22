#pragma once

// Exception thrown when a JSON document cannot be read as expected.
class JsonException {
    const QString msg;
public:
    JsonException(const QString& msg) : msg(msg) { }
    QString what() const { return msg; }
};
