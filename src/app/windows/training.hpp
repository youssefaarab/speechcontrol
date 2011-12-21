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

#ifndef TRAINING_WINDOW_HPP
#define TRAINING_WINDOW_HPP

#include <QDialog>

namespace Ui {
    class Training;
}

namespace SpeechControl {
    class Session;

namespace Windows {

class Training : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(Session* Session READ session WRITE setSession)

public:
    explicit Training(QWidget *parent = 0);
    virtual ~Training();
    static void startTraining(Session*);
    void setSession(Session* );
    Session* session() const;

public slots:
    void stopCollecting();
    void startCollecting();

private slots:
    void on_pushButtonProgress_toggled(bool checked);

private:
    Ui::Training *ui;
    Session* m_session;
};

}}

#endif // TRAINING_WINDOW_HPP
