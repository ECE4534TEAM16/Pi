/*
    Tyler Olson
    Virginia Tech ECE 4534 Embedded System Design
    celldialog.h & celldialog.cpp

    DESCRIPTION:
        These files are used to allow for cells to be clicked in the grid.  Allows
        for the roles of the cells to be changed.
*/

#ifndef CELLDIALOG_H
#define CELLDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include "mazecell.h"
#include <QHBoxLayout>

class CellDialog : public QDialog
{
    Q_OBJECT
public:
    CellDialog(QWidget *parent = 0);
    CellDialog(mazecell &link);

signals:
    void cellStartChange();
    void cellEndChange();

public slots:
    void okClicked();
private:
    mazecell *cell;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *label1;
    QComboBox *roleCombo;
};

#endif // CELLDIALOG_H
