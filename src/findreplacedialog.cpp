/*
* Copyright (C) 2021 Yet-Zio

* Redistribution and use in source and binary forms,
* with or without modification, are permitted provided
* that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation and/or other
*    materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or
*    promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*	findreplacedialog.cpp    (Thiruvananthapuram) 11th April 2020
*
*/

#include <QtWidgets>
#include "findreplacedialog.h"


FindReplaceDialog::FindReplaceDialog(QWidget *parent) : QDialog(parent)
{

    label = new QLabel(tr("Find &what: "));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    replaceLabel = new QLabel(tr("Replace with: "));
    replaceField = new QLineEdit;
    replaceLabel->setBuddy(replaceField);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    caseCheckBox->setChecked(true);
    fromStartCheckBox = new QCheckBox(tr("Search from &start"));
    fromStartCheckBox->setChecked(true);
    regexCheckBox = new QCheckBox(tr("Regex"));
    regexCheckBox->setChecked(false);

    findButton = new QPushButton(tr("&Find"));
    connect(findButton, SIGNAL(clicked()), this, SLOT(find()));
    findButton->setDefault(true);

    replaceButton = new QPushButton(tr("&Replace"));
    connect(replaceButton, SIGNAL(clicked()), this, SLOT(replace()));

    replaceAllButton = new QPushButton(tr("Replace All"));
    connect(replaceAllButton, SIGNAL(clicked()), this, SLOT(replaceAll()));

    moreButton = new QPushButton(tr("&More"));
    moreButton->setCheckable(true);

    moreButton->setAutoDefault(false);

    extension = new QWidget;

    wholeWordsCheckBox = new QCheckBox(tr("&Whole words"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));
    searchSelectionCheckBox = new QCheckBox(tr("Search se&lection"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(findButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(replaceButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(replaceAllButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(moreButton, QDialogButtonBox::ActionRole);

    connect(regexCheckBox, SIGNAL(toggled(bool)), this, SLOT(regexMode()));

    connect(moreButton, &QAbstractButton::toggled, extension, &QWidget::setVisible);

    QVBoxLayout *extensionLayout = new QVBoxLayout;
    extensionLayout->setContentsMargins(QMargins());
    extensionLayout->addWidget(wholeWordsCheckBox);
    extensionLayout->addWidget(backwardCheckBox);
    extensionLayout->addWidget(searchSelectionCheckBox);
    extension->setLayout(extensionLayout);

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QHBoxLayout *replaceLayout = new QHBoxLayout;
    replaceLayout->addWidget(replaceLabel);
    replaceLayout->addWidget(replaceField);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addLayout(replaceLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(regexCheckBox);
    leftLayout->addWidget(fromStartCheckBox);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addWidget(buttonBox, 0, 1);
    mainLayout->addWidget(extension, 1, 0, 1, 2);
    mainLayout->setRowStretch(2, 1);

    setLayout(mainLayout);

    setWindowTitle(tr("Find and Replace"));

    extension->hide();
}

void FindReplaceDialog::find(){
    QString query = lineEdit->text();
    QRegularExpression re;
    QPlainTextEdit *Editor = getEditor();

    if(fromStartCheckBox->isChecked()){
        cursor = Editor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        Editor->setTextCursor(cursor);
    }
    fromStartCheckBox->setChecked(false);

    if(regexCheckBox->isChecked()){
        re = QRegularExpression(query);
        if(backwardCheckBox->isChecked()){
            lastMatch = Editor->find(re, QTextDocument::FindBackward);
        }
        else{
            lastMatch = Editor->find(re);
        }
    }

    if(searchSelectionCheckBox->isChecked()){
        query = Editor->textCursor().selectedText();
        Editor->find(query);
    }

    else{
        if(backwardCheckBox->isChecked()){
            if(wholeWordsCheckBox->isChecked() and caseCheckBox->isChecked()){
                lastMatch = Editor->find(query, QTextDocument::FindWholeWords | QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
            }
            else if(wholeWordsCheckBox->isChecked() and caseCheckBox->isChecked() != true){
                lastMatch = Editor->find(query, QTextDocument::FindWholeWords | QTextDocument::FindBackward);
            }
            else if(caseCheckBox->isChecked()){
                lastMatch = Editor->find(query, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
            }
            else{
                lastMatch = Editor->find(query, QTextDocument::FindBackward);
            }
        }
        else{
            if(wholeWordsCheckBox->isChecked() and caseCheckBox->isChecked()){
                lastMatch = Editor->find(query, QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively);
            }
            else if(wholeWordsCheckBox->isChecked() and caseCheckBox->isChecked() != true){
                lastMatch = Editor->find(query, QTextDocument::FindWholeWords);
            }
            else if(caseCheckBox->isChecked()){
                lastMatch = Editor->find(query, QTextDocument::FindCaseSensitively);
            }
            else{
                lastMatch = Editor->find(query);
            }
        }
    }
}

void FindReplaceDialog::replace(){
    QPlainTextEdit *Editor = getEditor();
    cursor = Editor->textCursor();

    if(cursor.hasSelection()){
        cursor.insertText(replaceField->text());
        Editor->setTextCursor(cursor);
    }
}

void FindReplaceDialog::replaceAll(){
    lastMatch = false;
    find();
    replace();

    QPlainTextEdit *Editor = getEditor();
    for(int i = 0; i<Editor->document()->lineCount(); i++){
        find();
        replace();
    }
}


void FindReplaceDialog::regexMode(){
    caseCheckBox->setChecked(false);
    wholeWordsCheckBox->setChecked(false);

    caseCheckBox->setEnabled(false);
    wholeWordsCheckBox->setEnabled(false);
}
