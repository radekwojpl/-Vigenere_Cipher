#include "codevigenera.h"

CodeVigenera::CodeVigenera()
{

}

QString CodeVigenera::getPhrase() const
{
    return phrase;
}

void CodeVigenera::setPhrase(const QString &value)
{
    phrase = value;
}

QString CodeVigenera::getKeyWord() const
{
    return keyWord;
}

void CodeVigenera::setKeyWord(const QString &value)
{
    keyWord = value;
}

QString CodeVigenera::generateMultipleKeyWord(QString phrase, QString key)
{

    QString::iterator keyIterator = key.begin();
    multipleKeyWord.clear();
    for(QString::iterator it = phrase.begin();it != phrase.end(); it++)
    {
        if(*it >= "a" && *it<= "z" || *it >= "A" && *it<= "Z"  )
        {
            if(keyIterator == key.end()) keyIterator = key.begin();
            multipleKeyWord += *keyIterator;
            keyIterator++;
        }
        if(*it == " ")
        {
            multipleKeyWord +=" ";
        }
    }
    return multipleKeyWord;
}

QString CodeVigenera::generateReverseKeyWord(QString keyWord)
{
   QString cos = "";
    for(QString::iterator keyWord_it = keyWord.begin();keyWord_it != keyWord.end(); keyWord_it++)
    {
        int z = (26-findLetterPosition(*keyWord_it))%26;
        cos += encryptionArray[z][0];
   }
    return cos;
}

void CodeVigenera::encrypt()
{
    encryptedWord.clear();
    for(QString::iterator phrase_it = phrase.begin(), key_it=multipleKeyWord.begin();
        phrase_it != phrase.end(), key_it != multipleKeyWord.end();
        phrase_it++, key_it++)
    {
        if(*phrase_it >= "a" && *phrase_it<= "z" || *phrase_it >= "A" && *phrase_it<= "Z" )
        {
            auto positions = getXandYPosition(phrase_it, key_it);
            encryptedWord +=encryptionArray[std::get<0>(positions)][std::get<1>(positions)];
        }
        else if (*phrase_it == " ")
        {
            encryptedWord +=" ";
        }
    }
    qDebug()<<encryptedWord;
}


void CodeVigenera::findXposition(QChar x,std::promise<qint32> && prms)
{
    int i = 0;
    while(encryptionArray[i][0] != x.toUpper())
    {
        i++;
    }
    prms.set_value(i);
}


void CodeVigenera::findYposition(QChar y, std::promise<qint32> && prms)
{
    int i = 0;
    while(encryptionArray[0][i] != y.toUpper())
    {
        i++;
    }
    prms.set_value(i);

}

std::tuple<qint32, qint32> CodeVigenera::getXandYPosition(QString::iterator phrase_it, QString::iterator key_it)
{
    std::promise<qint32> prms1;
    std::future<qint32> ftr1 = prms1.get_future();
    std::promise<qint32> prms2;
    std::future<qint32> ftr2 = prms2.get_future();
    std::thread thr1(&CodeVigenera::findXposition,this,*phrase_it, std::move(prms1));
    std::thread thr2(&CodeVigenera::findYposition,this,*key_it, std::move(prms2));
    thr1.join();
    thr2.join();
    qint32 x = ftr1.get();
    qint32 y = ftr2.get();
    return std::make_tuple(x, y);
}

QString CodeVigenera::getEncryptedWord() const
{
    return encryptedWord;
}

void CodeVigenera::setEncryptedWord(const QString &value)
{
    encryptedWord = value;
}

qint32 CodeVigenera::findLetterPosition(QChar x)
{
    int i = 0;
    while(encryptionArray[i][0] != x.toUpper())
    {
        i++;
    }
    return i;
}

QString CodeVigenera::getMultipleKeyWord() const
{
    return multipleKeyWord;
}

void CodeVigenera::setMultipleKeyWord(const QString &value)
{
    multipleKeyWord = value;
}
