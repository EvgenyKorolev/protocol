#ifndef EDITOR_TRANS_H
#define EDITOR_TRANS_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QDialog>
#include <QComboBox>
#include <QVariant>
#include <memory>
#include <iostream>
#include "transformator.h"
// Виджет - редактор трансформатора

class editor_trans : public QDialog
{
    Q_OBJECT
public:
    editor_trans(transformator *arg, QWidget *par = 0);
    transformator close_ret();
    ~editor_trans();
public slots:
    void tr_save();
private:
    transformator* _data;
    QLineEdit* _type;       // Тип трансфоматора
    QLineEdit* _mnom;       // Заводской №:
    QLineEdit* _cls;        // Класс точности
    QLineEdit* _nom_power;  // Номинальная полная мощность нагрузки Sн для указанного класса точности, ВА:
    QLineEdit* _obm;        // Схема соединения обмоток (усл. обозначение)
    QLineEdit* _nom_u_2;    // Номинальное напряжение основной вторичной обмотки U2 ном, В
    QLineEdit* _nom_u_1;    // Номинальное напряжение первичной обмотки U1 ном, кВ
    QComboBox* _f;        // Сколько фаз (1 или 3)
};

#endif // EDITOR_TRANS_H
