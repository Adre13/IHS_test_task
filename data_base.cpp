#include "data_base.h"

data_base::data_base()
{

}

void data_base::read_folder(const QString& folder_path)
{
    if(!all_data.isEmpty())
        all_data.clear();
    QStringList filters;
    int norm_files = 0, bad_files = 0;
    filters << "*.txt";
    QRegExp delim("(\\. |\\! |\\? \\; |\\\n)");
    QDirIterator itr(folder_path, filters , QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
    while(itr.hasNext())
    {
        QFile t_file(itr.next());
        if(!t_file.open(QFile::ReadOnly))
        {
            bad_files++;
        }else
        {
            file_data = t_file.readAll();
            t_sent_data = file_data.split(delim);
            add_data(itr.fileName(), t_sent_data);
            norm_files++;
        }
        t_file.close();
    }
    QString inf = QString::number(norm_files) + " files was loaded and " + QString::number(bad_files) + " was not.";
    QMessageBox::information(nullptr,"Information", inf);
}

QString data_base::get_data(QString request)
{
    QString answer = QString(request + ":");
    if(all_data.contains(request))
    {
        auto iter = all_data[request].begin();
        while(iter != all_data[request].end())
        {
            answer += "\n\tFile \"" + iter.key() + "\"";
            auto data_iter = iter.value().begin();
            while(data_iter != iter.value().end())
            {
                answer += "\n\t\t" + *data_iter;
                ++data_iter;
            }
            ++iter;
        }
        return answer;
    }
    return (answer += " is not found");
}

bool data_base::save_to_file(const QString& file_name)
{
    QFile file_to_save(file_name);
    if(!file_to_save.open(QFile::WriteOnly))
    {
        return false;
    }
    else
    {
        QTextStream out(&file_to_save);
        auto iter = all_data.begin();
        while(iter != all_data.end())
        {
            out << str_to_save(iter.key());
            ++iter;
        }

        file_to_save.close();
        return true;
    }

}

bool data_base::load_from_file(const QString& file)
{
    all_data.clear();
    QFile file_read(file);
    if(!file_read.open(QFile::ReadOnly))
    {
        return false;
    }
    else
    {
        QStringList temp_word_data, t_data, file_index;
        QString word, file_name;
        temp_word_data = QString(file_read.readAll()).split("\n");
        auto data_iterator = temp_word_data.begin();
        while(data_iterator != temp_word_data.end())
        {
            if(data_iterator->size() == 0)
            {
                ++data_iterator;
                continue;
            }
            else
            {
                t_data = data_iterator->split(" | ");
                auto t_file_iterator = t_data.begin();
                word = *t_file_iterator;
                ++t_file_iterator;
                while(t_file_iterator != t_data.end() -1)
                {
                    file_index = t_file_iterator->split("|");
                    file_name = file_index.at(0);
                    file_index.pop_front();
                    file_index.pop_back();
                    all_data[word].insert(file_name, file_index);
                    t_file_iterator++;
                }
            }
            ++data_iterator;
        }
        return true;
    }
}

void data_base::add_data(const QString &file_name, const QStringList &data_list)
{
    int sentence_count = 0;
    for(auto sentence : data_list)
    {
        QRegExp delim("(\\\"|\\,|\\-|\\!|\\.|\\?)");
        sentence.remove(delim);
        t_word_data = sentence.split(" ");
        int offset = 0;
        for(auto word : t_word_data)
        {
            if(word.size() == 0)
                continue;
            QString t_data = "Sent#";
            t_data += QString::number(sentence_count) + ", offset = " + QString::number(offset);
            if (all_data.contains(word))
            {
                if(all_data[word].contains(file_name))
                {
                    all_data[word][file_name] << t_data;
                }
                else
                {
                    QStringList temp;
                    temp.append(t_data);
                    all_data[word].insert(file_name, temp);
                }
            }
            else
            {
                QMap<QString, QStringList> temp_map;
                temp_map[file_name].append(t_data);
                all_data[word] = temp_map;
            }
            offset += word.size() + 1;
        }
        sentence_count++;
    }
}

QString data_base::str_to_save(const QString &word)
{
    QString result = QString(word + " | ");
    auto iter = all_data[word].begin();
    while(iter != all_data[word].end())
    {
        QString temp = QString(iter.key() + "|");
        for(auto item : iter.value())
        {
            temp.append(item);
            temp.append("|");
        }
        result += temp + " | ";
        ++iter;
    }
    result += "\n";
    return result;
}
