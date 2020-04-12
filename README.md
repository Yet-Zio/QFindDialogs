# QFindDialogs
A custom working Qt-based dialog with Find, Replace and RegEX search functionalities based on the Extension Example.
You are Free to use this project under the BSD-3 Clause License. Please refer the License Terms for your project compatibility.
There are two available dialogs:

* [Find Dialog](#finddialog)
* [Find and Replace Dialog](#findreplacedialog)

### Public Functions (FindDialog)
| Type                 | Function                                |
| -------------------- | --------------------------------------- |
| *explicit*           |  [FindDialog](#explicit-finddialogfinddialogqwidget-parent--nullptr)(QWidget *parent = nullptr)  |
| *void*               |  [setEditor](#void-finddialogseteditorqplaintextedit-editor)(QPlainTextEdit *editor)      |
| *QPlainTextEdit**    |  [getEditor](#qplaintextedit-finddialoggeteditor)()                            |

### Private Slots (FindDialog)
| Type                 | Function                                |
| -------------------- | --------------------------------------- |
| *void*               | [find](#void-finddialogfind)()                                  |
| *void*               | [regexMode](#void-finddialogregexmode)()                             |

### Public Functions (FindReplaceDialog)
| Type                 | Function                                |
| -------------------- | --------------------------------------- |
| *explicit*           |  [FindReplaceDialog](#explicit-findreplacedialogfindreplacedialogqwidget-parent--nullptr)(QWidget *parent = *nullptr*)|
| *void*               |  [setEditor](#void-findreplacedialogseteditorqplaintextedit-editor)(QPlainTextEdit *editor)      |
| *QPlainTextEdit**    |  [getEditor](#qplaintextedit-findreplacedialoggeteditor)()                            |

### Private Slots (FindReplaceDialog)
| Type                 | Function                                |
| -------------------- | --------------------------------------- |
| *void*               | [find](#void-findreplacedialogfind)()                                  |
| *void*               | [replace](#void-findreplacedialogreplace)()                               |
| *void*               | [replaceAll](#void-findreplacedialogreplaceall)()                            |
| *void*               | [regexMode](#void-findreplacedialogregexmode)()                             |

## FindDialog
#### Sample Images:
  ![FindDialog](https://github.com/Master-Console/QFindDialogs/blob/master/snaps/screenshot2.png)
  
  The more button expands the remaining available options with its individual functionality provided as seen here:
  
  ![FindExpandedDialog](https://github.com/Master-Console/QFindDialogs/blob/master/snaps/screenshot3.png)
## FindReplaceDialog
#### Sample Images:
  ![FindReplaceDialog](https://github.com/Master-Console/QFindDialogs/blob/master/snaps/screenshot.png)
  
  The more button expands the same as it expanded before in FindDialog with the options.
  
  # _Documentation_
### Public Functions
#### *explicit* FindDialog::FindDialog(QWidget *parent = *nullptr*) 
###### Constructs a Find Dialog with the given parent.
###### FindDialog inherits from QDialog.
#### *void* FindDialog::setEditor(QPlainTextEdit *editor)
###### Sets the current active editor of the find dialog object to the specified one.
#### *QPlainTextEdit** FindDialog::getEditor()
###### Returns the current active editor of the find dialog object to the specified one.
#### *void* FindDialog::find()
###### Finds the query text in the find field, sets a selection to the found substring and sets the cursor at the end.
###### find() checks various checkboxes and does the exact search function.
#### *void* FindDialog::regexMode()
###### If regex-CheckBox is ticked, this method runs ensuring a Regular Expression mode for the find dialog to
###### search in the current editor. The find() then searches for a QRegularExpression in the Editor.
---
#### *explicit* FindReplaceDialog::FindReplaceDialog(QWidget *parent = *nullptr*) 
###### Constructs a Find and Replace Dialog with the given parent.
###### FindReplaceDialog inherits from QDialog and contains all the functions and properties from FindDialog.
#### *void* FindReplaceDialog::setEditor(QPlainTextEdit *editor)
###### Sets the current active editor of the find dialog object to the specified one.
#### *QPlainTextEdit** FindReplaceDialog::getEditor()
###### Returns the current active editor of the find dialog object to the specified one.
#### *void* FindReplaceDialog::find()
###### Finds the query text in the find field, sets a selection to the found substring and sets the cursor at the end.
###### find() checks various checkboxes and does the exact search function.
#### *void* FindReplaceDialog::replace()
###### Replaces the query selected by the find() and sets the cursor at the end of the replaced substring.
#### *void* FindReplaceDialog::replaceAll()
###### Replaces all occurences of the query selected by find() and the sets the cursor at the end of the last substring replaced.
#### *void* FindReplaceDialog::regexMode()
###### If regex-CheckBox is ticked, this method runs ensuring a Regular Expression mode for the find dialog to
###### search in the current editor. The find() then searches for a QRegularExpression in the Editor.
---
# _Usage_
#### FindDialog
```c++
QPlainTextEdit *myEditor = new QPlainTextEdit;
FindDialog *fdialog = new FindDialog(this);
fdialog->setEditor(myEditor);
fdialog->show();
```
#### FindReplaceDialog
```c++
QPlainTextEdit *myEditor = new QPlainTextEdit;
FindReplaceDialog *frDialog = new FindReplaceDialog(this);
frdialog->setEditor(myEditor);
frdialog->show();
```
