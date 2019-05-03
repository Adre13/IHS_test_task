#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <QString>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QTextStream>
#include <QMessageBox>

class data_base
{
public:
    data_base();
    void read_folder(const QString& folder_path);
    QString get_data(QString request);
    bool save_to_file(const QString& file_name);
    bool load_from_file(const QString& file);


private:
    QString folder_path;
    QString file_data;
    QStringList t_sent_data, t_word_data;
    QMap<QString, QMap<QString, QStringList>> all_data;


    void add_data(const QString& file_name, const QStringList& data_list);
    QString str_to_save(const QString& word);
};

#endif // DATA_BASE_H
