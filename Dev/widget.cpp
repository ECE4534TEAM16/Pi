#include "widget.h"
#include "ui_widget.h"



QTextStream erout(stderr);

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    userList_count = 0;
    scene = new QGraphicsScene(this);
    ui->mazeView->setScene(scene);
    mazeArray = new QList<QList<mazecell*> >;           //the first QList represents the columns, second represents the rows
    QList<mazecell*> temp1;
    mazeRow = 37;
    mazeCol = 37;
    currDir = UP;
    mapperMin = 0;
    mapperSec = 0;
    startCol = -1;
    startRow = -1;
    endCol = -1;
    endRow = -1;
    mapper_completed = false;
    end_exists = false;

    ports = new SerialPort();


/////////////////////////////////////////MAZE CREATION//////////////////////////////////////////////////////////
    //creates and instatiates the 76x76 array of custom graphics items used for the graphical maze
    for(int l = 0 ; l < GRID_SIZE; l++)
    {
        temp1.clear();
        for(int sahn = 0; sahn < GRID_SIZE; sahn++)
        {
            cell = new mazecell();          //use mazecell pointer to create new mazecell
            temp1.append(cell);             //pass that into the temp array
            connect(cell, SIGNAL(StartChange()), this, SLOT(on_RoleStartChange()));
            connect(cell, SIGNAL(EndChange()), this, SLOT(on_RoleEndChange()));
        }
        mazeArray->append(temp1);           //push the temp QList<*mazecell> into the master list (2d array)
    }

    for(int j = 0; j < GRID_SIZE; j++)
    {
        for(int i = 0; i < GRID_SIZE; i++)
        {
            int tempx = j*CELL_SIZE;
            int tempy = i*CELL_SIZE;
            if(i == mazeCol && j == mazeRow) //sets the default start node
            {
                mazeArray->at(i).at(j)->isMaze = true;
                mazeArray->at(i).at(j)->isNode = true;
                mazeArray->at(i).at(j)->setIntersection(INIT_START);        //the physical maze start will always be the middle of the graphical maze
                mazeArray->at(i).at(j)->setRole(START);                     //will be the default start for the maze
                mazeArray->at(i).at(j)->setpos(tempx,tempy,CELL_SIZE);      //set the position and size of each cell
                scene->addItem(mazeArray->at(i).at(j));                     //add that cell to the scene
                startCol = i;
                startRow = j;

            }
            else
            {
                mazeArray->at(i).at(j)->setpos(tempx,tempy,CELL_SIZE);          //set the position and size of each cell
                mazeArray->at(i).at(j)->setRole(NONMAZE);
                scene->addItem(mazeArray->at(i).at(j));                         //add that cell to the scene
            }
        }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


    connect(ports, SIGNAL(recieveMapperInstr()), this, SLOT(mapper_recieveData()));
    connect(ports, SIGNAL(user_error_recieved()), this, SLOT(user_ui_update()));
    mapperList_count = 0;


}





Widget::~Widget()
{
    qDebug () << "main destructor called";
    delete ports;
    delete ui;
}

//append data to stringlist so that commands can come in over time
QStringList Widget::parseM_dat(QStringList dat)
{
    QString temp;
    QString returnTemp;
    QString buildTemp;
    QStringList templist;

    for(int i = 0; i < dat.size(); i++)
    {
        temp = dat.at(i);
        if(temp.size() == 5)                            // this is an instruction for the maze
        {
            buildTemp.append(temp.at(0));
            buildTemp.append(",");
            buildTemp.append(temp.at(1));
            buildTemp.append(temp.at(2));
            buildTemp.append(temp.at(3));
            buildTemp.append(",");
            buildTemp.append(temp.at(4));
            buildList.append(buildTemp);
            buildTemp.clear();

            returnTemp.append("Dist: ");
            returnTemp.append(temp.at(0));              //should be a distance
            returnTemp.append(" | Intersection: ");
            returnTemp.append(temp.at(1));              //intersection type
            returnTemp.append(temp.at(2));
            returnTemp.append(temp.at(3));
            returnTemp.append(" | Dir: ");
            returnTemp.append(temp.at(4));              //direction taken
            templist.append(returnTemp);
            returnTemp.clear();
        }
        else //this is the end character or an error/warning
        {
            if(temp.size() == 1)
                templist.append("At end of maze");
            else
            {
                templist.append(temp);
                buildList.append("Warning/Error");
            }
        }

    }
    return templist;

}

void Widget::drawStandard()
{
    switch(currDir)
    {
    case UP:
        mazeCol--;
        checkBounds(mazeCol);
        checkBounds(mazeRow);
        mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
        mazeArray->at(mazeCol).at(mazeRow)->setIntersection(STANDARD);
        mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);
        break;
    case LEFT:
        mazeRow--;
        checkBounds(mazeCol);
        checkBounds(mazeRow);
        mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
        mazeArray->at(mazeCol).at(mazeRow)->setIntersection(STANDARD);
        mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);
        break;
    case RIGHT:
        mazeRow++;
        checkBounds(mazeCol);
        checkBounds(mazeRow);
        mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
        mazeArray->at(mazeCol).at(mazeRow)->setIntersection(STANDARD);
        mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);
        break;
    case DOWN:
        mazeCol++;
        checkBounds(mazeCol);
        checkBounds(mazeRow);
        mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
        mazeArray->at(mazeCol).at(mazeRow)->setIntersection(STANDARD);
        mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);
        break;
    default:
        erout << "DrawStandard case statement reached default state";
        exit(EXIT_FAILURE);
    }

}

void Widget::checkBounds(int pos)
{
    if(pos < 0 || pos > 75)
    {
        erout << "Rover has gone out of GUI Maze bounds.\n Check to make sure maze is within a 9x9 foot square from starting point";
        exit(EXIT_FAILURE);
    }
}

void Widget::updateDir(QString newDir)
{
    switch (currDir)
    {
    case UP:
        if(newDir == "l")
            currDir = LEFT;
        else if(newDir == "r")
            currDir = RIGHT;
        else if(newDir == "f")
            currDir = UP;
        else if(newDir == "b")
            currDir = DOWN;
        else
        {
            erout << "Improper character passed in as new direction in updateDir";
            exit(EXIT_FAILURE);
        }
        break;
    case LEFT:
        if(newDir == "l")
            currDir = DOWN;
        else if(newDir == "r")
            currDir = UP;
        else if(newDir == "f")
            currDir = LEFT;
        else if(newDir == "b")
            currDir = RIGHT;
        else
        {
            erout << "Improper character passed in as new direction in updateDir";
            exit(EXIT_FAILURE);
        }
        break;
    case RIGHT:
        if(newDir == "l")
            currDir = UP;
        else if(newDir == "r")
            currDir = DOWN;
        else if(newDir == "f")
            currDir = RIGHT;
        else if(newDir == "b")
            currDir = LEFT;
        else
        {
            erout << "Improper character passed in as new direction in updateDir";
            exit(EXIT_FAILURE);
        }
        break;
    case DOWN:
        if(newDir == "l")
            currDir = RIGHT;
        else if(newDir == "r")
            currDir = LEFT;
        else if(newDir == "f")
            currDir = DOWN;
        else if(newDir == "b")
            currDir = UP;
        else
        {
            erout << "Improper character passed in as new direction in updateDir";
            exit(EXIT_FAILURE);
        }
        break;
    default:
        erout << "updateDir switch reached default case";
        exit(EXIT_FAILURE);

        break;
    }

}

void Widget::drawIntersection(QString intersection)
{
    switch(currDir)
    {
    case UP:
        mazeCol--;
        checkBounds(mazeCol);
        checkBounds(mazeRow);
        break;
    case LEFT:
        mazeRow--;
        checkBounds(mazeCol);
        checkBounds(mazeRow);
        break;
    case RIGHT:
        mazeRow++;
        checkBounds(mazeCol);
        checkBounds(mazeRow);
        break;
    case DOWN:
        mazeCol++;
        checkBounds(mazeCol);
        checkBounds(mazeRow);
        break;
    default:
        erout << "DrawIntersection case statement reached default state";
        exit(EXIT_FAILURE);
    }
    if(!mazeArray->at(mazeCol).at(mazeRow)->isNode)//this intersection has not been visited yet
    {
        if(intersection == "100")//left
        {
            mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
            mazeArray->at(mazeCol).at(mazeRow)->isNode = true;
            mazeArray->at(mazeCol).at(mazeRow)->setIntersection(LEFT_ONLY);
            mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);

        }
        else if(intersection == "001")//right
        {
            mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
            mazeArray->at(mazeCol).at(mazeRow)->isNode = true;
            mazeArray->at(mazeCol).at(mazeRow)->setIntersection(RIGHT_ONLY);
            mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);

        }
        else if(intersection == "110")//left and straight
        {
            mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
            mazeArray->at(mazeCol).at(mazeRow)->isNode = true;
            mazeArray->at(mazeCol).at(mazeRow)->setIntersection(LEFT_FORWARD);
            mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);

        }
        else if(intersection == "101")//left and right
        {
            mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
            mazeArray->at(mazeCol).at(mazeRow)->isNode = true;
            mazeArray->at(mazeCol).at(mazeRow)->setIntersection(LEFT_RIGHT);
            mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);

        }
        else if(intersection == "011")//straight and right
        {
            mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
            mazeArray->at(mazeCol).at(mazeRow)->isNode = true;
            mazeArray->at(mazeCol).at(mazeRow)->setIntersection(RIGHT_FORWARD);
            mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);

        }
        else if(intersection == "111")//left,straigh, and right
        {
            mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
            mazeArray->at(mazeCol).at(mazeRow)->isNode = true;
            mazeArray->at(mazeCol).at(mazeRow)->setIntersection(ALL_THREE);
            mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);

        }
        else if(intersection == "000")//dead end
        {
            mazeArray->at(mazeCol).at(mazeRow)->isMaze = true;
            mazeArray->at(mazeCol).at(mazeRow)->isNode = true;
            mazeArray->at(mazeCol).at(mazeRow)->setIntersection(DEAD_END);
            mazeArray->at(mazeCol).at(mazeRow)->setRole(NORMAL);

        }
        else
        {
            std::string str = intersection.toStdString();
            fprintf(stderr, "Undefined intersection (%s) passed into drawIntersection\n", str.c_str());
            exit(EXIT_FAILURE);
        }
    }

}


//builds the maze as instructions are sent from mapper rover
void Widget::mazeBuild()
{
    QStringList instruction;
    int dist;
    QString intersection;
    QString newDir;
    mapperQueue.enqueue(buildList.at(mapperList_count));
    while(!mapperQueue.isEmpty())
    {
        QString temp = mapperQueue.dequeue();
        instruction = temp.split(",");          //[0] = distance [1] = intersection type [2] = new direction
        if(instruction.size() > 3)
        {
            std::string str = QString(instruction.join(",")).toStdString();
            fprintf(stderr, "Instruction (%s) parsed incorrectly at mazeBuild function\n", str.c_str());
            exit(EXIT_FAILURE);
        }
        else
        {
            bool ok;
            dist = QString(instruction.at(0)).toInt(&ok, 10);
            intersection = instruction.at(1);
            newDir = instruction.at(2);
            if(!ok)
            {
                erout << "mazeBuild distance int conversion error\n";
                exit(EXIT_FAILURE);
            }
            if(dist < 2)
            {
                erout << "mazeBuild distance to short.  Ensure that mapper rover is sending distances correctly\n";
                exit(EXIT_FAILURE);

            }
            while(dist != 1)  //ALL cells in while loop will be standard cells
            {
                drawStandard();
                dist--;
            }
            drawIntersection(intersection);
            updateDir(newDir);

        }
    }

}

void Widget::setDists(int col, int row) //set A* distances for all maze cells
{
    if(mazeArray->at(col).at(row)->isMaze)
    {
        int currCell_x, currCell_y, start_y, start_x, end_x, end_y;
        double toEnd, toStart, x_diff, y_diff;
        currCell_x = mazeArray->at(col).at(row)->x_pos;
        currCell_y = mazeArray->at(col).at(row)->y_pos;
        start_x = mazeArray->at(startCol).at(startRow)->x_pos;
        start_y = mazeArray->at(startCol).at(startRow)->y_pos;
        end_x = mazeArray->at(endCol).at(endRow)->x_pos;
        end_y = mazeArray->at(endCol).at(endRow)->y_pos;

        //to the end
        x_diff = currCell_x - end_x; //(x2-x1)
        x_diff = x_diff*x_diff; //squared
        y_diff = currCell_y - end_y; // (y2-y1)
        y_diff = y_diff*y_diff; //squared

        toEnd = sqrt(x_diff+y_diff);

        mazeArray->at(col).at(row)->distToEnd = toEnd;
        //

        //to the start
        x_diff = currCell_x - start_x; //(x2-x1)
        x_diff = x_diff*x_diff; //squared
        y_diff = currCell_y - start_y; // (y2-y1)
        y_diff = y_diff*y_diff; //squared

        toStart = sqrt(x_diff+y_diff);

        mazeArray->at(col).at(row)->distToStart = toStart;
        mazeArray->at(col).at(row)->F = toStart+toEnd;
        //
        qDebug() << row << "," << col <<  " : " <<  toStart+toEnd;
    }


}

void Widget::A_star(int col, int row) //holycrap this is so much easier implementing here than in javascript
{
    qDebug() << col << "," << row;
    qDebug() << "begin A*" << mazeArray->at(col).at(row)->cellRole << "|" <<mazeArray->at(col).at(row)->F;
    int newcol;
    int newrow;
    mazeArray->at(col).at(row)->visited = true;
    if(mazeArray->at(col).at(row)->cellRole == END) //found the end
    {
        QPair<int,int> instruction;
        int tempcol = col;
        int temprow = row;
        qDebug() << "we found a solution!";
        while(mazeArray->at(tempcol).at(temprow)->cellRole != START)
        {
            int temp;
            instruction.first = tempcol;
            instruction.second = temprow;
            temp = mazeArray->at(tempcol).at(temprow)->parent_col;
            temprow = mazeArray->at(tempcol).at(temprow)->parent_row;
            tempcol = temp;
            closedList.append(instruction);
        }
        openList.clear();
        for(int k = 0; k < (closedList.size()/2); k++) closedList.swap(k,closedList.size()-(1+k)); //reverses the list
        return;

    }
    findAdjacent(col, row);
    newcol = openList.at(0).col;
    newrow = openList.at(0).row;
    openList.removeFirst();
    count ++;
//    if(count < 100)
    A_star(newcol, newrow); //recursion baby!
    qDebug() << "end A*";
}

void Widget::findAdjacent(int col, int row) //find and adds adjecent to openlist, if cell has been visited it is not added, sorts openlist
{
    qDebug() << "in findAdjacent";
    listDat temp;
    if(mazeArray->at(col-1).at(row)->isMaze && !mazeArray->at(col-1).at(row)->visited) //to the left
    {
        temp.row = row;
        temp.col = col-1;
        temp.cost = mazeArray->at(col-1).at(row)->F;
        openList.append(temp);
        mazeArray->at(col-1).at(row)->parent_col = col;
        mazeArray->at(col-1).at(row)->parent_row = row;
    }
    if(mazeArray->at(col+1).at(row)->isMaze && !mazeArray->at(col+1).at(row)->visited) //to the right
    {
        temp.row = row;
        temp.col = col+1;
        temp.cost = mazeArray->at(col+1).at(row)->F;
        openList.append(temp);
        mazeArray->at(col+1).at(row)->parent_col = col;
        mazeArray->at(col+1).at(row)->parent_row = row;
    }
    if(mazeArray->at(col).at(row-1)->isMaze && !mazeArray->at(col).at(row-1)->visited) //above
    {
        temp.row = row-1;
        temp.col = col;
        temp.cost = mazeArray->at(col).at(row-1)->F;
        openList.append(temp);
        mazeArray->at(col).at(row-1)->parent_col = col;
        mazeArray->at(col).at(row-1)->parent_row = row;
    }
    if(mazeArray->at(col).at(row+1)->isMaze && !mazeArray->at(col).at(row+1)->visited) //below
    {
        temp.row = row+1;
        temp.col = col;
        temp.cost = mazeArray->at(col).at(row+1)->F;
        openList.append(temp);
        mazeArray->at(col).at(row+1)->parent_col = col;
        mazeArray->at(col).at(row+1)->parent_row = row;
    }

    qSort(openList.begin(), openList.end());
}

void Widget::parsePath(int pos)
{
    if(startCol > closedList.at(pos).first) //rover facing up, forward becomes up
    {
        UserDir = UP;
    }
    else if(startCol < closedList.at(pos).first) //rover is facing down, forward becomes down
    {
        UserDir = DOWN;
    }
    if(startRow > closedList.at(pos).second) //rover is facing left, forward becomes left
    {
        UserDir = LEFT;
    }
    else if(startRow < closedList.at(pos).second) //rover is facing right, forward becomes right
    {
        UserDir = RIGHT;
    }

}

QString Widget::IntersectionInstr(int col, int row, int futureCol, int futureRow)
{
    switch (UserDir)
    {
    case UP:
        if(futureCol > col) //this should not happen
        {
            UserDir = DOWN;
            return "b";

        }
        else if(futureCol < col)
        {
            UserDir = UP;
            return "f";
        }
        else if(futureRow > row)
        {
            UserDir = RIGHT;
            return "r";
        }
        else if(futureRow < row)
        {
            UserDir = LEFT;
            return "l";
        }
        else
        {
            erout << "Could not calculate instruction at intersection";
            exit(EXIT_FAILURE);
        }
        break;
    case LEFT:
        if(futureCol > col) //this should not happen
        {
            UserDir = DOWN;
            return "l";

        }
        else if(futureCol < col)
        {
            UserDir = UP;
            return "r";
        }
        else if(futureRow > row)
        {
            UserDir = RIGHT;
            return "b";
        }
        else if(futureRow < row)
        {
            UserDir = LEFT;
            return "f";
        }
        else
        {
            erout << "Could not calculate instruction at intersection";
            exit(EXIT_FAILURE);
        }
        break;
    case RIGHT:
        if(futureCol > col) //this should not happen
        {
            UserDir = DOWN;
            return "r";

        }
        else if(futureCol < col)
        {
            UserDir = UP;
            return "l";
        }
        else if(futureRow > row)
        {
            UserDir = RIGHT;
            return "f";
        }
        else if(futureRow < row)
        {
            UserDir = LEFT;
            return "b";
        }
        else
        {
            erout << "Could not calculate instruction at intersection";
            exit(EXIT_FAILURE);
        }
        break;
    case DOWN:
        if(futureCol > col)
        {
            UserDir = DOWN;
            return "f";

        }
        else if(futureCol < col)
        {
            UserDir = UP;
            return "b";
        }
        else if(futureRow > row)
        {
            UserDir = RIGHT;
            return "l";
        }
        else if(futureRow < row)
        {
            UserDir = LEFT;
            return "r";
        }
        else
        {
            erout << "Could not calculate instruction at intersection";
            exit(EXIT_FAILURE);
        }
        break;
    default:
        erout << "IntersectionInstr switch reached default case";
        exit(EXIT_FAILURE);

        break;
    }
}

void Widget::createPathList()
{
    int tempcol = closedList.at(1).first;
    int temprow = closedList.at(1).second;
    int count = 1;
    QString instr;
    //calulate begging direction
    parsePath(0);
    while(mazeArray->at(tempcol).at(temprow)->cellRole != END && count < closedList.length()-1)
    {
        int tempcol = closedList.at(count).first;
        int temprow = closedList.at(count).second;
        if(mazeArray->at(tempcol).at(temprow)->isNode) //this is an intersection, have to add instruction here
        {
            instr = IntersectionInstr(tempcol, temprow, closedList.at(count+1).first, closedList.at(count+1).second);
            userInstr.append(instr);
        }
        count++;
    }

    qDebug() << userInstr;
}



//
void Widget::on_RoleStartChange()
{
    mazeArray->at(startCol).at(startRow)->cellRole = NORMAL;
    //go through array to find curre
    for(int i = 0; i < GRID_SIZE; i++)
    {
        for(int j = 0; j < GRID_SIZE; j++)
        {
            if(mazeArray->at(i).at(j)->cellRole == START && mazeArray->at(i).at(j)->isMaze)
            {
                startCol = i;
                startRow = j;
            }
        }
    }
    qDebug() << "Start signal recieved at main";
}

void Widget::on_RoleEndChange()
{
    if(endCol == -1 && endRow == -1) //setting the initial end point
    {
        //go through array to find current end node
        //set endcol and endrow to those values
        for(int i = 0; i < GRID_SIZE; i++)
        {
            for(int j = 0; j < GRID_SIZE; j++)
            {
                if(mazeArray->at(i).at(j)->cellRole == END)
                {
                    endCol = i;
                    endRow = j;
                    end_exists = true;
                }
            }
        }
    }
    else
    {
        mazeArray->at(endCol).at(endRow)->setRole(NORMAL);
        //go through array to find curre
        for(int i = 0; i < GRID_SIZE; i++)
        {
            for(int j = 0; j < GRID_SIZE; j++)
            {
                if(mazeArray->at(i).at(j)->cellRole == END)
                {
                    endCol = i;
                    endRow = j;
                    end_exists = true;
                }
            }
        }

    }
    qDebug() << "End signal recieved at main";
}

void Widget::mapper_recieveData() //a full instruction or error has been recieved and signal sent from serialport.cpp
{
    QString temp;
    if(!TEST)
        mapperDat.append(ports->list); //will copy what is in the instruction buffer
    ports->list.clear(); //clears list instruction buffer
    //update ui with current instruction
    mapperDat = parseM_dat(mapperDat);              //mapperDat will contain set of instructions, use these processed instructions to update ui
    for(int i = 0; i < mapperDat.size(); i++)
    {
        temp = mapperDat.at(i);
        if(temp.at(0) == 'W')//warning
        {

            ui->mapperList->addItem(temp);
            ui->mapperList->item(mapperList_count)->setTextColor(QColor(255,165,0));
            mapperList_count++;
        }
        else if(temp.at(0) == 'E')//Error
        {
            ui->mapperList->addItem(mapperDat.at(i));
            ui->mapperList->item(mapperList_count)->setTextColor(Qt::darkRed);
            mapperList_count++;
        }
        else if(temp == "At end of maze")//end of instructions
        {
            //set some kind of flag indicating that the end of the maze has been reached
            //should no longer recieve data from mapper rover
            mapper_completed = true;
        }
        else//instruction
        {
            ui->mapperList->addItem(temp);
            mazeBuild();
            mapperList_count++;
        }
    }
    mapperDat.clear();


}

void Widget::user_ui_update()
{
    ui->userList->addItem(ports->user_error);
    if(ports->user_error.at(0) == 'E')
        ui->userList->item(userList_count)->setTextColor(Qt::darkRed);
    else if(ports->user_error.at(0) == 'W')
        ui->userList->item(userList_count)->setTextColor(QColor(255,165,0));
    else{}
    userList_count++;
    ports->user_error.clear();

}


//need to send start signal first, then wait for signal from serial port to recieve data as it comes in
void Widget::on_mapperStart_button_clicked()
{
    if(TEST)
    {
        mapperDat = ports->readline("test1.dat");
        Widget::mapper_recieveData();
        mapper_completed = true;
    }
    else
    {
        ports->sendMapperStartSignal(); //send the signal to start the mapper rover
    }
}

void Widget::on_userStart_button_clicked()
{
    QString end_sig = "E";
    ports->sendUserStartSignal();
    userInstr.append(end_sig);
    ports->sendPath(userInstr);
}

void Widget::on_mazeSolve_button_clicked()
{
    count = 0;
    if(!mapper_completed || !end_exists)
    {
        QMessageBox mazeSolve(this);
        if(!mapper_completed)
            mazeSolve.setText("The mapper rover must be run before the maze is solved.");
        else
            mazeSolve.setText("No end point has been selected yet.");
        mazeSolve.setIcon(QMessageBox::Information);
        mazeSolve.setStandardButtons(QMessageBox::Ok);
        mazeSolve.setDefaultButton(QMessageBox::Ok);
        mazeSolve.setWindowTitle("Unable to Solve");
        int ret = mazeSolve.exec();
        switch(ret)
        {
        case QMessageBox::Ok:
            break;
        default:
            erout << "Error, Reached default case in Widget::on_mazeSolve_button_clicked";
            exit(EXIT_FAILURE);
        }
    }
    else //solve the maze
    {
        for(int i = 0; i < GRID_SIZE ; i++)
        {
            for(int j = 0; j < GRID_SIZE ; j++)
            {
                setDists(i,j);
            }
        }
        A_star(startCol, startRow);
        createPathList();
    }

}




//following buttons do not need signals
//they simply output text in the from of QMessageBox
void Widget::on_constraints_button_clicked()
{
    QMessageBox constraints(this);
    constraints.setText(" - The maze must be confined to a 9x9 foot box\n - The mapper rover must be run before the user rover");
    constraints.setIcon(QMessageBox::Information);
    constraints.setStandardButtons(QMessageBox::Ok);
    constraints.setDefaultButton(QMessageBox::Ok);
    constraints.setWindowTitle("Application Constraints");
    int ret = constraints.exec();
    switch(ret)
    {
    case QMessageBox::Ok:
        break;
    default:
        erout << "Error, Reached default case in Widget::on_constraints_button_clicked";
        exit(EXIT_FAILURE);
    }

}

void Widget::on_exit_button_clicked()
{
    QMessageBox quits(this);
    quits.setText("Are you sure you want to exit the program?");
    quits.setIcon(QMessageBox::Question);
    quits.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    quits.setDefaultButton(QMessageBox::No);
    quits.setWindowTitle("Quit?");
    int ret = quits.exec();
    switch (ret)
    {
    case QMessageBox::No:
          // dont quit program
        break;
    case QMessageBox::Yes:
          // Quit the program

        QApplication::quit();
        break;
    default:
          // should never be reached
        erout << "Error, Reached default case in Widget::on_exit_button_clicked";
        exit(EXIT_FAILURE);
    }
}



