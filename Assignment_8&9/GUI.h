#pragma once

#include "ServiceAdmin.h"
#include "ServiceUser.h"

#include <vector>

#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QMessageBox>

class GUI : public QWidget {
    //for any non-templated classes that derive from QObject (ex:signals and slots)
    //Q_OBJECT
private:
    ServiceAdmin& serviceAdmin;
    ServiceUser& serviceUser;

    /// first page
    QPushButton* adminModeButton{};
    QPushButton* userModeButton{};

    /// second page for user
    QPushButton* csvButton{};
    QPushButton* htmlButton{};

    /// --- admin mode ---
    QWidget* adminWidget{};

    /// buttons for the admin mode
    QPushButton* addDogButton{};
    QPushButton* deleteDogButton{};
    QPushButton* updateDogButton{};
    QPushButton* saveAndExitButton{};

    /// lines edit for the add, update and delete dog buttons
    QLineEdit* nameLineEdit{};
    QLineEdit* breedLineEdit{};
    QLineEdit* ageLineEdit{};
    QLineEdit* photoLineEdit{};

    /// --- user mode ---
    QWidget* userWidget{};
    QWidget* fileTypeWidget{};

    /// buttons for the user mode
    QPushButton* showPhotoButton{};
    QPushButton* nextDogButton{};
    QPushButton* adoptDogButton{};
    QPushButton* seeAdoptedDogsButton{};
    QPushButton* saveAndExitUserButton{};
    QPushButton* seeFilteredDogsButton{};


    /// labels for the dog data
    QLabel* nameLabelInfo{};
    QLabel* breedLabelInfo{};
    QLabel* ageLabelInfo{};
    QLabel* photoLabelInfo{};

    /// widgets for all application
    QListWidget* dogsListWidget{};

    std::vector<Dog> dogList;

public:
    // constructor
    GUI(ServiceAdmin& serviceAdminToBeSet, ServiceUser& serviceUserToBeSet, QWidget* parent = Q_NULLPTR);

    // destructor
    ~GUI() override;

    /// admin mode
    void AdminModeGUI();

    void addDogGUI();
    void deleteDogGUI();
    void updateDogGUI();
    void saveAndExitAdminGUI();

    void populateListAdminMode();
    void showDogDataAdmin();

    /// user mode
    void chooseFileType();

    void setCSVFile();
    void setHTMLFile();

    void UserModeGUI();

    void populateListUserMode();

    [[maybe_unused]] void showDogDataUser();

    void showPhoto();
    void nextDogGUI();
    void adoptDogGUI();
    void seeAdoptedDogsGUI();
    void filterDogsGUI();

    void saveAndExitUserGUI();

};

