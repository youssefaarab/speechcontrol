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

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <QObject>
#include "plugins.hpp"

namespace SpeechControl {
namespace Plugins {
class Factory;

/**
 * @brief Represents a manipulative system to control plug-ins.
 *
 * The Factory of SpeechControl allows the system to load and unload plug-ins at whim.
 * Configuration and settings about plug-ins can also be obtained via convenience methods
 * provided by the Factory.
 *
 * @section configuration-settings Settings and Configuration
 *
 * The term 'configuration' and 'setting' are synonyms, but here in SpeechControl, we use the
 * terms to define two separate things.
 *
 * @subsection configuration Plug-in Configuration
 * <b>Configuration</b> refers to the settings used to define the plug-in so that SpeechControl can determine its dependencies and manage the (un)loading process.
 *
 * @subsection settings Plug-in Settings
 * <b>Settings</b> refer to the options and values that the plug-in will use within SpeechControl to extend its functionality.
 *
 **/
class Factory : public QObject {
    Q_OBJECT

signals:
    /**
     * @brief Emitted when the Factory's started.
     **/
    void started();

    /**
     * @brief Emitted when the Factory's stopped.
     **/
    void stopped();

    /**
     * @brief Emitted when a plug-in is loaded.
     * @param p_uuid The UUID of the plug-in loaded.
     **/
    void pluginLoaded ( const QUuid& p_uuid );

    /**
     * @brief Emitted when a plug-in is unloaded.
     * @param p_uuid The UUID of the plug-in unloaded.
     **/
    void pluginUnloaded ( const QUuid& );

public slots:
    /**
     * @brief Starts the Factory.
     **/
    void start();

    /**
     * @brief Stops the Factory.
     **/
    void stop();

public:
    /**
     * @brief Destructor.
     **/
    virtual ~Factory();

    /**
     * @brief Loads a plug-in.
     *
     * Invokes the loading process for a plug-in and readies it
     * for integration with SpeechControl.
     *
     * @param p_uuid The UUID of the plug-in to load.
     * @return const bool True if the plug-in loaded successfully, false otherwise.
     **/
    static bool loadPlugin ( const QUuid& );

    /**
     * @brief Unloads a plug-in.
     *
     * Invokes the unloading process for a plug-in and readies it
     * for removal from SpeechControl.
     *
     * @param p_uuid The UUID of the plug-in to unload.
     * @return const bool True if the plug-in unloaded successfully, false otherwise.
     **/
    void unloadPlugin ( const QUuid& p_uuid );

    /**
     * @brief Determines if a plug-in has been loaded.
     * @param p_uuid The plug-in's UUID to verify.
     * @return bool True if the plug-in is loaded, false otherwise.
     **/
    static bool isPluginLoaded ( const QUuid& );

    /**
     * @brief Obtains a list of loaded plug-ins.
     * @return A PluginList. length() == 0 if there's no loaded plug-ins.
     **/
    static PluginList loadedPlugins();

    /**
     * @brief Obtains a mapping of all of the plug-ins that can be loaded by SpeechControl.
     * @return A PluginMap of all of the discovered plug-ins for SpeechControl on the system.
     **/
    static PluginMap availablePlugins();

    /**
     * @brief Obtains a pointer to the Factory's instance.
     * @return Factory.
     **/
    static Factory* instance();

    /**
     * @brief Obtains the configuration of a plug-in by its specified UUID.
     * @param p_uuid The UUID of the plug-in whose configuration is requested.
     * @return A pointer to a QSettings* object. NULL if the UUID points to an invalid plug-in.
     * @see pluginSettings()
     **/
    static QSettings* pluginConfiguration ( QUuid p_uuid );

    /**
     * @brief Obtains the settings of a plug-in by its specified UUID.
     * @param p_uuid The UUID of the plug-in whose settings is requested.
     * @return A pointer to a QSettings* object. NULL if the UUID points to an invalid plug-in.
     * @see pluginConfiguration()
     **/
    static QSettings* pluginSettings ( QUuid p_uuid );

private:
    explicit Factory();
    static Factory* s_inst;
    static PluginMap s_ldPlgns;
};
}
}

#endif // FACTORY_HPP
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
