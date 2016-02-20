#ifndef DBSETTINGS_H
#define DBSETTINGS_H

#include <QtWidgets>

class DBSettings
{
public:
    DBSettings();
    ~DBSettings();

    bool readSettings();

    QString getDatabaseName() const;
    void setDatabaseName(const QString &value);

    QString getUserName() const;
    void setUserName(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getHostName() const;
    void setHostName(const QString &value);

signals:

public slots:
    void writeSettings(QString databaseName,
                       QString userName,
                       QString password,
                       QString hostName);

private:
    QFile *m_pSettingsFile;
    QString m_databaseName;
    QString m_userName;
    QString m_password;
    QString m_hostName;

    static const int NUM_SETTINGS = 4;
    QString *settings[DBSettings::NUM_SETTINGS];

    void createMassivePointersToSettings();
    void errorOpenMessage(QString action);
};

#endif // DBSETTINGS_H
