#include "celldialog.h"
#include <QtWidgets>

//CellDialog::CellDialog(QWidget *parent) :
//    QDialog(parent)
//{
//}

//CellDialog::CellDialog(MazeCell &link)
//{
//    cell = &link;

//    label1 = new QLabel("Change Role");
//    roleCombo = new QComboBox;
//    roleCombo->addItem("NORMAL");
//    roleCombo->addItem("START");
//    roleCombo->addItem("END");
//    QHBoxLayout *h1 = new QHBoxLayout;
//    h1->addWidget(label1);
//    h1->addWidget(roleCombo);
//    okButton = new QPushButton("Ok");
//    cancelButton = new QPushButton("Cancel");
//    QHBoxLayout *h2 = new QHBoxLayout;
//    h2->addWidget(okButton);
//    h2->addWidget(cancelButton);
//    QVBoxLayout *main = new QVBoxLayout;
//    main->addLayout(h1);
//    main->addLayout(h2);
//    setLayout(main);

//    //connection
//    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
//    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
//}

//void CellDialog::okClicked(){
//    ROLE theRole;
//    if(roleCombo->currentText() == "NORMAL")theRole = NORMAL;
//    else if(roleCombo->currentText() == "START")theRole = START;
//    else if(roleCombo->currentText() == "END")theRole = END;
//    cell->setRole(theRole);
//    this->close();
//}
