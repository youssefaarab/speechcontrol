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

#include "core.hpp"
#include "session.hpp"
#include "content-information-dialog.hpp"
#include "ui_content-information-dialog.h"

using SpeechControl::Core;
using SpeechControl::Windows::ContentInformationDialog;

ContentInformationDialog::ContentInformationDialog ( Content* p_content ) :
    QDialog ( Core::mainWindow() ),
    m_ui ( new Ui::ContentInformationDialog ),
    m_content ( p_content ) {
    m_ui->setupUi ( this );
    updateUi();
}

void ContentInformationDialog::updateUi(){
    m_ui->lblTitle->setText(QString("<p><span style=\"font-size:16pt;\">%1</span></p>"
                                    "<p>by <span style=\"font-weight:600;\">%2</span></p>")
                           .arg(m_content->title(),m_content->author()));
}


ContentInformationDialog::~ContentInformationDialog() {
    delete m_ui;
}

#include "content-information-dialog.moc"
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
