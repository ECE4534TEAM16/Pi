#include "celldialog.h"
#include <QWidget>


CellDialog::CellDialog(QWidget *parent) :
    QDialog(parent)
{
}

CellDialog::CellDialog(mazecell &link)
{
    cell = &link;

    label1 = new QLabel("Change Role");
    roleCombo = new QComboBox;
    if(cell->intersectionType == DEAD_END)
        roleCombo->addItem("START");
    roleCombo->addItem("END");
    QHBoxLayout *h1 = new QHBoxLayout;
    h1->addWidget(label1);
    h1->addWidget(roleCombo);
    okButton = new QPushButton("Ok");
    cancelButton = new QPushButton("Cancel");
    QHBoxLayout *h2 = new QHBoxLayout;
    h2->addWidget(okButton);
    h2->addWidget(cancelButton);
    QVBoxLayout *main = new QVBoxLayout;
    main->addLayout(h1);
    main->addLayout(h2);
    setLayout(main);

    //connection
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void CellDialog::okClicked()
{
    ROLE theRole;
    if(roleCombo->currentText() == "START")
        theRole = START;
    else if(roleCombo->currentText() == "END")
        theRole = END;
    if(theRole != cell->cellRole)
    {
        cell->setRole(theRole);
        if(theRole == START)
            emit cellStartChange();
        else if(theRole == END)
            emit cellEndChange();
    }
    this->close();
}
