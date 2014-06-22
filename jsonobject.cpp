#include "jsonobject.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonParseError>

#include "jsonarray.h"
#include "jsonexception.h"

void wrongType(const QString& type, const QString& key) {
    throw JsonException("expected " + type + " for " + key);
}

JsonObject::JsonObject() : o() { }

JsonObject::JsonObject(const QByteArray& json) {
    QJsonParseError pe;
    QJsonDocument doc = QJsonDocument::fromJson(json, &pe);
    if (pe.error != QJsonParseError::NoError)
        throw JsonException("cannot parse JSON: " + pe.errorString());
    if ( ! doc.isObject()) {
        throw JsonException("expected object");
    }
    o = doc.object();
}

JsonObject::JsonObject(const QJsonObject& object) : o(object) { }

QByteArray JsonObject::toByteArray() const {
    QJsonDocument doc(o);
    return doc.toJson();
}

QString JsonObject::toString() const {
    return QString(toByteArray());
}

bool JsonObject::contains(const QString& key) const {
    return o.contains(key);
}

void JsonObject::checkContains(const QString& key) const {
    if ( ! contains(key))
        throw JsonException("expected value for " + key);
}

QString JsonObject::string(const QString& key) const {
    checkContains(key);
    QJsonValue value = o.value(key);
    if ( ! value.isString())
        wrongType("string", key);
    return value.toString();
}

double JsonObject::number(const QString& key) const {
    checkContains(key);
    QJsonValue value = o.value(key);
    if ( ! value.isDouble())
        wrongType("number", key);
    return value.toDouble();
}

JsonObject JsonObject::object(const QString& key) const {
    checkContains(key);
    QJsonValue value = o.value(key);
    if ( ! value.isObject())
        wrongType("object", key);
    return JsonObject(value.toObject());
}

JsonArray JsonObject::array(const QString& key) const {
    checkContains(key);
    QJsonValue value = o.value(key);
    if ( ! value.isArray())
        wrongType("array", key);
    return JsonArray(value.toArray());
}

bool JsonObject::boolean(const QString& key) const {
    checkContains(key);
    QJsonValue value = o.value(key);
    if ( ! value.isBool())
        wrongType("'true' or 'false'", key);
    return value.toBool();
}

bool JsonObject::isNull(const QString& key) const {
    checkContains(key);
    return o.value(key).isNull();
}

QString JsonObject::nString(const QString& key) const {
    if (isNull(key))
        return QString();
    return string(key);
}

int JsonObject::integer(const QString& key) const {
    double d = number(key);
    int integer = (int)d;
    if ((double)integer != d)
        wrongType("integer", key);
    return integer;
}

QDateTime JsonObject::dateTime(const QString& key) const {
    QString s = string(key);
    return QDateTime::fromString(s, Qt::ISODate);
}

QDateTime JsonObject::nDateTime(const QString& key) const {
    if (isNull(key))
        return QDateTime();
    return dateTime(key);
}

void JsonObject::putString(const QString& key, const QString& value) {
    o.insert(key, QJsonValue(value));
}
void JsonObject::putNumber(const QString& key, double value) {
    o.insert(key, QJsonValue(value));
}
void JsonObject::putObject(const QString& key, const JsonObject& value) {
    o.insert(key, value.get());
}
void JsonObject::putArray(const QString& key, const JsonArray& value) {
    o.insert(key, value.get());
}
void JsonObject::putBoolean(const QString& key, bool value) {
    o.insert(key, QJsonValue(value));
}
void JsonObject::putNull(const QString& key) {
    o.insert(key, QJsonValue());
}

void JsonObject::putNString(const QString& key, const QString& value) {
    if (value.isNull())
        putNull(key);
    else
        putString(key, value);
}
void JsonObject::putInteger(const QString& key, int value) {
    putNumber(key, value);
}
void JsonObject::putDateTime(const QString& key, const QDateTime& value) {
    putString(key, value.toString(Qt::ISODate));
}
void JsonObject::putNDateTime(const QString& key, const QDateTime& value) {
    if (value.isNull())
        putNull(key);
    else
        putDateTime(key, value);
}
