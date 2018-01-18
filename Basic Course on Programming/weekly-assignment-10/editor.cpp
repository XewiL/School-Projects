#include "editor.hh"
#include "ui_editor.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <string>

using namespace std;

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);

    // In the beginning before the user has had any chance
    // to type text in the editor, the text has not been
    // modified and therefore save button doesn't need to be
    // active (i.e. it is grayed out).
    text_modified_ = false;
    ui->saveButton->setEnabled(false);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_quitButton_clicked() {
    // If the text has been modified better not quit right away
    // but instead ask the user for a confirmation since if
    // quit happens, all the modifications to the text are lost.
    if ( text_modified_ ) {
        int answer = QMessageBox::warning(this,
                                          "Unsaved Modifications",
                                          "You have unsaved modifications.\n"
                                            "Are you sure you want to quit?",
                                          QMessageBox::Yes|QMessageBox::Cancel);

        if ( answer == QMessageBox::Yes ) {
            QApplication::quit();

        } else {

            return;
        }

    } else {

        QApplication::quit();
    }
}


void Editor::on_textEditor_textChanged()
{
    // If any changes have been made to the text, let's
    // keep track of that in text_modified_ and also
    // activate the save button so the user has a chance to
    // save the modifications.
    text_modified_ = true;
    ui->saveButton->setEnabled(true);
}


void Editor::on_loadButton_clicked() {
    // If there are earlier modifications in the editor window,
    // let's make sure the user wants to throw them away and start
    // editing a new file instead.
    if ( text_modified_ ) {
        int answer = QMessageBox::warning(this,
                                          "Unsaved Modifications",
                                          "You have unsaved modifications.\n"
                                            "You sure you want to load a new file?",
                                          QMessageBox::Ok|QMessageBox::Cancel);

        if ( answer == QMessageBox::Cancel ) {

            return;
        }
    }

    // QFileDialog::getOpenFileName is an easy way to ask filename from the user.
    filename_ = QFileDialog::getOpenFileName(this,
                                            "Choose Filename to Edit",
                                            "",
                                            ".txt files (*.txt);;All files (*.*)");

    // In case there was some old text in the editor, let's clear it.
    // This is not really necessary, as the setPlainText method a few lines
    // down would replace the contents of textEditor anyways.
    ui->textEditor->clear();

    // QFileDialog::getOpenFileName returns filename as QString type value.
    // if we want to use regular fstream librabry to read the file, we
    // have to convert QString into standard C++ string.  This is because
    // ifstream expects filename to be given as standard string.
    string std_filename = filename_.toStdString();
    string file_contents;

    // Read the file here using ifstream. Let's simulate it and
    // assume the file had two lines of text:
    //   Hello,
    //   My name is.....
    file_contents = "Hello,\nMy name is.....\n";

    // textEditor (QPlainTextEdit widget) requires text to be QString
    // so file_contents must be manually converted into equivalent
    // QString type value which can then be stored in the textEditor.
    ui->textEditor->setPlainText(QString::fromStdString(file_contents));

    // File was just read i.e. no modifications have been done.
    // Let's update the bookkeeping and deactivate save button.
    text_modified_ = false;
    ui->saveButton->setEnabled(false);
}


// Save napin toteutus menee samalla logiikalla kuin Open pienin muutoksin
// tai ns. päinvastaisessa järjestyksessä.
void Editor::on_saveButton_clicked() {

    // Jos ei olla ennestään tallennettu mitään, pyydetään tiedostonnimi
    // johon tallennetaan
    if (filename_.isEmpty()) {
        // QFileDialog::getSaveFileName syntaksi samalla lailla kuin load
        filename_ = QFileDialog::getSaveFileName(this,
                                                 "Save file",
                                                 "",
                                                 ".txt files (*.txt);;All files (*.*)");

        // Jos nyt dialog ikkunassa oltiin painettu cancel,
        // niin tiedoston nimi on edelleen tyhjä eli
        // palataan tekstieditoriin tallentamatta.
        if (filename_.isEmpty()) {
            return;
        }
    }

    // TextEditorista saadaan teksti QString muodossa, joten
    // käännetään se aps:in toiveiden mukaan normi stringiksi
    // ennen kuin se tallennetaan.
    string allText = ui->textEditor->toPlainText().toStdString();
    string std_filename = filename_.toStdString();

    // --
    // ofstreameilla tiedoston tallennuksen simulointi tähän???
    // --

    // Lopuksi deaktivoidaan save-nappi ja kerrotaan että tekstiä ei olla muokattu.
    ui->saveButton->setEnabled(false);
    text_modified_ = false;
}
