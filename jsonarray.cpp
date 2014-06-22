#include "jsonarray.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonParseError>

#include "jsonobject.h"
#include "jsonexception.h"

void wrongType(const QString &type, int i) {
    throw JsonException("expected " + type +
                        " for array element " + QString::number(i));
}


JsonArray::JsonArray() : a() { }

JsonArray::JsonArray(const QByteArray& json) {
    QJsonParseError pe;
    QJsonDocument doc = QJsonDocument::fromJson(json, &pe);
    if (pe.error != QJsonParseError::NoError)
        throw JsonException("cannot parse JSON: " + pe.errorString());
    if ( ! doc.isArray())
        throw JsonException("expected array");
    a = doc.array();
}

JsonArray::JsonArray(const QJsonArray& array) : a(array) { }

QByteArray JsonArray::toByteArray() const {
    QJsonDocument doc(a);
    return doc.toJson();
}

QString JsonArray::toString() const {
    return QString(toByteArray());
}

QString JsonArray::string(int i) const {
    QJsonValue value = a.at(i);
    if ( ! value.isString())
        wrongType("string", i);
    return value.toString();
}
double JsonArray::number(int i) const {
    QJsonValue value = a.at(i);
    if ( ! value.isDouble())
        wrongType("number", i);
    return value.toDouble();
}
JsonObject JsonArray::object(int i) const {
    QJsonValue value = a.at(i);
    if ( ! value.isObject())
        wrongType("object", i);
    return JsonObject(value.toObject());
}
JsonArray JsonArray::array(int i) const {
    QJsonValue value = a.at(i);
    if ( ! value.isArray())
        wrongType("array", i);
    return JsonArray(value.toArray());
}
bool JsonArray::boolean(int i) const {
    QJsonValue value = a.at(i);
    if ( ! value.isBool())
        wrongType("'true' or 'false'", i);
    return value.toBool();
}
bool JsonArray::isNull(int i) const {
    return a.at(i).isNull();
}

QString JsonArray::nString(int i) const {
    if (isNull(i))
        return QString();
    return string(i);
}
int JsonArray::integer(int i) const {
    double d = number(i);
    int integer = (int)d;
    if ((double)integer != d)
        wrongType("integer", i);
    return integer;
}
QDateTime JsonArray::dateTime(int i) const {
    QString s = string(i);
    return QDateTime::fromString(s, Qt::ISODate);
}
QDateTime JsonArray::nDateTime(int i) const {
    if (isNull(i))
        return QDateTime();
    return dateTime(i);
}

void JsonArray::appendString(const QString& s) {
    a.append(QJsonValue(s));
}
void JsonArray::appendNumber(double d) {
    a.append(QJsonValue(d));
}
void JsonArray::appendObject(const JsonObject& o) {
    a.append(QJsonValue(o.get()));
}
void JsonArray::appendArray(const JsonArray& array) {
    a.append(array.get());
}
void JsonArray::appendBoolean(bool b) {
    a.append(QJsonValue(b));
}
void JsonArray::appendNull() {
    a.append(QJsonValue());
}

void JsonArray::appendNString(const QString& s) {
    if (s.isNull())
        appendNull();
    else
        appendString(s);
}
void JsonArray::appendInteger(int integer) {
    appendNumber(integer);
}
void JsonArray::appendDateTime(const QDateTime& d) {
    appendString(d.toString(Qt::ISODate));
}
void JsonArray::appendNDateTime(const QDateTime& d) {
    if (d.isNull())
        appendNull();
    else
        appendDateTime(d);
}
