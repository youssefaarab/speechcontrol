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

#ifndef USER_HPP
#define USER_HPP

#include <QObject>

class QUrl;
class QFile;
class QUuid;
class QDomDocument;

namespace SpeechControl {
    class User;
    class Session;
    class SessionList;

    class User : public QObject {
        Q_OBJECT

    public:
        explicit User(QObject *parent = 0);
        virtual ~User();
        SessionList sessions() const;
        Session* createSession();
        static User* loadFromString(QFile& );
        static User* loadFromUrl(QUrl&);
        static User* loadFromUuid(QUuid& );
        static const bool hasAny();

    signals:
        void loaded();
        void saved();

    public slots:
        void save();
        void load(QUrl&);
        void load(QUuid&);

    private:
        void load(QFile&);
        QDomDocument* m_dom;
    };
}

#endif // USER_HPP
