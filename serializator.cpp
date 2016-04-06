#include "serializator.h"

serializator::serializator(QTextStream * stream)
{
    out = stream;
    *out << "{\n";
}

serializator::~serializator() { }


serializator * serializator::add(QString attr, int val, bool final) {
    *out << QString("\t\"%1\": %2%3\n").arg(attr).arg(val).arg(final ? "" : ",");
    return this;
}

serializator * serializator::add(QString attr, QString val, bool final) {
    *out << QString("\t\"%1\": \"%2\"%3\n").arg(attr).arg(val).arg(final ? "" : ",");
    return this;
}

serializator * serializator::add(QString attr, QVector< QPair<QPointF, int> > &val, bool final) {
    *out << QString("\t\"%1\": [\n").arg(attr);

    for(int i = 0; i < val.size()-1; i++) {
        *out << QString("\t\t{ \"x\": %1, \"y\": %2, \"time\": %3 },\n").arg(val[i].first.x()).arg(val[i].first.y()).arg(val[i].second);
    }
    *out << QString("\t\t{ \"x\": %1, \"y\": %2, \"time\": %3 }\n").arg(val.last().first.x()).arg(val.last().first.y()).arg(val.last().second);

    *out << QString("\t]%1\n").arg(final ? "" : ",");
    return this;
}

void serializator::end() {
    *out << "\n}\n";
}
