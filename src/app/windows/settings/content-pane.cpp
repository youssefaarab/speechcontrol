/***
 *  This file is part of SpeechControl.
 *
 *  Copyright (C) 2012 SpeechControl Developers <spchcntrl-devel@thesii.org>
 *
 *  SpeechControl is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  SpeechControl is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with SpeechControl .  If not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "content-pane.hpp"
#include "sessions/session.hpp"
#include "windows/content-information-dialog.hpp"
#include "windows/contents-wizard.hpp"
#include "ui_settingspane-content.h"

#include <QListWidget>
#include <QMessageBox>
#include <QErrorMessage>

using namespace SpeechControl;
using namespace SpeechControl::Windows;

ContentSettingsPane::ContentSettingsPane ( QWidget *parent ) :
    QFrame ( parent ),
    ui ( new Ui::ContentSettingsPane ) {
    ui->setupUi ( this );
    updateList();
}

ContentSettingsPane::~ContentSettingsPane() {
    delete ui;
}

void ContentSettingsPane::show() {
    updateList();
    QFrame::show();
}

void ContentSettingsPane::changeEvent ( QEvent *e ) {
    QFrame::changeEvent ( e );
    switch ( e->type() ) {
    case QEvent::LanguageChange:
        ui->retranslateUi ( this );
        break;
    default:
        break;
    }
}

const QString SpeechControl::Windows::ContentSettingsPane::title() const {
    return "Content";
}

const QString SpeechControl::Windows::ContentSettingsPane::id() const {
    return "cntns";
}

void SpeechControl::Windows::ContentSettingsPane::updateList() {
    QListWidget* l_widget = ui->lstContent;
    ContentList l_lst = Content::allContents();

    l_widget->clear();

    if ( !l_lst.empty() ) {
        Q_FOREACH ( const Content* l_cnt, l_lst ) {
            const QString l_lbl = l_cnt->title();
            QListWidgetItem* l_item = new QListWidgetItem ( l_widget );
            l_item->setData ( Qt::UserRole,l_cnt->uuid().toString() );
            l_widget->addItem ( l_item );

            if ( l_lbl.isEmpty() ) {
                l_item->setText ( tr ( "Unnamed" ) );
            } else {
                l_item->setText ( l_lbl );
            }
        }
    }
}

void SpeechControl::Windows::ContentSettingsPane::on_btnDelete_clicked() {
    QListWidget* l_widg = ui->lstContent;
    if ( !l_widg->selectedItems().empty() ) {
        Q_FOREACH ( QListWidgetItem* l_itm, l_widg->selectedItems() ) {
            Content* l_cntn = Content::obtain ( l_itm->data ( Qt::UserRole ).toString() );
            if ( QMessageBox::Yes == QMessageBox::question ( this,
                    tr ( "Confirm Content Delete" ),
                    tr ( "Are you sure you want to delete this book '%1' by '%2'?\nAny session connected to the book will become invalid and untrainable." ).arg ( l_cntn->title() ).arg ( l_cntn->author() ),
                    QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::No ) ) {
                l_cntn->erase();
            }
        }

        updateList();
    }
}

void SpeechControl::Windows::ContentSettingsPane::on_btnAdd_clicked() {
    Wizards::ContentWizard* l_wiz = new Wizards::ContentWizard ( this );
    if ( l_wiz->exec() == QDialog::Accepted ) {
        updateList();
    }
}

void SpeechControl::Windows::ContentSettingsPane::on_btnInfo_clicked() {
    QListWidget* l_widg = ui->lstContent;
    if ( !l_widg->selectedItems().empty() ) {
        Q_FOREACH ( QListWidgetItem* l_itm, l_widg->selectedItems() ) {
            Content* l_cntn = Content::obtain ( l_itm->data ( Qt::UserRole ).toString() );
            ContentInformationDialog l_dialog ( l_cntn );
            l_dialog.exec();
        }
    }
}

#include "content-pane.moc"
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;