/**
 * This file is part of SpeechControl
 *
 * Copyright 2011 Jacky Alcine <jacky.alcine@thesii.org>
 *
 * SpeechControl is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * SpeechControl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with SpeechControl; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <microphone.hpp>

#include "micpicker.hpp"
#include "ui_micpicker.h"

using namespace SpeechControl;
using namespace SpeechControl::Wizards::Pages;

MicrophonePicker::MicrophonePicker(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::MicrophoneSelection)
{
    ui->setupUi(this);

    MicrophoneList l_mics = Microphone::allMicrophones();
    if (l_mics.empty())
        ui->comboBoxMicrophones->setEnabled(false);
    else {
        Q_FOREACH(const Microphone* l_mic, l_mics)
            ui->comboBoxMicrophones->addItem(l_mic->friendlyName(),l_mic->uuid().toString());
    }
}

MicrophonePicker::~MicrophonePicker()
{
    delete ui;
}