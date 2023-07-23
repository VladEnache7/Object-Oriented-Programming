//
// Created by Admin on 13-May-23.
//

#include <QDesktopServices>
#include "GUI.h"

#include <iostream>
using namespace std;

GUI::GUI(ServiceAdmin &serviceAdminToBeSet, ServiceUser &serviceUserToBeSet, QWidget *parent) : QWidget(parent),
                                                                                               serviceAdmin(serviceAdminToBeSet),
                                                                                               serviceUser(serviceUserToBeSet)
{
    auto* firstPageLayout = new QVBoxLayout{this};

    this->setWindowTitle("Keep Calm and Adopt a Dog Shelter");
    this->setWindowIcon(QIcon(R"(C:\Users\Admin\Documents\GitHub\a89-912-enache-vlad\animal-shelter.png)"));
    this->setMinimumSize(850, 200);

    /// welcome label
    QFont font("Verdana", 20, QFont::Bold);
    auto* welcomeLabel = new QLabel("Welcome to the Keep Calm and Adopt a Dog Shelter!", this);
    welcomeLabel->setFont(font);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    firstPageLayout->addWidget(welcomeLabel);



    // buttons
    auto* buttonsLayout = new QHBoxLayout{};

    QFont fontModes("Arial", 15, QFont::Bold);

    this->adminModeButton = new QPushButton("Admin mode");
    this->adminModeButton->setFont(fontModes);

    this->userModeButton = new QPushButton("User mode");
    this->userModeButton->setFont(fontModes);

    buttonsLayout->addWidget(this->adminModeButton);
    buttonsLayout->addWidget(this->userModeButton);

    // add the buttons layout to the main layout
    firstPageLayout->addLayout(buttonsLayout);

    // connect the signals and slots
    QObject::connect(this->adminModeButton, &QPushButton::clicked, this, &GUI::AdminModeGUI);
    QObject::connect(this->userModeButton, &QPushButton::clicked, this, &GUI::chooseFileType);
}

GUI::~GUI() = default;

void GUI::AdminModeGUI() {
    // read only if is empty
    if(this->serviceAdmin.getDogs().empty())
        this->serviceAdmin.readShelterDogFromFile();

    this->adminWidget = new QWidget{};

    this->adminWidget->setWindowTitle("Keep Calm and Adopt a Dog Shelter");
    this->adminWidget->setWindowIcon(QIcon(R"(C:\Users\Admin\Documents\GitHub\a89-912-enache-vlad\animal-shelter.png)"));

    this->adminWidget->show(); // show the admin window
    this->hide(); // hide the first page window

    // setting the size for the admin window
    this->adminWidget->setMinimumSize(600, 400);

    // the big layout for the admin window
    auto *bigLayout = new QVBoxLayout{this->adminWidget};

    /// --- title --- ///
    auto *adminLabel = new QLabel{"~ Admin mode ~"};
    QFont font("Arial", 20, QFont::Bold);
    adminLabel->setFont(font);
    adminLabel->setAlignment(Qt::AlignCenter);
    adminLabel->setMinimumHeight(50);

    // layout for the admin page
    auto *adminLayout = new QHBoxLayout{this->adminWidget};

    // adding the title and the layout to the big layout
    bigLayout->addWidget(adminLabel);
    bigLayout->addLayout(adminLayout);

    /// --- left layout --- ///
    auto *leftLayout = new QVBoxLayout{};
    adminLayout->addLayout(leftLayout);

    /// --- title of list --- ///
    auto *dogsLabel = new QLabel{"Sheltered Dogs"};
    QFont font2("Arial", 15, QFont::Bold);
    dogsLabel->setFont(font2);
    dogsLabel->setAlignment(Qt::AlignCenter);
    dogsLabel->setMinimumHeight(20);
    leftLayout->addWidget(dogsLabel);


    /// --- list dogs widget --- ///
    this->dogsListWidget = new QListWidget{};
    leftLayout->addWidget(this->dogsListWidget);

    QFont listFont("Arial", 12);
    this->dogsListWidget->setFont(listFont);

    this->dogsListWidget->setMinimumSize(200, 600);
    this->dogsListWidget->setSelectionMode(QAbstractItemView::SingleSelection); // select just one dog at a time
    this->populateListAdminMode();

//    this->dogsListWidget->setCurrentRow(0); // select the first dog by default

    // TODO: here may be the bug for the admin mode
    // connect the list widget to the function that shows the dog's data
    QObject::connect(this->dogsListWidget, &QListWidget::itemSelectionChanged, this, &GUI::showDogDataAdmin);

    /// --- right layout --- ///
    auto *rightLayout = new QVBoxLayout{};
    adminLayout->addLayout(rightLayout);


    /// --- form layout --- ///
    auto *formLayout = new QFormLayout{};
    rightLayout->addLayout(formLayout);

    QFont formFont("Arial", 15, QFont::Bold);

    /// form labels
    auto *nameLabel = new QLabel{"Name:"};
    nameLabel->setFont(formFont);
    nameLabel->setMinimumWidth(100);
    nameLabel->setAlignment(Qt::AlignCenter);

    auto *breedLabel = new QLabel{"Breed:"};
    breedLabel->setFont(formFont);
    breedLabel->setMinimumWidth(100);
    breedLabel->setAlignment(Qt::AlignCenter);

    auto *ageLabel = new QLabel{"Age:"};
    ageLabel->setFont(formFont);
    ageLabel->setMinimumWidth(100);
    ageLabel->setAlignment(Qt::AlignCenter);

    auto *photoLabel = new QLabel{"Photo:"};
    photoLabel->setFont(formFont);
    photoLabel->setMinimumWidth(100);
    photoLabel->setAlignment(Qt::AlignCenter);

    /// form line edits
    this->nameLineEdit = new QLineEdit{};
    this->breedLineEdit = new QLineEdit{};
    this->ageLineEdit = new QLineEdit{};
    this->photoLineEdit = new QLineEdit{};
    this->photoLineEdit->setMinimumWidth(300);

    formLayout->addRow(nameLabel, this->nameLineEdit);
    formLayout->addRow(breedLabel, this->breedLineEdit);
    formLayout->addRow(ageLabel, this->ageLineEdit);
    formLayout->addRow(photoLabel, this->photoLineEdit);


    /// --- buttons layout --- ///
    {
        auto *buttonsLayout = new QVBoxLayout{};
        rightLayout->addLayout(buttonsLayout);

        QFont buttonsFont("Arial", 15, QFont::Bold);

        this->addDogButton = new QPushButton{"Add Dog"};
        this->addDogButton->setFont(buttonsFont);

        this->deleteDogButton = new QPushButton{"Delete Dog"};
        this->deleteDogButton->setFont(buttonsFont);

        this->updateDogButton = new QPushButton{"Update Dog"};
        this->updateDogButton->setFont(buttonsFont);

        this->saveAndExitButton = new QPushButton{"Save and Exit"};
        this->saveAndExitButton->setFont(buttonsFont);

        buttonsLayout->addWidget(this->addDogButton);
        buttonsLayout->addWidget(this->deleteDogButton);
        buttonsLayout->addWidget(this->updateDogButton);
        buttonsLayout->addWidget(this->saveAndExitButton);
    }

    // connect the signals and slots
    QObject::connect(this->addDogButton, &QPushButton::clicked, this, &GUI::addDogGUI);
    QObject::connect(this->deleteDogButton, &QPushButton::clicked, this, &GUI::deleteDogGUI);
    QObject::connect(this->updateDogButton, &QPushButton::clicked, this, &GUI::updateDogGUI);
    QObject::connect(this->saveAndExitButton, &QPushButton::clicked, this, &GUI::saveAndExitAdminGUI);



}

void GUI::addDogGUI() {
    // take the data from the line edits and add the dog to the list
    std::string newName = this->nameLineEdit->text().toStdString();
    std::string newBreed = this->breedLineEdit->text().toStdString();
    int newAge = this->ageLineEdit->text().toInt();
    std::string newPhoto = this->photoLineEdit->text().toStdString();

    try {
        this->serviceAdmin.addDog(newName, newBreed, newAge, newPhoto);
    } catch (const std::exception& exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->populateListAdminMode();
}

void GUI::deleteDogGUI() {
    // take the nameDogToBeDeleted of the selected dog and delete it from the list
    std::string nameDogToBeDeleted = this->nameLineEdit->text().toStdString();

    try {
        this->serviceAdmin.deleteDog(nameDogToBeDeleted);
    } catch (const std::exception& exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->populateListAdminMode();
}

void GUI::updateDogGUI() {
    // take the data from the line edits and update the dog from the list
    std::string nameDogToBeUpdated = this->nameLineEdit->text().toStdString();
    std::string newBreed = this->breedLineEdit->text().toStdString();
    int newAge = this->ageLineEdit->text().toInt();
    std::string newPhoto = this->photoLineEdit->text().toStdString();

    try {
        this->serviceAdmin.updateDog(nameDogToBeUpdated, newBreed, newAge, newPhoto);
    } catch (const std::exception& exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->populateListAdminMode();
}

void GUI::saveAndExitAdminGUI() {
    // save the dogs to the file and exit the admin mode
    this->serviceAdmin.saveShelterDogToFile();
    this->adminWidget->close();
    this->show();
}

void GUI::populateListAdminMode() {
    // clear the list
    this->dogsListWidget->clear();

    // populate the list with the dogs from the repository
    for (const auto& dog : this->serviceAdmin.getDogs()) {
        this->dogsListWidget->addItem(QString::fromStdString(dog.getName() + " - " + dog.getBreed()));
    }
}

void GUI::showDogDataAdmin() {
    // take the selected dog and show its data in the line edits
    int selectedIndex = this->dogsListWidget->currentIndex().row();
    if (selectedIndex < 0) {
        return;
    }

    const auto& dog = this->serviceAdmin.getDogs()[selectedIndex];

    this->nameLineEdit->setText(QString::fromStdString(dog.getName()));
    this->breedLineEdit->setText(QString::fromStdString(dog.getBreed()));
    this->ageLineEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
    this->photoLineEdit->setText(QString::fromStdString(dog.getPhotograph()));
}

void GUI::chooseFileType() {
    this->hide();

    // choose the file type
    fileTypeWidget = new QWidget{};
    fileTypeWidget->setMinimumSize(300, 100);
    auto *fileTypeLayout = new QVBoxLayout{fileTypeWidget};
    fileTypeWidget->setLayout(fileTypeLayout);

    QFont fileTypeFont("Arial", 15, QFont::Bold);

    /// --- file type label --- ///
    auto *fileTypeLabel = new QLabel{"Choose the file type:"};
    fileTypeLayout->addWidget(fileTypeLabel);

    fileTypeLabel->setFont(fileTypeFont);
    fileTypeLabel->setAlignment(Qt::AlignCenter);

    /// --- file type buttons --- ///
    auto *fileTypeButtonsLayout = new QHBoxLayout{};
    fileTypeLayout->addLayout(fileTypeButtonsLayout);

    auto *csvButton = new QPushButton{"CSV"};
    csvButton->setFont(fileTypeFont);

    auto *htmlButton = new QPushButton{"HTML"};
    htmlButton->setFont(fileTypeFont);

    fileTypeButtonsLayout->addWidget(csvButton);
    fileTypeButtonsLayout->addWidget(htmlButton);

    QObject::connect(csvButton, &QPushButton::clicked, this, &GUI::setCSVFile);
    QObject::connect(htmlButton, &QPushButton::clicked, this, &GUI::setHTMLFile);

    fileTypeWidget->show();

}

void GUI::setCSVFile() {
    // set the file type to CSV
    this->serviceUser.setRepoAdopted(new RepoAdoptedDogsCSV);

    // close the file type widget
    this->fileTypeWidget->close();

    // start the user mode GUI
    this->UserModeGUI();
}

void GUI::setHTMLFile() {
    // set the file type to HTML
    this->serviceUser.setRepoAdopted(new RepoAdoptedDogsHTML);

    // close the file type widget
    this->fileTypeWidget->close();

    // start the user mode GUI
    this->UserModeGUI();
}


void GUI::UserModeGUI(){
    // it will be fragmented in 3 vertical parts:
    // - the title  "~ User Mode ~"
    // - the main part, where the user can see the dogs, and the buttons
    // -- the main part will be fragmented in 2 horizontal parts:
    // --- the left part, also fragmented in 2 horizontal parts:
    // ---- the top part, where will be the title Sheltered Dogs
    // ---- the bottom part, where will be the list of dogs from the shelter
    // --- the right part, also fragmented in 3 horizontal parts:
    // ---- the top part, where will be the title Current Dog
    // ---- the middle part, where will be the dog's data, in a form layout like in the admin mode
    // ---- the bottom part, where will be the buttons Show Photo, Adopt Dog, Next Dog, See Adopted List, Save and Exit
    // - the bottom part will be fragmented in 2 vertical parts:
    // -- the up part will be also fragmented in 2 horizontal parts:
    // --- the left part will have the Breed form layout like in the admin mode
    // --- the right part will have the Age form layout like in the admin mode
    // -- the bottom part will have a button called Filter

    // read the dogs from the file only if the list is empty
    if(this->serviceUser.getDogsShelter().empty()){
        this->serviceUser.readShelterDogFromFile();
    }
    if(this->serviceUser.getDogsAdopted().empty()){
        this->serviceUser.readAdoptedDogFromFile();
    }


    /// the big widget containing all the other widgets
    {
        userWidget = new QWidget{};

        this->userWidget->setWindowTitle("Keep Calm and Adopt a Dog Shelter");
        this->userWidget->setWindowIcon(QIcon(R"(C:\Users\Admin\Documents\GitHub\a89-912-enache-vlad\animal-shelter.png)"));

        userWidget->show();


        userWidget->setMinimumSize(600, 600);
        auto *mainLayout = new QVBoxLayout{userWidget};
        userWidget->setLayout(mainLayout);

        /// the title
        {
            auto *titleLabel = new QLabel{"~ User Mode ~"};
            QFont titleFont("Arial", 20, QFont::Bold);
            titleLabel->setFont(titleFont);
            titleLabel->setAlignment(Qt::AlignCenter);
            mainLayout->addWidget(titleLabel);
        }

        /// the main part
        {
            auto *mainPartWidget = new QWidget{};
            auto *mainPartLayout = new QHBoxLayout{mainPartWidget};
            mainPartWidget->setLayout(mainPartLayout);
            mainLayout->addWidget(mainPartWidget);

            /// the left part
            {
                auto *leftPartWidget = new QWidget{};
                auto *leftPartLayout = new QVBoxLayout{leftPartWidget};
                leftPartWidget->setLayout(leftPartLayout);
                mainPartLayout->addWidget(leftPartWidget);

                /// the top part of the left part
                auto *leftTopPartWidget = new QWidget{};
                auto *leftTopPartLayout = new QHBoxLayout{leftTopPartWidget};
                leftTopPartWidget->setLayout(leftTopPartLayout);
                leftPartLayout->addWidget(leftTopPartWidget);

                /// the title Sheltered Dogs
                auto *shelteredDogsLabel = new QLabel{"Sheltered Dogs:"};
                QFont shelteredDogsFont("Arial", 15, QFont::Bold);
                shelteredDogsLabel->setFont(shelteredDogsFont);
                leftTopPartLayout->addWidget(shelteredDogsLabel);

                /// the bottom part of the left part
                auto *leftBottomPartWidget = new QWidget{};
                auto *leftBottomPartLayout = new QHBoxLayout{leftBottomPartWidget};
                leftBottomPartWidget->setLayout(leftBottomPartLayout);
                leftPartLayout->addWidget(leftBottomPartWidget);

                /// the list of dogs from the shelter
                this->dogsListWidget = new QListWidget{};
                leftBottomPartLayout->addWidget(this->dogsListWidget);
                this->dogList = this->serviceUser.getDogsShelter();
                populateListUserMode();
                this->dogsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);

                int size = this->serviceUser.getDogsShelter().size();
                this->dogsListWidget->setCurrentRow(size - 1);
                // TODO: I have to find why I can not show the data first time
//                showDogDataUser();

                QObject::connect(this->dogsListWidget, &QListWidget::itemSelectionChanged, this, &GUI::showDogDataUser);
            }

            /// the right part
            {
                auto *rightPartWidget = new QWidget{};
                auto *rightPartLayout = new QVBoxLayout{rightPartWidget};
                rightPartWidget->setLayout(rightPartLayout);
                mainPartLayout->addWidget(rightPartWidget);

                /// the top part of the right part
                auto *rightTopPartWidget = new QWidget{};
                auto *rightTopPartLayout = new QHBoxLayout{rightTopPartWidget};
                rightTopPartWidget->setLayout(rightTopPartLayout);
                rightPartLayout->addWidget(rightTopPartWidget);

                /// the title Current Dog
                auto *currentDogLabel = new QLabel{"Current Dog:"};
                QFont currentDogFont("Arial", 15, QFont::Bold);
                currentDogLabel->setFont(currentDogFont);
                rightTopPartLayout->addWidget(currentDogLabel);

                /// the middle part of the right part
                {
                    auto *rightMiddlePartWidget = new QWidget{};
                    auto *rightMiddlePartLayout = new QFormLayout{rightMiddlePartWidget};
                    rightMiddlePartWidget->setLayout(rightMiddlePartLayout);
                    rightPartLayout->addWidget(rightMiddlePartWidget);

                    /// the form line info
                    {
                        this->nameLabelInfo = new QLabel{};
                        this->nameLabelInfo->setAlignment(Qt::AlignCenter);
                        this->nameLabelInfo->setMinimumWidth(100);
                        this->nameLabelInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);

                        this->breedLabelInfo = new QLabel{};
                        this->breedLabelInfo->setAlignment(Qt::AlignCenter);
                        this->breedLabelInfo->setMinimumWidth(100);
                        this->breedLabelInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);

                        this->ageLabelInfo = new QLabel{};
                        this->ageLabelInfo->setAlignment(Qt::AlignCenter);
                        this->ageLabelInfo->setMinimumWidth(100);
                        this->ageLabelInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);

                        this->photoLabelInfo = new QLabel{};
                        this->photoLabelInfo->setAlignment(Qt::AlignCenter);
                        this->photoLabelInfo->setMinimumWidth(300);
                        this->photoLabelInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    }

                    /// form labels
                    {
                        QFont formFont("Arial", 15, QFont::Bold);

                        auto *nameLabel = new QLabel{"Name:"};
                        nameLabel->setFont(formFont);
                        nameLabel->setMinimumWidth(100);
                        nameLabel->setAlignment(Qt::AlignCenter);

                        auto *breedLabel = new QLabel{"Breed:"};
                        breedLabel->setFont(formFont);
                        breedLabel->setMinimumWidth(100);
                        breedLabel->setAlignment(Qt::AlignCenter);

                        auto *ageLabel = new QLabel{"Age:"};
                        ageLabel->setFont(formFont);
                        ageLabel->setMinimumWidth(100);
                        ageLabel->setAlignment(Qt::AlignCenter);

                        /// adding the form labels and info to the form layout
                        {
                            rightMiddlePartLayout->addRow(nameLabel, nameLabelInfo);
                            rightMiddlePartLayout->addRow(breedLabel, breedLabelInfo);
                            rightMiddlePartLayout->addRow(ageLabel, ageLabelInfo);
                        }
                    }
                }

                /// the bottom part of the right part
                {
                    auto *rightBottomPartWidget = new QWidget{};
                    auto *rightBottomPartLayout = new QVBoxLayout{rightBottomPartWidget};
                    rightBottomPartWidget->setLayout(rightBottomPartLayout);
                    rightPartLayout->addWidget(rightBottomPartWidget);

                    /// the buttons
                    {
                        /// show photo button
                        {
                            this->showPhotoButton = new QPushButton{"Show Photo"};
                            rightBottomPartLayout->addWidget(this->showPhotoButton);
                            QObject::connect(this->showPhotoButton, &QPushButton::clicked, this, &GUI::showPhoto);
                        }

                        /// the adopt dog button
                        {
                            this->adoptDogButton = new QPushButton{"Adopt Dog"};
                            rightBottomPartLayout->addWidget(this->adoptDogButton);
                            QObject::connect(this->adoptDogButton, &QPushButton::clicked, this, &GUI::adoptDogGUI);
                        }

                        /// the Next Dog button
                        {
                            this->nextDogButton = new QPushButton{"Next Dog"};
                            rightBottomPartLayout->addWidget(this->nextDogButton);
                            QObject::connect(this->nextDogButton, &QPushButton::clicked, this, &GUI::nextDogGUI);
                        }

                        /// See Adoption List button
                        {
                            this->seeAdoptedDogsButton = new QPushButton{"See Adoption List"};
                            rightBottomPartLayout->addWidget(this->seeAdoptedDogsButton);
                            QObject::connect(this->seeAdoptedDogsButton, &QPushButton::clicked, this, &GUI::seeAdoptedDogsGUI);
                        }

                        /// the Save and Exit button
                        {
                            this->saveAndExitUserButton = new QPushButton{"Save and Exit"};
                            rightBottomPartLayout->addWidget(this->saveAndExitUserButton);
                            QObject::connect(this->saveAndExitUserButton, &QPushButton::clicked, this, &GUI::saveAndExitUserGUI);
                        }
                    }
                }
            }
        }

        /// the bottom part -
        {
            auto *bottomPartWidget = new QWidget{};
            auto *bottomPartLayout = new QVBoxLayout{bottomPartWidget};
            bottomPartWidget->setLayout(bottomPartLayout);
            mainLayout->addWidget(bottomPartWidget);

            /// the up part
            {
                auto *bottomUpPartWidget = new QWidget{};
                auto *bottomUpPartLayout = new QHBoxLayout{bottomUpPartWidget};
                bottomUpPartWidget->setLayout(bottomUpPartLayout);
                bottomPartLayout->addWidget(bottomUpPartWidget);


                /// the breed filter
                {
                    auto *breedFilterWidget = new QWidget{};
                    auto *breedFilterLayout = new QVBoxLayout{breedFilterWidget};
                    breedFilterWidget->setLayout(breedFilterLayout);
                    bottomUpPartLayout->addWidget(breedFilterWidget);

                    /// the breed filter label
                    {
                        auto *breedFilterLabel = new QLabel{"Breed:"};
                        QFont breedFilterFont("Arial", 10, QFont::Bold);
                        breedFilterLabel->setFont(breedFilterFont);
                        breedFilterLayout->addWidget(breedFilterLabel);
                    }

                    /// the breed filter line
                    {
                        this->breedLineEdit = new QLineEdit{};
                        breedFilterLayout->addWidget(this->breedLineEdit);
                    }
                }

                /// the age filter
                {
                    auto *ageFilterWidget = new QWidget{};
                    auto *ageFilterLayout = new QVBoxLayout{ageFilterWidget};
                    ageFilterWidget->setLayout(ageFilterLayout);
                    bottomUpPartLayout->addWidget(ageFilterWidget);

                    /// the age filter label
                    {
                        auto *ageFilterLabel = new QLabel{"Age:"};
                        QFont ageFilterFont("Arial", 10, QFont::Bold);
                        ageFilterLabel->setFont(ageFilterFont);
                        ageFilterLayout->addWidget(ageFilterLabel);
                    }

                    /// the age filter line
                    {
                        this->ageLineEdit = new QLineEdit{};
                        ageFilterLayout->addWidget(this->ageLineEdit);
                    }
                }

            }

            /// the down part
            {
                auto *bottomDownPartWidget = new QWidget{};
                auto *bottomDownPartLayout = new QHBoxLayout{bottomDownPartWidget};
                bottomDownPartWidget->setLayout(bottomDownPartLayout);
                bottomPartLayout->addWidget(bottomDownPartWidget);

                /// the filter button
                {
                    this->seeFilteredDogsButton = new QPushButton{"Filter"};
                    bottomDownPartLayout->addWidget(this->seeFilteredDogsButton);
                    QObject::connect(this->seeFilteredDogsButton, &QPushButton::clicked, this, &GUI::filterDogsGUI);
                }
            }
        }
    }

}

void GUI::populateListUserMode() {
    // clear the list
    this->dogsListWidget->clear();

    // get the list of dogs from the shelter
    auto dogs = this->dogList;

    if(dogs.empty()){
        QString emptyString = "No dogs left in the shelter!";
        auto *emptyItem = new QListWidgetItem{emptyString};
        this->dogsListWidget->addItem(emptyItem);
    }

    // add the dogs to the list
    for (auto &dog : dogs) {
        QString dogString = QString::fromStdString(dog.getName() + " - " + dog.getBreed());
        auto *dogItem = new QListWidgetItem{dogString};
        this->dogsListWidget->addItem(dogItem);
    }

}

void GUI::showDogDataUser() {
    // get the selected index
    auto selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty())
        return;

    // get the name of the dog from the list

    int selectedIndex = selectedIndexes.at(0).row();

    // get the dog at the selected index
    auto nameAndBreed = selectedIndexes.at(0).data().toString().toStdString();
    auto name = nameAndBreed.substr(0, nameAndBreed.find(" - "));

    auto dog = this->serviceAdmin.getDogByName(name);

    // set the text of the lineEdits with the dog data
    this->nameLabelInfo->setText(QString::fromStdString(dog.getName()));
    this->breedLabelInfo->setText(QString::fromStdString(dog.getBreed()));
    this->ageLabelInfo->setText(QString::number(dog.getAge()));
    this->photoLabelInfo->setText(QString::fromStdString(dog.getPhotograph()));



}

void GUI::showPhoto() {
    // get the selected index
    auto selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty())
        return;

    int selectedIndex = selectedIndexes.at(0).row();

    // get the dog at the selected index
    auto dogs = this->serviceUser.getDogsShelter();
    if (selectedIndex >= dogs.size())
        return;
    auto dog = dogs[selectedIndex];

    // open the photo in a browser
    QString link = QString::fromStdString(dog.getPhotograph());
    QDesktopServices::openUrl(QUrl(link));

}

void GUI::nextDogGUI() {
    // get the selected index
    auto selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty())
        return;

    int selectedIndex = selectedIndexes.at(0).row();

    // get the dog at the selected index
    auto dogs = this->dogList;
    if (selectedIndex >= dogs.size())
        return;
    auto dog = dogs[selectedIndex];

    // set the text of the lineEdits with the dog data
    this->nameLabelInfo->setText(QString::fromStdString(dog.getName()));
    this->breedLabelInfo->setText(QString::fromStdString(dog.getBreed()));
    this->ageLabelInfo->setText(QString::number(dog.getAge()));
    this->photoLabelInfo->setText(QString::fromStdString(dog.getPhotograph()));

    // select the next dog in the list
    if (selectedIndex == dogs.size() - 1)
        selectedIndex = 0;
    else
        selectedIndex++;
    this->dogsListWidget->setCurrentRow(selectedIndex);


}

void GUI::adoptDogGUI() {
    // get the selected index
    auto selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty())
        return;

    int selectedIndex = selectedIndexes.at(0).row();

    // get the dog at the selected index
    auto nameAndBreed = selectedIndexes.at(0).data().toString().toStdString();
    auto name = nameAndBreed.substr(0, nameAndBreed.find(" - "));

    cout << name << endl;
    auto dog = this->serviceAdmin.getDogByName(name);


    /// if here we are not in the filtered list
    if(this->dogList == this->serviceUser.getDogsShelter()) {
        // adopt the dog
        try {
            this->serviceUser.adoptDog(dog.getName());
        }
        catch (std::exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
        // update the list
        this->dogList = this->serviceUser.getDogsShelter();


    }
    else{
        // adopt the dog
        try {
            this->serviceUser.adoptDog(dog.getName());
        }
        catch (std::exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }

        // open again filtered list
        this->filterDogsGUI();
    }

    this->populateListUserMode();

    // set the index to the next dog
    if (selectedIndex == this->dogList.size())
        selectedIndex = 0;
    this->dogsListWidget->setCurrentRow(selectedIndex);

    // clear the lineEdits
    this->nameLabelInfo->clear();
    this->breedLabelInfo->clear();
    this->ageLabelInfo->clear();
    this->photoLabelInfo->clear();

}

void GUI::seeAdoptedDogsGUI() {
    // open the file with the adopted dogs
    this->serviceUser.getRepoAdopted()->write();
    this->serviceUser.getRepoAdopted()->display();
}

void GUI::saveAndExitUserGUI() {
    // save the adoption list
    this->serviceUser.saveShelterDogToFile();

    // save the shelter list
    this->serviceUser.saveAdoptedDogToFile();

    // exit the user mode
    this->userWidget->close();
//    this->userWidget = nullptr;
    this->show();
}

void GUI::filterDogsGUI() {
    // get the breed and age
    QString breed = this->breedLineEdit->text();
    QString age = this->ageLineEdit->text();

    if (breed.isEmpty() || age.isEmpty()) {
        /// if the breed or age are empty, show all the dogs
        this->dogList = this->serviceUser.getDogsShelter();
        int size = this->serviceUser.getDogsShelter().size();
        this->dogsListWidget->setCurrentRow(0);
        populateListUserMode();

    }
    else {
        // convert the age to int
        int ageInt = age.toInt();

        // filter the dogs
        auto filteredDogs = this->serviceUser.getDogsFiltered(breed.toStdString(), ageInt);

        /// change the dogList to the filtered dogs
        this->dogList = filteredDogs;

        // populate the list with the filtered dogs
        this->dogsListWidget->clear();

        if (filteredDogs.empty()) {
            // if there are no more filtered dogs, come back to all dogs
            this->dogList = this->serviceUser.getDogsShelter();
        }
        else {
            for (auto &dog: filteredDogs) {
                QString dogString = QString::fromStdString(dog.getName() + " - " + dog.getBreed());
                auto *dogItem = new QListWidgetItem{dogString};
                this->dogsListWidget->addItem(dogItem);
            }


            this->dogsListWidget->setCurrentRow(0);
        }
    }
}
