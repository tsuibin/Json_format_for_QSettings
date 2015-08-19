#include <QApplication>
#include <QJsonDocument>
#include <QDebug>
#include <QVariant>
#include <QSettings>


bool readJsonFile(QIODevice &device, QSettings::SettingsMap &map)
{
	bool ret = false;

	QJsonParseError error;
	map = QJsonDocument::fromJson(device.readAll() , &error).toVariant().toMap();

	if( error.error == QJsonParseError::NoError )
		ret = true;

	return ret;
}

bool writeJsonFile(QIODevice &device, const QSettings::SettingsMap &map)
{    
	bool ret = false;

	QJsonDocument jsonDocument = QJsonDocument::fromVariant(QVariant::fromValue(map));
	if ( device.write(jsonDocument.toJson()) != -1 )
		ret = true;

	return ret;
}


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	const QSettings::Format JsonFormat = QSettings::registerFormat("json", readJsonFile, writeJsonFile);
	QSettings settings(JsonFormat, QSettings::UserScope, "json","cazool");

	QMap<QString, QVariant> cazoolData;
	cazoolData.insert("Address","China");

	cazoolData.insert("age",18);

	cazoolData.insert("Tel","13888888888");
	settings.remove("Tsuibin");


	settings.setValue("Cazool", QVariant::fromValue(cazoolData));

	return a.exec();
}

