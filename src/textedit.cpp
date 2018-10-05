/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextCodec>
#include <QPushButton>
#include <QBoxLayout>
#include <QRadioButton>
#include <QTextTable>
#include <QTextTableCell>
#include <QLabel>
#include <QTextEdit>
#include <QStatusBar>
#include <QSpinBox>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif

#include "textedit.h"

#ifdef Q_OS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif

TextEdit::TextEdit(ret_str *arg, QWidget *parent, TextEdit_opt pto)
    : QMainWindow(parent), opt{pto}
{
#ifdef Q_OS_OSX
    setUnifiedTitleAndToolBarOnMac(true);
#endif
    setWindowTitle(QCoreApplication::applicationName());
    sv = arg;
    textEdit = new QTextEdit(this);
    connect(textEdit, &QTextEdit::currentCharFormatChanged,
            this, &TextEdit::currentCharFormatChanged);
    connect(textEdit, &QTextEdit::cursorPositionChanged,
            this, &TextEdit::cursorPositionChanged);
    setCentralWidget(textEdit);

    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    setupFileActions();
    setupEditActions();
    setupTextActions();
    setupTableActions();

    QFont textFont("Helvetica");
    textFont.setStyleHint(QFont::SansSerif);
    textEdit->setFont(textFont);
    fontChanged(textEdit->font());
    colorChanged(textEdit->textColor());
    alignmentChanged(textEdit->alignment());

    connect(textEdit->document(), &QTextDocument::modificationChanged,
            actionSave, &QAction::setEnabled);
    connect(textEdit->document(), &QTextDocument::modificationChanged,
            this, &QWidget::setWindowModified);
    connect(textEdit->document(), &QTextDocument::undoAvailable,
            actionUndo, &QAction::setEnabled);
    connect(textEdit->document(), &QTextDocument::redoAvailable,
            actionRedo, &QAction::setEnabled);

    setWindowModified(textEdit->document()->isModified());
    actionSave->setEnabled(textEdit->document()->isModified());
    actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
    actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

#ifndef QT_NO_CLIPBOARD
    actionCut->setEnabled(false);
    actionCopy->setEnabled(false);

    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &TextEdit::clipboardDataChanged);
#endif

    textEdit->setFocus();
    setCurrentFileName(QString());
}
void TextEdit::closeEvent(QCloseEvent *e)
{
    if (maybeSave()){
        emit svexit();
        e->accept();
    }
    else
        e->ignore();
}
void TextEdit::setupFileActions()
{
    QToolBar *tb = addToolBar(tr("File Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&Файл"));

    menu->addSeparator();

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(rsrcPath + "/filesave.png"));
    actionSave = menu->addAction(saveIcon, tr("&Сохранить"), this, &TextEdit::fileSave);
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setEnabled(false);
    tb->addAction(actionSave);

    QAction *a = menu->addAction(tr("Сохранить &как..."), this, &TextEdit::fileSaveAs);
    a->setPriority(QAction::LowPriority);
    menu->addSeparator();

    if (opt == TextEdit_opt::pattern){
        const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(rsrcPath + "/fileopen.png"));
        a = menu->addAction(openIcon, tr("&Экспортировать из..."), this, &TextEdit::fileOpen);
        a->setShortcut(QKeySequence::Open);
        tb->addAction(a);
        menu->addSeparator();
    }

#ifndef QT_NO_PRINTER
    const QIcon printIcon = QIcon::fromTheme("document-print", QIcon(rsrcPath + "/fileprint.png"));
    a = menu->addAction(printIcon, tr("&Печать..."), this, &TextEdit::filePrint);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Print);
    tb->addAction(a);

    const QIcon filePrintIcon = QIcon::fromTheme("fileprint", QIcon(rsrcPath + "/fileprint.png"));
    menu->addAction(filePrintIcon, tr("Предварительный просмотр..."), this, &TextEdit::filePrintPreview);

    const QIcon exportPdfIcon = QIcon::fromTheme("exportpdf", QIcon(rsrcPath + "/exportpdf.png"));
    a = menu->addAction(exportPdfIcon, tr("&Экспорт в PDF..."), this, &TextEdit::filePrintPdf);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(Qt::CTRL + Qt::Key_D);
    tb->addAction(a);

    menu->addSeparator();
#endif

    a = menu->addAction(tr("&Выход"), this, &QWidget::close);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);
}
void TextEdit::setupTableActions()
{
    QToolBar *tb = addToolBar(tr("Tables Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&Таблицы"));

    const QIcon addTableIcon = QIcon::fromTheme("add-table", QIcon(rsrcPath + "/addtable.png"));
    actionAddTable = menu->addAction(addTableIcon , tr("&Добавить таблицу"), this, SLOT(addTable()));
    tb->addAction(actionAddTable);
    menu->addSeparator();

    const QIcon addRowIcon = QIcon::fromTheme("add-row", QIcon(rsrcPath + "/addrow.png"));
    actionAddRow = menu->addAction(addRowIcon , tr("&Вставить строку"), this, SLOT(addRow()));
    actionAddRow->setPriority(QAction::LowPriority);
    tb->addAction(actionAddRow);

    const QIcon addColIcon = QIcon::fromTheme("add-col", QIcon(rsrcPath + "/addcol.png"));
    actionAddCol = menu->addAction(addColIcon , tr("&Вставить столбец"), this, SLOT(addCol()));
    actionAddCol->setPriority(QAction::LowPriority);
    tb->addAction(actionAddCol);
    menu->addSeparator();

    const QIcon DelRowIcon = QIcon::fromTheme("del-row", QIcon(rsrcPath + "/delrow.png"));
    actionDelRow = menu->addAction(DelRowIcon , tr("&Удалить строку"), this, SLOT(delRow()));
    actionDelRow->setPriority(QAction::LowPriority);
    tb->addAction(actionDelRow);

    const QIcon delColIcon = QIcon::fromTheme("del-col", QIcon(rsrcPath + "/delcol.png"));
    actionDelCol = menu->addAction(delColIcon , tr("&Удалить столбец"), this, SLOT(delCol()));
    actionDelCol->setPriority(QAction::LowPriority);
    tb->addAction(actionDelCol);
    menu->addSeparator();

    const QIcon mergeCellsIcon = QIcon::fromTheme("mer-cel", QIcon(rsrcPath + "/mergecells.png"));
    actionMergeCells = menu->addAction(mergeCellsIcon , tr("&Объеденить ячейки"), this, SLOT(mergeCells()));
    actionMergeCells->setPriority(QAction::LowPriority);
    tb->addAction(actionMergeCells);
}
void TextEdit::setupEditActions()
{
    QToolBar *tb = addToolBar(tr("Edit Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&Редактирование"));

    const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png"));
    actionUndo = menu->addAction(undoIcon, tr("&Назад"), textEdit, &QTextEdit::undo);
    actionUndo->setShortcut(QKeySequence::Undo);
    tb->addAction(actionUndo);

    const QIcon redoIcon = QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png"));
    actionRedo = menu->addAction(redoIcon, tr("&Вперёд"), textEdit, &QTextEdit::redo);
    actionRedo->setPriority(QAction::LowPriority);
    actionRedo->setShortcut(QKeySequence::Redo);
    tb->addAction(actionRedo);
    menu->addSeparator();

#ifndef QT_NO_CLIPBOARD
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png"));
    actionCut = menu->addAction(cutIcon, tr("Вы&резать"), textEdit, &QTextEdit::cut);
    actionCut->setPriority(QAction::LowPriority);
    actionCut->setShortcut(QKeySequence::Cut);
    tb->addAction(actionCut);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png"));
    actionCopy = menu->addAction(copyIcon, tr("&Копировать"), textEdit, &QTextEdit::copy);
    actionCopy->setPriority(QAction::LowPriority);
    actionCopy->setShortcut(QKeySequence::Copy);
    tb->addAction(actionCopy);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png"));
    actionPaste = menu->addAction(pasteIcon, tr("Вс&тавить"), textEdit, &QTextEdit::paste);
    actionPaste->setPriority(QAction::LowPriority);
    actionPaste->setShortcut(QKeySequence::Paste);
    tb->addAction(actionPaste);
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif
}
void TextEdit::setupTextActions()
{
    QToolBar *tb = addToolBar(tr("Format Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&Форматирование"));

    menu->addSeparator();

    const QIcon boldIcon = QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png"));
    actionTextBold = menu->addAction(boldIcon, tr("&Выделение"), this, &TextEdit::textBold);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    tb->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    const QIcon italicIcon = QIcon::fromTheme("format-text-italic", QIcon(rsrcPath + "/textitalic.png"));
    actionTextItalic = menu->addAction(italicIcon, tr("&Курсив"), this, &TextEdit::textItalic);
    actionTextItalic->setPriority(QAction::LowPriority);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    tb->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    const QIcon underlineIcon = QIcon::fromTheme("format-text-underline", QIcon(rsrcPath + "/textunder.png"));
    actionTextUnderline = menu->addAction(underlineIcon, tr("П&одчёркивание"), this, &TextEdit::textUnderline);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    actionTextUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    tb->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    menu->addSeparator();

    const QIcon leftIcon = QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png"));
    actionAlignLeft = new QAction(leftIcon, tr("&Слева"), this);
    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignLeft->setPriority(QAction::LowPriority);
    const QIcon centerIcon = QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png"));
    actionAlignCenter = new QAction(centerIcon, tr("&По центру"), this);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignCenter->setPriority(QAction::LowPriority);
    const QIcon rightIcon = QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png"));
    actionAlignRight = new QAction(rightIcon, tr("Сп&рава"), this);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignRight->setPriority(QAction::LowPriority);
    const QIcon fillIcon = QIcon::fromTheme("format-justify-fill", QIcon(rsrcPath + "/textjustify.png"));
    actionAlignJustify = new QAction(fillIcon, tr("&Равномерно"), this);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);
    actionAlignJustify->setPriority(QAction::LowPriority);

    // Make sure the alignLeft  is always left of the alignRight
    QActionGroup *alignGroup = new QActionGroup(this);
    connect(alignGroup, &QActionGroup::triggered, this, &TextEdit::textAlign);

    if (QApplication::isLeftToRight()) {
        alignGroup->addAction(actionAlignLeft);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignRight);
    } else {
        alignGroup->addAction(actionAlignRight);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignLeft);
    }
    alignGroup->addAction(actionAlignJustify);

    tb->addActions(alignGroup->actions());
    menu->addActions(alignGroup->actions());

    menu->addSeparator();

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = menu->addAction(pix, tr("&Цвет..."), this, &TextEdit::textColor);
    tb->addAction(actionTextColor);

    tb = addToolBar(tr("Format Actions"));
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBarBreak(Qt::TopToolBarArea);
    addToolBar(tb);

    comboStyle = new QComboBox(tb);
    tb->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");

    connect(comboStyle, QOverload<int>::of(&QComboBox::activated), this, &TextEdit::textStyle);

    comboFont = new QFontComboBox(tb);
    tb->addWidget(comboFont);
    connect(comboFont, QOverload<const QString &>::of(&QComboBox::activated), this, &TextEdit::textFamily);

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    comboSize->setEditable(true);

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    foreach (int size, standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, QOverload<const QString &>::of(&QComboBox::activated), this, &TextEdit::textSize);
}
bool TextEdit::load_html(const QString &h)
{
        textEdit->setHtml(h);
        sv->operator()(textEdit->toHtml());
        setCurrentFileName("Протокол");
        return true;
}
void TextEdit::set_callback(ret_str *arg)
{
    sv = arg;
}
bool TextEdit::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Документ был изменён.\n"
                                "Хотите сохранить изменения?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}
void TextEdit::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "Протокол";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName, QCoreApplication::applicationName()));
    setWindowModified(false);
}
void TextEdit::fileNew()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFileName(QString());
    }
}
bool TextEdit::fileSave()
{
    bool success = sv->operator()(textEdit->document()->toHtml());
    if (success) {
        sv->save();
        textEdit->document()->setModified(false);
    }
    return success;
}
bool TextEdit::fileSaveAs()
{
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "application/vnd.oasis.opendocument.text" << "text/html" << "text/plain";
    fileDialog.setMimeTypeFilters(mimeTypes);
    fileDialog.setDefaultSuffix("odt");
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first();
    setCurrentFileName(fn);
    if (fileName.isEmpty())
        return fileSaveAs();
    if (fileName.startsWith(QStringLiteral(":/")))
        return fileSaveAs();
    QTextDocumentWriter writer(fileName);
    bool success = writer.write(textEdit->document());
    if (success) {
        textEdit->document()->setModified(false);
        statusBar()->showMessage(tr("Записано в \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    } else {
        statusBar()->showMessage(tr("Не могу записать файл \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
    }
    return success;
}
void TextEdit::filePrint()
{
#if QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPaperSize(QPrinter::A4);
    QSizeF paperSize;
    paperSize.setWidth(printer.width());
    paperSize.setHeight(printer.height());
    textEdit->document()->setPageSize(paperSize);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Печатать документ"));
    if (dlg->exec() == QDialog::Accepted)
        textEdit->print(&printer);
    delete dlg;
#endif
}
void TextEdit::filePrintPreview()
{
#if QT_CONFIG(printpreviewdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &TextEdit::printPreview);
    preview.exec();
#endif
}

void TextEdit::printPreview(QPrinter *printer)
{
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else
    textEdit->print(printer);
#endif
}
void TextEdit::filePrintPdf()
{
#ifndef QT_NO_PRINTER
//! [0]
    QFileDialog fileDialog(this, tr("Экспорт в PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString fileName = fileDialog.selectedFiles().first();
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPaperSize(QPrinter::A4);
    QSizeF paperSize;
    paperSize.setWidth(printer.width());
    paperSize.setHeight(printer.height());
    textEdit->document()->setPageSize(paperSize);
    textEdit->document()->print(&printer);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    textEdit->document()->print(&printer);
    statusBar()->showMessage(tr("Экспортировано в \"%1\"")
                             .arg(QDir::toNativeSeparators(fileName)));
//! [0]
#endif
}
void TextEdit::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}
void TextEdit::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}
void TextEdit::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}
void TextEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}
void TextEdit::textSize(const QString &p)
{
    qreal pointSize = static_cast<qreal>(p.toFloat());
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}
void TextEdit::textStyle(int styleIndex)
{
    QTextCursor cursor = textEdit->textCursor();

    if (styleIndex != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (styleIndex) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListCircle;
                break;
            case 3:
                style = QTextListFormat::ListSquare;
                break;
            case 4:
                style = QTextListFormat::ListDecimal;
                break;
            case 5:
                style = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                style = QTextListFormat::ListUpperAlpha;
                break;
            case 7:
                style = QTextListFormat::ListLowerRoman;
                break;
            case 8:
                style = QTextListFormat::ListUpperRoman;
                break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);

        cursor.createList(listFmt);

        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}
void TextEdit::textColor()
{
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}
void TextEdit::textAlign(QAction *a)
{
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}
void TextEdit::cursorPositionChanged()
{
    alignmentChanged(textEdit->alignment());
}
void TextEdit::clipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif
}
void TextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);
}
void TextEdit::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}
void TextEdit::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}
void TextEdit::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft)
        actionAlignLeft->setChecked(true);
    else if (a & Qt::AlignHCenter)
        actionAlignCenter->setChecked(true);
    else if (a & Qt::AlignRight)
        actionAlignRight->setChecked(true);
    else if (a & Qt::AlignJustify)
        actionAlignJustify->setChecked(true);
}
void TextEdit::fileOpen()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters(QStringList() << "text/html" << "text/plain");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
    if (load(fn))
        statusBar()->showMessage(tr("Открыт \"%1\"").arg(QDir::toNativeSeparators(fn)));
    else
        statusBar()->showMessage(tr("Не могу открыть \"%1\"").arg(QDir::toNativeSeparators(fn)));
}
bool TextEdit::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        load_html(str);
    } else {
        str = QString::fromLocal8Bit(data);
        textEdit->setPlainText(str);
    }
    setCurrentFileName(f);
    return true;
}
void TextEdit::addTable()
{
    add_table* tad = new add_table();
    if (tad->exec() == QDialog::Accepted) {
    textEdit->insertHtml(tad->result());
    }
    delete tad;
}
void TextEdit::addRow()
{
    QTextTable *act =  textEdit->textCursor().currentTable();
    if (act == nullptr || act == 0) return;
    int tmpc = act->cellAt(textEdit->textCursor()).row();
    act->insertRows(tmpc + 1, 1);
}
void TextEdit::addCol()
{
    QTextTable *act =  textEdit->textCursor().currentTable();
    if (act == nullptr || act == 0) return;
    int tmpc = act->cellAt(textEdit->textCursor()).column();
    act->insertColumns(tmpc + 1, 1);
}

void TextEdit::delRow()
{
    QTextTable *act =  textEdit->textCursor().currentTable();
    if (act == nullptr || act == 0) return;
    int tmpc = act->cellAt(textEdit->textCursor()).row();
    act->removeRows(tmpc, 1);
}
void TextEdit::delCol()
{
    QTextTable *act =  textEdit->textCursor().currentTable();
    if (act == nullptr || act == 0) return;
    int tmpc = act->cellAt(textEdit->textCursor()).column();
    act->removeColumns(tmpc, 1);
}
void TextEdit::mergeCells()
{
    QTextTable *act =  textEdit->textCursor().currentTable();
    if (act == nullptr || act == 0) return;
    act->mergeCells(textEdit->textCursor());
}
// --------------------========================== Окошко для добавления таблиц ======================================------------------------------
add_table::add_table(QWidget *par) : QDialog(par)
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Добавить таблицу");
    columns = new QSpinBox();
    columns->setMinimum(1);
    columns->setMaximumWidth(100);
    QBoxLayout* col_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* col_lab = new QLabel();
    col_lab->setText("Столбцов: ");
    col_lab->setMinimumWidth(200);
    col_lab->setMaximumWidth(200);
    col_lab->setAlignment(Qt::AlignRight);
    col_lay->addWidget(col_lab);
    col_lay->addWidget(columns);
    rows = new QSpinBox();
    rows->setMinimum(1);
    QBoxLayout* row_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* row_lab = new QLabel();
    row_lab->setText("Строк: ");
    row_lab->setMinimumWidth(200);
    row_lab->setMaximumWidth(200);
    row_lab->setAlignment(Qt::AlignRight);
    row_lay->addWidget(row_lab);
    row_lay->addWidget(rows);
    border = new QSpinBox();
    border->setMinimum(1);
    QBoxLayout* border_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* border_lab = new QLabel();
    border_lab->setText("Толщина рамки: ");
    border_lab->setMinimumWidth(200);
    border_lab->setMaximumWidth(200);
    border_lab->setAlignment(Qt::AlignRight);
    border_lay->addWidget(border_lab);
    border_lay->addWidget(border);
    width = new QSpinBox();
    width->setValue(100);
    width->setRange(1, 100);
    width->setSuffix(" %");
    QBoxLayout* width_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* width_lab = new QLabel();
    width_lab->setText("Ширина таблицы: ");
    width_lab->setMinimumWidth(200);
    width_lab->setMaximumWidth(200);
    width_lab->setAlignment(Qt::AlignRight);
    width_lay->addWidget(width_lab);
    width_lay->addWidget(width);
    align = new QComboBox();
    align->addItem("По центру", "center");
    align->addItem("Слева", "left");
    align->addItem("Справа", "right");
    QBoxLayout* align_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* align_lab = new QLabel();
    align_lab->setText("Выравнивание: ");
    align_lab->setMinimumWidth(200);
    align_lab->setMaximumWidth(200);
    align_lab->setAlignment(Qt::AlignRight);
    align_lay->addWidget(align_lab);
    align_lay->addWidget(align);
    inv = new QRadioButton();
    inv->setChecked(false);
    QLabel* inv_lab = new QLabel();
    QBoxLayout* inv_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    inv_lab->setText("Задать атрибуты: ");
    inv_lab->setMinimumWidth(200);
    inv_lab->setMaximumWidth(200);
    inv_lab->setAlignment(Qt::AlignRight);
    inv_lay->addWidget(inv_lab);
    inv_lay->addWidget(inv);
    QLabel* style_lab = new QLabel();
    style_lab->setText("Если флажок установлен, то таблица <br>будут создана с нижеследующими атрибутами:");
    style_t = new QTextEdit();
    style_t->setMinimumWidth(500);
    style_t->setPlainText("align = \"center\" width=\"100%\" bordercolor=\"black\" border=\"1\" cellspacing=\"0\"");
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QBoxLayout *end_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    end_lay->addWidget(my_ok);
    end_lay->addWidget(my_cancel);
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addLayout(col_lay);
    main_lay->addLayout(row_lay);
    main_lay->addLayout(border_lay);
    main_lay->addLayout(width_lay);
    main_lay->addLayout(align_lay);
    main_lay->addLayout(inv_lay);
    main_lay->addWidget(style_lab);
    main_lay->addWidget(style_t);
    main_lay->addLayout(end_lay);
    this->setLayout(main_lay);
}
add_table::~add_table()
{
    delete columns;
    delete rows;
    delete border;
    delete width;
    delete align;
    delete inv;
    delete style_t;
}
QString add_table::result()
{
    QString ret{""};
    if (inv->isChecked()){
        ret += "<table " + style_t->toPlainText() + ">";
    } else {
        ret += "<table  align = \"" + align->currentData().toString() +
                "\" width=\"" + QString::number(width->value()) +
                "%\" bordercolor=\"black\" border=\"" + QString::number(border->value()) +
                "\" cellspacing=\"0\"";
        ret += ">";
    }
    for (int i = 1; i <= rows->value(); ++i){
        ret += "<tr>";
        for (int j = 1; j <= columns->value(); ++j){
            ret += "<td> </td>";
        }
        ret += "</tr>";
    }
    ret += "</table>";
    return ret;
}
