#include <QDebug>
#include "bot.h"
#include "dot.h"



Bot::Bot(Field *m)
{
    field = m;
    m_n = field->is_m_n();
    m_mineNumber = field->is_m_mineNumber();
}

void Bot::Step()
{

    //qDebug() << "click but";

    if(field->m_isGameActive != true)           //Если игровое поле неактивно, то возврат
    {
        return;
    }


    auto Lambda_ValidCoord = [=](int i, int j) -> bool
    {
        return i >= 0 && j >= 0 && i < m_n && j < m_n;
    };


    //инфа сотка бомба
    for (int i = 0; i < m_n; ++i)
        for (int j = 0; j < m_n; ++j)
        {
            if(field->Dot_isOpen(i,j)  &&  field->Dot_isValue(i,j) != 0)
            {
                //подсчет флагов
                int tmpZnach = 0;
                auto LambdaF1 = [&](int i, int j)
                {
                    if(field->Dot_isFlag(i,j) == flagF)
                        tmpZnach++;

                };
                if (Lambda_ValidCoord(i - 1, j - 1))     LambdaF1(i - 1, j - 1);
                if (Lambda_ValidCoord(i - 1, j))         LambdaF1(i - 1, j);
                if (Lambda_ValidCoord(i - 1, j + 1))     LambdaF1(i - 1, j + 1);
                if (Lambda_ValidCoord(i, j - 1))         LambdaF1(i, j - 1);
                if (Lambda_ValidCoord(i, j + 1))         LambdaF1(i, j + 1);
                if (Lambda_ValidCoord(i + 1, j - 1))     LambdaF1(i + 1, j - 1);
                if (Lambda_ValidCoord(i + 1, j))         LambdaF1(i + 1, j);
                if (Lambda_ValidCoord(i + 1, j + 1))     LambdaF1(i + 1, j + 1);

                //подсчет закрытых клеток
                int i_c = 0, j_c = 0, c_c = 0;
                auto LambdaF2 = [&](int i, int j)
                {
                    if(!(field->Dot_isOpen(i,j)) && field->Dot_isFlag(i,j) == notF)
                    {
                        c_c++;
                        i_c = i;
                        j_c = j;
                    }

                };
                if (Lambda_ValidCoord(i - 1, j - 1))     LambdaF2(i - 1, j - 1);
                if (Lambda_ValidCoord(i - 1, j))         LambdaF2(i - 1, j);
                if (Lambda_ValidCoord(i - 1, j + 1))     LambdaF2(i - 1, j + 1);
                if (Lambda_ValidCoord(i, j - 1))         LambdaF2(i, j - 1);
                if (Lambda_ValidCoord(i, j + 1))         LambdaF2(i, j + 1);
                if (Lambda_ValidCoord(i + 1, j - 1))     LambdaF2(i + 1, j - 1);
                if (Lambda_ValidCoord(i + 1, j))         LambdaF2(i + 1, j);
                if (Lambda_ValidCoord(i + 1, j + 1))     LambdaF2(i + 1, j + 1);

                if(c_c >= 1 &&  ((field->Dot_isValue(i,j) - tmpZnach) == c_c))
                {
                    //инфа сотка бомба
                    qDebug() << "Flag:  " << i<< j;
                    field->Dot_VirtualEvent(i_c,j_c, rightV);
                    return;
                }
                else
                {
                    if(c_c >= 1 &&  field->Dot_isValue(i,j) == tmpZnach)
                    {
                        //инфа сотка пустая клетка
                        qDebug() << "Click: " << i<< j << " /top";
                        field->Dot_VirtualEvent(i_c,j_c, leftV);
                        return;
                    }
                }
                //qDebug() << "\n\r";
            }
        }
    qDebug() << "Click: ";
    {
        int j_t;
        int i_t;

        do
        {
            j_t = qrand() % m_n;
            i_t = qrand() % m_n;

        }
        while(field->Dot_isFlag(i_t,j_t) || field->Dot_isOpen(i_t,j_t));

        qDebug() << "Click: " << i_t << j_t << " /rand";
        field->Dot_VirtualEvent(i_t, j_t, leftV);
        return;
    }

    //отчет
    for (int i = 0; i < m_n; ++i)
    {
        QString a;
        for (int j = 0; j < m_n; ++j)
            a += ' ' + QString::number(verDot[i][j]);
        qDebug() << a;
    }
    qDebug() << "\n\r";
    qDebug() << "\n\r";
    return;
}
